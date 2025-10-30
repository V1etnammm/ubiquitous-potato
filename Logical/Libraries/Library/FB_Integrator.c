
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif
/* INTEGRATOR */
void FB_Integrator(struct FB_Integrator* inst)
{
    inst->dt= 0.01;
 
    inst->out = inst->dt * inst->in + inst->state;
    inst->state = inst->out;
}
