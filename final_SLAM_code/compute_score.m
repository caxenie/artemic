%%
% Aplicatie SLAM offline pt ARTEMIC
%
% Functia de estimare a potrivirii hartii pe termen scurt cu harta pe
% termen lung; scorul reda o dimensionare a rezultatului comparatiei
%%
function score = compute_score(world, model, offset)
    world = world(offset(1)+1:offset(1)+length(model),...
                  offset(2)+1:offset(2)+length(model));
    if(isempty(find((world~=.5).*(model~=.5), 1)))
        score = 0;
        return;
    end
    score = sum(sum(abs(world - model)));
end
