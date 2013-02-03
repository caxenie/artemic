%%
% Aplicatie SLAM offline pt ARTEMIC (pentru demo algoritm)
%
% Functie de salvare a valorilor citite de la sonare
%%
function save_readings(r)
% initializare robot pentru testare algoritm
robotInitSim(r)
% operare asincrona a robotului
runAsync(r)
try
    % algoritm de explorare aleatorie a mediului 
    wander(r,300);
    % se salveaza informatia din mediu 
    save_map(r,180/0.25);  % timpul de executie "sec"/"pas esantionare"
catch
    % finalizare
    lasterr
    setVel2(r, 0, 0);
    shutdown(r);
    return;
end
% opreste robotul 
stopRunning(r);
% intrerupe conexiunea cu simulatorul
shutdown(r);