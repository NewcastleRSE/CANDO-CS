clear;
clc;
close all;

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% GUI and Algorithm Parameters
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
algoOption  = 0;        % Algorithm option 			(Original/Set Intensity)    - Default: Original
phaseOption = 0;        % Phase options				(Fixed/Sequential/Random)   - Default: Fixed
phaseCond   = 4;        % Phase condition			(0-7)                       - Default: 0
gainOption  = 0;        % Gain options				(Fixed/Sequential/Random) 	- Default: Fixed
gain        = 1;        % Gain value				(1-?)						- Default: 1
f           = 10;       % Central frequency			(10 Hz)						- Default: 10
thr         = 0;        % Threshold					(0-?)						- Default: 0
setIntValB1 = 250;      % Set intensity value 		(?-?)						- Default: ?
setIntValB2 = 0;        % Set intensity value cont.
kernelLenB1 = 0;        % Kernel length				(?-?)						- Default: 512
kernelLenB2 = 2;        % Kernel length cont.
dutyCycle   = 0;        % Duty cycle				(Off/On)					- Default: Off
onTimeB1    = 0;        % On-time					(100ms - 1000s)				- Default: 1s
onTimeB2    = 0;        % On-time cont.
offTimeB1   = 0;        % Off-time					(100ms - 1000s)				- Default: 1s
offTimeB2   = 0;        % Off-time cont.
manLED      = 0;        % Manual Algo/LED control 	(Algo/LED)					- Default: Algo
manLEDLvlB1 = 0;        % Manual LED DAC level		(0-4095)					- Default: 0
manLEDLvlB2 = 0;        % Manual LED DAC level cont.

num         = 100;      % Number of times rx buffer fills up

dur         = 1;        % Duration of collected data
Ts          = 0.002;    % Sampling period in seconds
dataPoints  = (dur/Ts); % Number of samples
packetLen   = 9;        % bytes
t = (1:dataPoints)*Ts*1000;

inputBufferSize = packetLen*dataPoints;
baudRate = 256000;

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Serial Port Communication
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
delete(instrfind);
s = serial('COM25', 'BaudRate', baudRate, 'InputBufferSize', inputBufferSize);

fopen(s);

fwrite(s, [algoOption, phaseOption, phaseCond, gainOption, gain, f, thr, setIntValB1, setIntValB2, kernelLenB1, kernelLenB2, dutyCycle, onTimeB1, onTimeB2, offTimeB1, offTimeB2, manLED, manLEDLvlB1, manLEDLvlB2]);

% cnt = 1;
% 
% figure;
% 
% while(cnt < num)    
% 
%     while (~strcmp(get(s, 'TransferStatus'), 'idle')) 
%     end
% 
%     while(s.BytesAvailable ~= inputBufferSize) 
%     end
% 
%     inputBuffer = fread(s, inputBufferSize, 'uint8');
% 
%     while (~strcmp(get(s, 'TransferStatus'), 'idle'))
%     end
% 
%     % ------------------------------------------------
%     % extract data 
%     % ------------------------------------------------
%     % The data is in a binary sequence so the data needs to
%     % be acquired as bytes, converted to binary and then
%     % the information extracted for each of the components
%     byteSequence = 1:packetLen;
% 
%     LFPData = 0;
%     AlgValues = 0;
% 
%     data = inputBuffer;
% 
%     for datapoint = 1:dataPoints
% 
%         % extract the bytes associated with the data point
%         dataBytes = inputBuffer(byteSequence);
% 
%         % Byte 1: bits 0-7:     LFP Data
%         % Byte 2: bits 8-15:    not used
%         % Byte 3: bits 0-7:     Algorithm values
%         % Byte 4: bits 8-11:    Algorithm values (cont)
%         % Byte 4: bits 12-15:   Phase condition
%         % Byte 5: bits 0-7:     Time
%         % Byte 5: bits 8-9:     Time (cont)
%         % Byte 6: bits 10-13:   Gain 
%         % Byte 6: bits 14:      Algo: 0 = original, 1 = set intensity
%         % Byte 6: bits 15:      Algorithm ON/OFF
%         LFPData(datapoint)     = dataBytes(1)/255*3.3;
%         AlgValues(datapoint)   = (bitshift(dataBytes(4), 8) + dataBytes(3))/4095*3.3;
%         phaseCond(datapoint)   = dataBytes(5);
% 
%         byteSequence = byteSequence + packetLen;
%     end
% 
%     clf;
%     hold on
%     plot(t, LFPData);
%     plot(t, AlgValues);
%     plot(t, phaseCond);
%     ylim([0 7.1]);
%     xlabel('Time (ms)');
%     ylabel('Amplitude (V)');
%     pause(0.00001);
% 
%     cnt = cnt + 1;
% end

fclose(s);
delete(instrfind);