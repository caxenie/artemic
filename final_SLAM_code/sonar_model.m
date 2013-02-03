%%
% Aplicatie SLAM offline pt ARTEMIC
%
% Functie care implementeaza modelul sonarelor
%%
function model = sonar_model(sonars_readings, heading)
    % jumatate din unghiul de deschidere a conului
    beta = 7;
    % range maxim sonar
    range = 26; 
    % scare de reprezentare a hartii
    scale = 35;
    % toleranta in reprezentarea hartii
    tolerance = 1;
    % valoare utilizata pentru definirea starii initiale
    percent_occupied = 0.98;
    % dimensiunea modelului sonarului pentru harta
    % pe termen scurt
    model_size = 150;
    % initializarea modelului
    model = zeros(model_size, model_size);
    model(:,:) = NaN;
    % corectie heading robot
    a = -heading/180*pi;
    T = [cos(a) -sin(a);sin(a) cos(a)];
   % pozitionarea sonarelor pe X Y si orientare
   % pe partea frontala a robotului
     sonars_setup=[  69      136     90
                     114      119     50
                     148      78      30  
                     166      27      10
                     166     -27     -10
                     148     -78     -30
                     114    -119     -50
                      69    -136     -90 ];
     % se elimina senzorii out of range
     tmp = [];
     tmp2 = [];
     for si=1:length(sonars_setup)
         % distanta maxima de activitate a sonarului
         % in reprezentarea hartii
         if(sonars_readings(si)<2000) 
            tmp = [tmp; sonars_setup(si,:)];
            tmp2 = [tmp2; sonars_readings(si)];
         end
     end
     % verificari suplimentare de dimensiune 
     if(size(tmp,1)==0)
         return
     end
     % formarea modelului sonarului
     sonars_setup = tmp;
     sonars_readings = tmp2./scale;
     sonars_setup(:,1:2) = sonars_setup(:,1:2)*T./scale;
     sonars_setup(:,3) = sonars_setup(:,3)+heading;
     for yi=1:model_size
         for xi=1:model_size
             for si=1:size(sonars_setup, 1)
                 % calcul pozitie
                 x = xi-model_size/2;
                 y = yi-model_size/2;
                 r = ((x-sonars_setup(si,1))^2 + (y-sonars_setup(si,2))^2)^0.5;
                 b = abs(atan2(y-sonars_setup(si,2), x-sonars_setup(si,1))/pi*180-sonars_setup(si,3));
                 while(b>180)
                     b = abs(b-360);
                 end
                 % verificarile dimensiunilor pentru afisare
                 if(b>beta || r>sonars_readings(si)+tolerance/2)
                     continue
                 end
                 % calculul probabilitatilor ca o celula a matricii de 
                 % ocupare este ocupata tinand cont de citirea sonarului
                 if(abs(r-sonars_readings(si))<=tolerance)
                     probability = ((((range - r) / range) + ((beta - b)/beta))/2)*percent_occupied;
                     probability = .5*probability+.5;
                 else
                     probability = (((range - r)/range)+((beta - b)/beta))/2;
                     probability = 1-(.5*probability+.5);
                 end
                 % formeaza modelul sonarului
                 model(xi,yi)=probability;
             end
         end
     end
end

                     