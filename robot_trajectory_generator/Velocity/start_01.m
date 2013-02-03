clear all
clear
clc
  global kkkk xxx yyy teta P v_final

%        xxx = [0, 2, 2.5, 2];
%        yyy = [0, 0, 0.5, 1];
%        teta = [0, 0, pi/2, pi];

% traiectorie complexa
% % 
%        xxx = [0, 2, 4, 6, 8, 10, 12, 10, 8, 10, 14];
%        yyy = [0, 0, 2, 4, 2, 0, 2, 4, 2, 0, 0];
%        teta = [0, 0, pi/2, 0, -pi/2, 0, pi/2, pi, -pi/2, 0, 0];
%        

% % traiectorie complexa 2
% % 
%        xxx = [0, 1, 2, 3, 4, 5, 6, 5, 4, 5, 7];
%        yyy = [0, 0, 1, 2, 1, 0, 1, 2, 1, 0, 0];
%        teta = [0, 0, pi/2, 0, -pi/2, 0, pi/2, pi, -pi/2, 0, 0];
       
       % traiectorie complexa 3 OK pt demo !!!
% 
%        xxx = [0, 0.5, 1, 1.5, 2, 2.5, 3, 2.5, 2, 2.5, 3.5];
%        yyy = [0, 0, 0.5, 1, 0.5, 0, 0.5, 1, 0.5, 0, 0];
%        teta = [0, 0, pi/2, 0, -pi/2, 0, pi/2, pi, -pi/2, 0, 0];
       
       % pentru demo 
%        
%        xxx = [0, 0.5, 1, 1.5, 2, 2.5, 3, 2.5, 2, 2.5, 3,3.5, 4.0, 3.5,1.5,1,0.5,0];
%        yyy = [0, 0, 0.5, 1, 0.5, 0, 0.5, 1, 0.5, 0,0,0,0.5,1,1,1,0.5,0];
%        teta = [0, 0, pi/2, 0, -pi/2, 0, pi/2, pi, -pi/2, 0, 0,0, pi/2,pi, pi,pi,-pi/2,pi];

    % pentru demo timisoara TM current circuit
%        xxx = [0, 0.5, 1, 1.5, 2, 2.5, 3, 2.5, 2, 2.5, 3,3.5, 4.0, 3.5,3.0,2.5,2.0,1.5,1.0,0.5,0.0,0.0,0.0,0.0];
%        yyy = [0, 0, 0.5, 1, 0.5, 0, 0.5, 1, 0.5, 0,0,0,0.5,1,1,1,1,1.5,2.0,2.0,1.5,1,0.5,0.0];
%        teta = [0, 0, pi/2, 0, -pi/2, 0, pi/2, pi, -pi/2, 0, 0,0, pi/2,pi,pi,pi,pi,pi/2,pi,pi,-pi/2,-pi/2,-pi/2,pi/2];
%        
       % demo TM alternativ simplu fara circuit
%        
%         xxx = [0, 0.5, 1, 1.5, 2, 2.5, 3, 2.5, 2, 2.5, 3,3.5, 4.0];
%        yyy = [0, 0, 0.5, 1, 0.5, 0, 0.5, 1, 0.5, 0,0,0,0];
%        teta = [0, 0, pi/2, 0, -pi/2, 0, pi/2, pi, -pi/2, 0, 0,0,0];

 % traiectorie linie dreapta
 
%         xxx = [0, 2];
%         yyy = [0, 0];
%         teta =[0, 0];
%        
  % traiectorie cerc 1 _O
%   
%         xxx = [3.9, 4, 4.75, 4, 3.25, 4];
%         yyy = [0, 0, 0.75, 1.5, 0.75, 0];
%         teta = [0, 0, pi/2, pi, -pi/2, 0];
        
% traiectorie cerc 2 _O_
  
%         xxx = [3.9, 4, 4.75, 4, 3.25, 4, 4.2];
%         yyy = [0, 0, 0.75, 1.5, 0.75, 0, 0];
%         teta = [0, 0, pi/2, pi, -pi/2, 0, 0];

  % traiectorie semicerc
  
%          xxx = [0,0.75,0];
%         yyy = [0,0.75,1.5];
%         teta = [0, pi/2, pi];
%         
        % traiectorie pentru demo
       
%         xxx = [0, 0.9, 1, 1.75, 1  , 0.25, 1 , 3, 3.75, 3 ,   0];
%         yyy = [0, 0,  0, 0.75, 1.5, 0.75, 0,0, 0.75, 1.5, 1.5];
%         teta =[0, 0,  0, pi/2, pi, -pi/2, 0,0, pi/2, pi ,  pi];

% traiectorie simpla

%     xxx= [0, 2, 2.5, 2.5];
%     yyy = [0, 0, 0.5, 1.5];
%     teta = [0, 0, pi/2, pi/2];
%   

% traiectorie demo SLAM offline - coridor corp Y

xxx = [0, 0, 0, 0, 0, 6, 12, 18, 22, 26, 26.6, 0, 0, 0, 0, 0];
yyy = [0, 4, 8, 12, 14.4, 0, 0, 0, 0, 0, 0, 14.4, 12, 8, 4, 0];
teta = [0, 0, 0, 0, pi/2, 0, 0, 0, 0, 0, 0, pi/2, 0, 0, 0, 0];

P = [xxx;yyy];

kkkk=[zeros(2,length(P))];
v_final=[zeros(1,length(P))]

algoritm_feb_sep_01(v_final);
