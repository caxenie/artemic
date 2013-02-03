% pentru extragerea caracteristicii liniarizate pe portiuni
function get_dependency(omega_vector,pwm_vector)
syms U w real;
len = length(omega_vector);
for i = 2:len
    U = pwm_vector(i-1)+((w-omega_vector(i-1))/(omega_vector(i)-omega_vector(i-1)))*(pwm_vector(i)-pwm_vector(i-1));
    i
    Upwm = vpa(U)
end;

