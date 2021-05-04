function readAndPlotSerial(src)
            % Read the incoming data:
            dataBuffer = read(src, src.UserData.inputBufferSize, 'uint8');
            dataPoints = src.UserData.inputBufferSize/src.UserData.dataLength;
            byteSequence = 1:src.UserData.dataLength;
            % preallocate for speed:
            LFPData          = zeros(1,dataPoints);
            AlgValues        = zeros(1,dataPoints);
            phaseCondition   = zeros(1,dataPoints);
            time             = zeros(1,dataPoints);
            gain             = zeros(1,dataPoints);
            IntensAlg        = zeros(1,dataPoints);
            Algorithm        = zeros(1,dataPoints);
            for datapoint = 1:dataPoints
                % extract the bytes associated with the data point
                dataBytes = dataBuffer(byteSequence);
                % convert the byte sequence to a binary sequence
                binVals = [];
                for n = 1:src.UserData.dataLength
                    binVals = [binVals, dec2bin(dataBytes(n),8)];
                end
                
                % Byte 1: bits 0-7:     LFP Data
                % Byte 2: bits 8-15:    not used
                % Byte 3: bits 0-7:     Algorithm values
                % Byte 4: bits 8-15:    Algorithm values (cont)
                % Byte 5: bits 0-7:     Phase condition
                % Byte 6: bits 0-7:     Time (may need to be bigger than 1
                % byte)
                % Byte 7: bits 10-13:   Gain
                % Byte 7: bits 14:      Algo: 0 = original, 1 = set intensity
                % Byte 7: bits 15:      Algorithm ON/OFF
                LFPData(datapoint)          = dataBytes(1);
                AlgValues(datapoint)        = bitshift(dataBytes(4),8)+dataBytes(3); % Combine bytes 3 and 4
                phaseCondition(datapoint)   = dataBytes(5); %bin2dec(binVals(32:39));
                time(datapoint)             = bin2dec(binVals(40:42));
                gain(datapoint)             = bin2dec(binVals(43:46));
                IntensAlg(datapoint)        = binVals(47);
                Algorithm(datapoint)        = binVals(48);
                
                byteSequence = byteSequence + src.UserData.dataLength;
            end
            % ----------------------------------------
            % Prepare the data for display
            % ----------------------------------------
            % convert LFPData into uV
            LFPData = LFPData ./ 255 .* 3.3;
            %
            % Convert phase condition to degrees
            phaseCondition = phaseCondition .* 45;
            t_sequence = 1:dataPoints-1;
            LFPData_sequence = LFPData(2:501);
            ProcessedData_sequence = AlgValues(2:501);
            AlgState_sequence = phaseCondition;
            % ----------------------------------------
            % Plot the data
            % ----------------------------------------
            % Plot the incoming data (Top graph)
            plot(src.UserData.LFPGraph, t_sequence, LFPData_sequence);
            pause(0.00001);
            % Plot the processed data (middle graph)
            plot(src.UserData.ProcessedGraph, t_sequence, ProcessedData_sequence);
            pause(0.00001);
            % Plot the Algorithm state overlaid on the LFP
            hold(src.UserData.LFPGraph)
            plot(src.UserData.LFPGraph, t_sequence, AlgState_sequence);
            pause(0.00001);
            % Update the parameters displayed on the GUI
            src.UserData.degLabel_2.Text = num2str(phaseCondition(dataPoints));
            src.UserData.Label_6.Text = num2str(gain(dataPoints));
            if IntensAlg(dataPoints) % if this is 1 then the current algorithm is set intensity
                src.UserData.AlgorithmLabel.Text = 'Set Intensity';
                src.UserData.IntensityLabel.Text = 'Intensity';
            else
                src.UserData.AlgorithmLabel.Text = 'Original FIR';
                src.UserData.IntensityLabel.Text = 'Gain';
            end
            % ----------------------------------------
            % Save data to file
            % ----------------------------------------
            fname      = sprintf ('%s %i', src.UserData.filename, src.UserData.index);
            matfile    = fullfile(src.UserData.path, fname);
            save(matfile,'LFPData','AlgValues','phaseCondition','src.UserData.index');
            src.UserData.index = src.UserData.index + 1;
        end