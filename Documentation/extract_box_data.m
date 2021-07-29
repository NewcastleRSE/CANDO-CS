
function extract_box_data(filename,savename)
% This function is designed to take a filename containing .mat files that
% have been produced by the RCS box and GUI, version 19 or above. This
% function will process the individual mat files and combine the data into
% the complete time series for the experiment. The function will then
% attempt to save the data under the user given savename argument, and
% produce a plot of the time series.
%
% filename and savename should be strings.
% FT March 2021

myFolder = filename;
filePattern = fullfile(myFolder, '*.mat');
matFiles = dir(filePattern);

lfp = [];
stim = [];
algOn = [];
gain = [];
intensity = [];
phase = [];
inds = [];
metadata = ["Connected Controller version","Connected Controller version",...
    "GUI Software version","year","month","day","hour","minute","second",...
    "serialport input","serialport input","baudrate","serialport out","serialport out",...
    "baudrate","Parameters","Project"];

[~, reindex] = sort( str2double( regexp( {matFiles.name}, '\s\d+', 'match', 'once' )));
matFiles = matFiles(reindex);

for k = 1:length(matFiles)
    
  baseFileName = matFiles(k).name;
  fullFileName = fullfile(myFolder, baseFileName);
  
  fprintf(1, 'Now reading %s\n', fullFileName);

  
  % catch the metadata!
  if contains(baseFileName,'metadata')
      
      meta = load(fullFileName);
      % we will want to load this seperately
      metadata = [metadata;meta.metadata];
  else

      matData(k) = load(fullFileName);
        
      data_lfp = matData(k).LFPData;
      lfp = [lfp, data_lfp];

      data_stim = matData(k).AlgValues;
      stim = [stim, data_stim];

      data_algOn = matData(k).Algorithm;
      algOn = [algOn, data_algOn];

      data_gain = matData(k).gain;
      gain = [gain, data_gain];

      data_intensity = matData(k).intensity;
      intensity = [intensity, data_intensity];

      data_phase = matData(k).phaseCondition;
      phase = [phase, data_phase];

      % this one is really just a sanity check, to make sure we have read the
      % files in the correct order:
      data_inds = matData(k).ind * ones(1,length(matData(k).LFPData));
      inds = [inds, data_inds];
  end
  
end


t = 1/500:1/500:1/500*length(lfp);

try 
    save(savename,'lfp','stim','phase','algOn','gain','intensity','inds','t','-v7.3')
catch
    warning('File failed to save, make sure you have space and an appropriate save name.')
end

figure;
title('Raw experimental results');
subplot(3,1,1);
plot(t,lfp);
ylabel('LFP data (V)'); % y-axis label

subplot(3,1,2);
plot(t, stim);
xlabel('time (s)'); % x-axis label
ylabel('LED output'); % y-axis label

subplot(3,1,3);
plot(t, phase);
xlabel('time (s)'); % x-axis label
ylabel('Phase condition'); % y-axis label

