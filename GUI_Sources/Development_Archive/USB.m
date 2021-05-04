clear;
clc;
close all;

% Constants 
start_sending = 1;
stop_sending = 2;

% Number of sine waves to be transmitted and received. Range 1-10
nof_sine_waves = 10;

% Check if input is valid
if (nof_sine_waves > 10)
    nof_sine_waves = 10;
elseif(nof_sine_waves < 1)
    nof_sine_waves = 1;
end

% Close any ports that are open
delete(instrfind);

% Serial communication settings
Baud_Rate = 115200;
Data_Bits = 8;
Stop_Bits = 1;
Parity = 'none';
inputBufferSize = nof_sine_waves*200;
figure;
% Setup a serial port and connect to it
% The appropriate port name ('COM14' in this case) should be provided
%sprt = serialportlist;
s = serialport('ttyACM0',Baud_Rate,'DataBits',Data_Bits,'Parity',Parity,'StopBits',Stop_Bits);
while(1)

% Ask the microcontroller to start sending data
write(s, start_sending, 'uint8');

% Wait until enough data has been received
while(s.NumBytesAvailable < inputBufferSize) 
end

% Read the input buffer from the microcontroller
data = read(s, inputBufferSize, 'uint8');

data = data/255*3.3;

% Ask the microcontroller to stop sending data
% write(s, stop_sending, 'uint8');

% Plot data

plot(data);
title('Data received over UART');
xlabel('Data points');
ylabel('Value');

end

% Close any ports that are open
delete(instrfind);