% Signal generator to output a time series with random seizure like
% activity.
% Based on the adapted wilson cowan model.
clear all;

pause on

dt = 0.001; %1000Hz sample rate
freq = 10;

% Byte 1: bits 0-7:     LFP Data
% Byte 2: bits 8-15:    not used
% Byte 3: bits 0-7:     Algorithm values
% Byte 4: bits 8-11:    Algorithm values (cont)
% Byte 4: bits 12-15:   
% Byte 5: bits 0-7:     Time
% Byte 5: bits 8-9:     Phase condition
% Byte 6: bits 10-13:   Gain
% Byte 6: bits 14:      Algo: 0 = original, 1 = set intensity
% Byte 6: bits 15:      Algorithm ON/OFF
alg1 = 0;
alg2 = 0;
phase = 0;
gain =0;
Algo = 0;
onoff = 0; % always off

inputBufferSize = 6000;

% run in a while loop, outputting to file in a byte each value 
fid = fopen('incoming.bin','w'); % Open file to write to:
fid2 = fopen('saveincoming.bin','w');

t = 0;

while 1 % while true, infinite loop :O 
    
        % 10 Hz sine wave with 1000Hz sampling, need to generate one data
        % point per loop.
        signal = round(sin(t*freq*2*pi)*100+127.5); % Need to center between 0 and 255
        
        %disp(signal)
        fwrite(fid,[signal,0,alg1,alg2,phase,0]);
        fwrite(fid2,signal);

        fileprops = dir('incoming.bin');
        if fileprops.bytes >= inputBufferSize % When we hit the input buffer size the GUI expects
            pause(0.5)
            fclose(fid);
            fid = fopen('incoming.bin','w'); % Open file to write to, clearing the contents
            disp('data packet full')
        end
        pause(0.1) % don't want to generate too much too fast.
        t = t+dt;
end




