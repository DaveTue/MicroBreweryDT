%initial values
% t_init = 0;
t_init = 0;
t_step = 1;
t_stop = 16500;
% sug_init = 751.64;
sug_init = 1011.832; %mol/L
sug_current = sug_init;
% sug_current = 477.34;
volume = 25; %L
% temperature=296;
temp = 296;
% temp = 298.15;
yeast_gram =11;

t_cool = 287.15;%K
T_amb = 295.15;%K

delta_t = 1.0; %[min]
rho = 1000;%kg/m^3
%t_step = 1;
Cp = 3.8;%kJ/kgK 
Vol = volume;% m^3
delta_H = -65;% kJ/mol
h = 678.07;% W/m2K 
A = 0.31;% m^2
h_amb = 42.93;% W/m2K 
A_amb = 0.754;% m^2
T_k0=298.15;%

set_param("test_brewery", "StartTime", num2str(t_init));
set_param('test_brewery','FixedStep', num2str(t_step));
set_param('test_brewery','StopTime',num2str(t_stop))