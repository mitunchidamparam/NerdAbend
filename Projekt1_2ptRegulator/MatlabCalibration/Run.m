
% close all; clear all; clc

Data = importfile('Mappe2.xlsx');


% Mittelwerte Bereichnen

y = Data(:,1);

[l,~] = size(Data);


for(i=1:l)
   
    x(i) = mean(Data(i,2:11));
    
    
end



[fit, ~] = createFit(x,y);

m =fit.p1;
b = fit.p2;

