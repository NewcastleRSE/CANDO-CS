% Signal generator to output a time series with random seizure like
% activity.
% Based on the adapted wilson cowan model.
clear all;

pause on

rng(35)
params.h = 0.001;

params.a = 17;
params.b = 10;
params.c = 40;
params.d = 0;
params.P = -0.3;
params.Q = -15;
params.taux = 0.0264;
params.tauy = 0.012;
params.noiseScaler = 0.19;
y0=double(rand(2,1)*0.1); % y0 is the initial conditions. Here randomly generated.
Y = y0; % assign initial conditions to Y

% Byte 1: bits 0-7:     LFP Data
% Byte 2: bits 8-15:    not used
% Byte 3: bits 0-7:     Algorithm values
% Byte 4: bits 8-11:    Algorithm values (cont)
% Byte 4: bits 12-15:   Phase condition
% Byte 5: bits 0-7:     Time
% Byte 5: bits 8-9:     Time (cont)
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

while 1 % while true, infinite loop :O 
    

        dPydt    =(-Y(1)     + Sigm(params.a*Y(1)      - params.b*Y(2)   + params.P, 4,1))./params.taux;
        dInhdt   =(-Y(2)    + Sigm(params.c*Y(1)      - params.d*Y(2)    + params.Q, 4,1))./params.tauy;
        % NB: Sigm is a function (made by Yujiang) taking x, threshold, steepness. Make sure it is not
        % overshadowed by the JanRit sigm function.
       
        %Y(:,i+1) = Y(:,i) + h*[dPydt;dInhdt];
        Y = Y + params.h*[dPydt;dInhdt] +  randn(2,1).*sqrt(params.h).*params.noiseScaler;
        signal =  ((0.5*Y(2)-0.4*Y(1))*100)+127.5; % Need to center between 0 and 255
        
        % get current time
        h = datestr(now,'HH');
        m = datestr(now,'MM');
        %disp(signal)
        fwrite(fid,[signal,0,alg1,alg2,phase,str2num(h),str2num(m),gain,Algo,onoff]);
        fwrite(fid2,[signal,0,alg1,alg2,phase,str2num(h),str2num(m),gain,Algo,onoff]);

        fileprops = dir('incoming.bin');
        if fileprops.bytes > inputBufferSize % When we hit the input buffer size the GUI expects
            fclose(fid);
            fid = fopen('incoming.bin','w'); % Open file to write to, clearing the contents
            disp('data packet full')
        end
        pause(0.1) % don't want to generate too much too fast. Pause for 1 second.
    
end



function S = Sigm(xi,th,s)
        S=1./(1+exp(-s.*(xi-th)));
end


