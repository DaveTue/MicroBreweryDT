% t_init = 0;
t_init = 0;
t_step = 1;
t_stop = 16500;
% sug_init = 751.64;
sug_init = 1011.832;
sug_current = sug_init;
% sug_current = 477.34;
volume = 25;
temp = 296;
% temp = 298.15;
yeast_gram =11;

%sigma_model = 1648.125;
%sigma_sensor= 34.20144;
%c_meassure = 968.4678;

%open_system("Fermentation");

set_param("FermentationV3", "StartTime", num2str(t_init));
set_param('FermentationV3','FixedStep', num2str(t_step));
set_param('FermentationV3','StopTime',num2str(t_stop))

sim("FermentationV3");