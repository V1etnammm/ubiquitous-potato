#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
    enable = 1;
    counter = 0;
    speed = 0;
	speed_in_rad = 0;
    
    fb_motor.dt=0.01;
    fb_motor.ke=2.65;
    fb_motor.Tm=0.05;
    
    fb_motor2.dt = 0.01;
    fb_motor2.ke = 2.65;
    fb_motor2.Tm = 0.05;
    
    fb_controller.dt=0.01;
    fb_controller.k_p = (fb_motor.ke* fb_motor.Tm) / 0.02;
    fb_controller.k_i = fb_motor.ke / 0.02;
    fb_controller.max_abs_value=24;
}

void _CYCLIC ProgramCyclic(void)
{
    REAL PI = 3.141592653589793;
    REAL desired_w = speed * 2.0 * PI / 60.0;
	speed_in_rad = desired_w;

    if (enable == 1){
        counter += 1;
        if ((counter >= 500 ) && (counter <= 1000)) speed = 70;
        else speed = 0;
    }
    else speed = 0;
    
    fb_controller.e = desired_w - fb_motor.w;
    FB_Regulator(&fb_controller);
	fb_motor.u = fb_controller.u;
    
    fb_motor2.u = desired_w * fb_motor2.ke;
    
    FB_Motor(&fb_motor);
    FB_Motor(&fb_motor2);
    
}

void _EXIT ProgramExit(void)
{

}
