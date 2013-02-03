% loturi de date de la robot pentru studiul dependentei PWM - omega
load values_150.txt
load values_175.txt
load values_200.txt
load values_225.txt
load values_250.txt
load values_275.txt
load values_300.txt
load values_325.txt
load values_350.txt
load values_375.txt
load values_400.txt
load values_425.txt
load values_450.txt
load values_475.txt
load values_500.txt

% trasarea caracteristicii 
v15L = [mean(values_150(:,1:1)),mean(values_150(:,2:2))];
v15R = [mean(values_150(:,3:3)),mean(values_150(:,4:4))];
v175L = [mean(values_175(:,1:1)),mean(values_175(:,2:2))];
v175R = [mean(values_175(:,3:3)),mean(values_175(:,4:4))];
v20L = [mean(values_200(:,1:1)),mean(values_200(:,2:2))];
v20R = [mean(values_200(:,3:3)),mean(values_200(:,4:4))];
v225L = [mean(values_225(:,1:1)),mean(values_225(:,2:2))];
v225R = [mean(values_225(:,3:3)),mean(values_225(:,4:4))];
v250L = [mean(values_250(:,1:1)),mean(values_250(:,2:2))];
v250R = [mean(values_250(:,3:3)),mean(values_250(:,4:4))];
v275L = [mean(values_275(:,1:1)),mean(values_275(:,2:2))];
v275R = [mean(values_275(:,3:3)),mean(values_275(:,4:4))];
v30L = [mean(values_300(:,1:1)),mean(values_300(:,2:2))];
v30R = [mean(values_300(:,3:3)),mean(values_300(:,4:4))];
v325L = [mean(values_325(:,1:1)),mean(values_325(:,2:2))];
v325R = [mean(values_325(:,3:3)),mean(values_325(:,4:4))];
v350L = [mean(values_350(:,1:1)),mean(values_350(:,2:2))];
v350R = [mean(values_350(:,3:3)),mean(values_350(:,4:4))];
v375L = [mean(values_375(:,1:1)),mean(values_375(:,2:2))];
v375R = [mean(values_375(:,3:3)),mean(values_375(:,4:4))];
v400L = [mean(values_400(:,1:1)),mean(values_400(:,2:2))];
v400R = [mean(values_400(:,3:3)),mean(values_400(:,4:4))];
v425L = [mean(values_425(:,1:1)),mean(values_425(:,2:2))];
v425R = [mean(values_425(:,3:3)),mean(values_425(:,4:4))];
v450L = [mean(values_450(:,1:1)),mean(values_450(:,2:2))];
v450R = [mean(values_450(:,3:3)),mean(values_450(:,4:4))];
v475L = [mean(values_475(:,1:1)),mean(values_475(:,2:2))];
v475R = [mean(values_475(:,3:3)),mean(values_475(:,4:4))];
v500L = [mean(values_500(:,1:1)),mean(values_500(:,2:2))];
v500R = [mean(values_500(:,3:3)),mean(values_500(:,4:4))];

pwm_left = [v15L(:,1),v175L(:,1),v20L(:,1),v225L(:,1),v250L(:,1),v275L(:,1),v30L(:,1),v325L(:,1),v350L(:,1),v375L(:,1),v400L(:,1),v425L(:,1),v450L(:,1),v475L(:,1),v500L(:,1)];
omega_left = [v15L(:,2),v175L(:,2),v20L(:,2),v225L(:,2),v250L(:,2),v275L(:,2),v30L(:,2),v325L(:,2),v350L(:,2),v375L(:,2),v400L(:,2),v425L(:,2),v450L(:,2),v475L(:,2),v500L(:,2)];

figure(1);
plot(pwm_left,omega_left);
title('robot roata stanga');
xlabel('tensiunea pt generare PWM [v]');
ylabel('viteza unghiulara [rad/s]');
grid;

pwm_right = [v15R(:,1),v175R(:,1),v20R(:,1),v225R(:,1),v250R(:,1),v275R(:,1),v30R(:,1),v325R(:,1),v350R(:,1),v375R(:,1),v400R(:,1),v425R(:,1),v450R(:,1),v475R(:,1),v500R(:,1)];
omega_right = [v15R(:,2),v175R(:,2),v20R(:,2),v225R(:,2),v250R(:,2),v275R(:,2),v30R(:,2),v325R(:,2),v350R(:,2),v375R(:,2),v400R(:,2),v425R(:,2),v450R(:,2),v475R(:,2),v500R(:,2)];
figure(2);
plot(pwm_right,omega_right)
title('robot roata dreapta');
xlabel('tensiunea pt generare PWM [v]');
ylabel('viteza unghiulara [rad/s]');
grid;

% get dependency se apeleaza pentru a obtine dependenta pe fiecare interval
% considerat la obtinerea caracteristicii statice
disp('dependenta pentru motorul stanga al robotului')
get_dependency(omega_left,pwm_left)
disp('dependenta pentru motorul dreapta al robotului')
get_dependency(omega_right,pwm_right)