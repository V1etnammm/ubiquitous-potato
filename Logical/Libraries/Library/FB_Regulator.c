
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif
/* REGULATOR */
void FB_Regulator(struct FB_Regulator* inst)
{
    REAL p_part = inst->e * inst->k_p;
    
    REAL i_part = inst->e * inst->k_i;
    
    inst->integrator.in = i_part;
    
    FB_Integrator(&inst->integrator);
    
    i_part = inst->integrator.out;
    
    REAL total_output = p_part + i_part;
    
    if (total_output > inst->max_abs_value)
    {
        inst->u = inst->max_abs_value;
        inst->integrator.out = inst->max_abs_value - p_part;
        
    } else if (total_output < -inst->max_abs_value)
    {
        inst->u = -inst->max_abs_value;
        inst->integrator.out = -inst->max_abs_value - p_part;
    } else
    {
        inst->u = total_output;
        
    }
    inst->iyOld = i_part;
}
