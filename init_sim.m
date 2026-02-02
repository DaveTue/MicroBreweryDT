t_init = 500;
sug_init = 1011;
volume = 25;
temp = 298.15;
yest_gram =11;
%open_system("Fermentation");

set_param("Fermentation", "StartTime", "t_init");

sim("Fermentation");