
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
    enable = 1;
    counter = 0;
    speed = 0;
    
    fb_motor.dt=0.01;
    fb_motor.ke=2.65;
    fb_motor.Tm=0.0246;
    
    fb_motor2.dt = 0.01;
    fb_motor2.ke = 5;
    fb_motor2.Tm = 0.05;
    
    fb_controller.dt=0.02;
    fb_controller.k_p = (fb_motor.ke* fb_motor.Tm) / 0.005;
    fb_controller.k_i = fb_motor.ke / 0.005;
    fb_controller.max_abs_value=24;
}

void _CYCLIC ProgramCyclic(void)
{
    if (enable == 1){
        counter += 1;
        if ((counter >= 500 ) && (counter <= 1000)) speed = 70;
        else speed = 0;
    }
    else speed = 0;
    fb_controller.e = speed - fb_motor.w;
    fb_motor2.u = speed * fb_motor2.ke;
    fb_motor.u = (speed * (2 * 3.141592653589897) / 60 ) * fb_motor.ke;
    FB_Regulator(&fb_controller);
    FB_Motor(&fb_motor);
    FB_Motor(&fb_motor2);
    
}

void _EXIT ProgramExit(void)
{

}

