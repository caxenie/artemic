%%
% Aplicatie SLAM offline pt ARTEMIC (pentru demo algoritm)
%
% Functie care salveaza harta (de fapt valorile pentru construirea hartii)
%%
function save_map(r,num_readings)
    for(i=1:num_readings)
        % secventierea citirilor
        pause(0.250);
        % informatia de pozitie
        saved_pose(i,:) = position(r);
        % informatia de la sonare
        saved_readings(i,:) = sonarSensorRange(r);
    end
    % fisierul salvat in simulator
    save robot_state saved*;
end