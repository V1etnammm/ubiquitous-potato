
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif
/* MOTOR */
void FB_Motor(struct FB_Motor* inst)
{
    REAL b1 = inst->u * (1/inst->ke) - inst->w;
    REAL b2 = b1/ inst->Tm;
    
    inst->motor_integrator.in = b2;
    FB_Integrator(&inst->motor_integrator);
    
    inst->w = inst->motor_integrator.out;
    
    inst->sensor_integrator.in = inst->w;
    FB_Integrator(&inst->sensor_integrator);
    
    inst->phi = inst->sensor_integrator.out ;
    
    
}
