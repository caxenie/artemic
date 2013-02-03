% identificarea modelului MCC1 a robotului

% 
% Opening System Identification Tool ....... done. 
% Process model with transfer function                      
%            K                                              
% G(s) = ----------                                         
%         1+Tp1*s                                           
% 
% with   K = 1.1004+-0.0052921
%      Tp1 = 0.46973+-0.025221
%                                                           
% Estimated using PEM from data set right motor                  
% Loss function 0.0476646 and FPE 0.0484334                 
% Created:       28-Mar-2009 13:53:08                       
% Last modified: 28-Mar-2009 13:53:08 

K = 1.1004;
Tp1 = 0.46973;
nump = [K/Tp1];
denp = [1 1/Tp1];
% stabilirea performantelor ctrl PI + proces
a = 1/Tp1;
b = K/Tp1;
zeta = 1;
tr = 0.5;
omega = 4/(zeta*tr);
% parametrii controlerului PI
disp('-----------------------')
Kp = (2*zeta*omega-a)/b
Ki = omega^2/b
% simulare in bucla inchisa
Ho=series(tf([Kp Ki],[1 0]),tf([K],[Tp1 1]));
%Ho = tf(b*[Kp Ki],[1 Kp*b+a Ki*b]);
figure(3);

step(feedback(Ho,1));
title('Raspunsul motorului dreapta (1)');
%hold on
%step(tf([K],[Tp1 1]));
grid;
disp('parametrii controlerului pentru motorul 1 sunt');
Kp
Ki

% identificarea modelului MCC2 a robotului
% 
% Process model with transfer function                         
%            K                                                 
% G(s) = ----------                                            
%         1+Tp1*s                                              
% 
% with   K = 0.87966+-9.8855e-005
%      Tp1 = 0.34849+-0.017543
%                                                              
% Estimated using PEM from data set left motor                 
% Loss function 0.0271026 and FPE 0.0275398                    
% Created:       28-Mar-2009 13:51:32                          
% Last modified: 28-Mar-2009 13:51:37

K = 0.87966;
Tp1 = 0.34849;
nump = [K/Tp1];
denp = [1 1/Tp1];
% stabilirea performantelor ctrl PI + proces
a = 1/Tp1;
b = K/Tp1;

% parametrii controlerului PI
Kp = (2*zeta*omega-a)/b;
Ki = omega^2/b;
% simulare in bucla inchisa
Ho=series(tf([Kp Ki],[1 0]),tf([K],[Tp1 1]));
%Ho = tf(b*[Kp Ki],[1 Kp*b+a Ki*b]);
figure(4);
step(feedback(Ho,1));
title('Raspunsul motorului stanga (2)');
%hold on
%step(tf([K],[Tp1 1]));
grid;
disp('parametrii controlerului pentru motorul 2 sunt');
Kp
Ki

