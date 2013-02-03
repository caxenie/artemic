%%
% Aplicatie SLAM offline pt ARTEMIC
%
% Functie care returneaza pozitiile posibile
%%
function poses = pose_generator(~)
poses = [0 0;-1 -1;1 1;1 -1;-1 1;0 -1;0 1;-1 0;1 0];
return
end