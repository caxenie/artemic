%%
% l = 14.8
% L = 26.6
% d = 2.7
% Aplicatie SLAM offline pt ARTEMIC
%
% Programul principal de simulare a SLAM
%%
% elibereaza mediul 
clear all
clc
% valori scalare pentru afisare
scale = 50; % 20 pt camera | 50 pt hol
world_size =800; % 600 pt camera | 800 pt hol
world=zeros(world_size,world_size);
world(:,:)=0.5;
% grad suprapunere harti
overlap=0;
% ajustare heading (a se tine cont de pozitia de start)
degrees=[0 0 0 0 0 0 0];
% incarca fisierul cu datele de la senzori de pe disc
load robot_state saved*;
% alocarea variabilelor pentru valorile citite
readings=saved_readings;
pose=saved_pose;
% offset harti
off=1;
% prealocare vector pozitie
pos=[];

while(off<length(readings)-overlap)
    % initializari
    stm_size=0;
    num=0;
    % numarul de esantioane citite de le sonare (min45)
    while(num<45 && off+stm_size<length(readings))
        num=num+sum(readings(off+stm_size,:)<6000); 
        stm_size = stm_size+1;
    end
    % prealocari
    rpos=[];
    rstm=[];
    rposes=[];
    rscore=[];
    rdegrees=[];
    for k=1:length(degrees)
        % porneste cu o harta initiala goala
        stm=zeros(world_size, world_size);
        % niciun punct nu e necunoscut
        stm(:,:)=0.5;
        for j=1:stm_size
            % calculul pozitiei
            pos=ceil((pose(off+j,:)./scale)+(world_size./2)-40);
            % genereaza modelul sonarului
            model=sonar_model(readings(off+j,:),pose(off+j,3)+degrees(k));
            % adauga in harta temporara (pe termen scurt)
            stm=bayes_fusion(stm, model, pos);
        end
        % limita impusa afisare 
        margin= 5;%15;
        pos=ceil((pose(off+1,:)./scale)+(world_size./2)-40-margin);
        % formeaza harta pe termen scurt
        stm=stm(pos(1)+1:pos(1)+length(model)+2*margin, pos(2)+1:pos(2)+length(model)+2*margin);
        % functia pose_generator() returneaza o matrice a posibilelor
        % pozitii pe care le-ar putea avea robotul, in functie depozitia
        % actuala
        % functia compute_score() pentru a vedea in care din aceste pozitii se 
        % integreaza cel mai bine
        poses=pose_generator(pose(off+1,:));
        for(l=1:size(poses,1))
            pos2=pos(1:2)+poses(1,:);
            rscore=[rscore compute_score(world, stm, pos2)];
            rpos=[rpos;pos2];
            rstm(:,:,length(rscore)) = stm;
            rposes=[rposes;poses(1,:)];
            rdegrees=[rdegrees degrees(k)];
        end
    end
    % functia MIN returneaza locatia cea mai probabila
    [score, idx]=min(rscore);
    stm=rstm(:,:,idx);
    pos=rpos(idx,:);
    % inregistrarea (validarea) hartii porvizorii in (cu) harta globala 
    world=bayes_fusion(world, stm, pos);
    left=off+stm_size-overlap:length(readings);
    a=-rdegrees(idx)/180*pi;
    T=[cos(a) -sin(a);sin(a) cos(a)];
    pos=[pose(left,1)-pose(off+1,1) pose(left,2)-pose(off+1,2)];
    pos=pos*T;
    pose(left,1:2)=[pos(:,1)+pose(off+1,1) pos(:,2)+pose(off+1,2)];
    pose(left,1) = pose(left,1)+(scale.*rposes(idx,1));
    pose(left,2) = pose(left,2)+(scale.*rposes(idx,2));
    pose(left,3) = pose(left,3)+rdegrees(idx);
    % afisarea hartii temporare (pe termen scurt, in timpul generarii)
    figure(1);
    colormap(gray);
    h = imrotate(world, 180);
    imagesc(h, [0 1]);
    drawnow;
    zoom on
    zoom(1.5)
    off=off+stm_size-overlap;
end
% harta globala ajustata
figure(2);
colormap(gray);
world(world<.7)=0;
world(world>=.7)=1;
h = imrotate(world, 180);
imagesc(h, [0 1]);
zoom on
zoom(1.5)

