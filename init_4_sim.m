%initial values
% t_init = 0;
t_init = 0;
t_step = 1;
t_stop = 16500;
% sug_init = 751.64;
sug_init = 1011.832;
sug_current = sug_init;
% sug_current = 477.34;
volume = 25;
% temperature=296;
temp = 296;
% temp = 298.15;
yeast_gram =11;

t_cool = 293.15;

set_param("test_brewery", "StartTime", num2str(t_init));
set_param('test_brewery','FixedStep', num2str(t_step));
set_param('test_brewery','StopTime',num2str(t_stop))