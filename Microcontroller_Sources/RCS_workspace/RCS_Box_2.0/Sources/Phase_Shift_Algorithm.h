/* ###################################################################
**     Filename    : Phase_Shift_Algorithm.h
**     Project     : RCS_Box_2.0
**     Processor   : MK22FN512VDC12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-01-27, 16:48, # CodeGen: 0
**     Abstract    :
**         	Contains function declarations related to the phase shift
**         	algorithms.
** ###################################################################*/

#ifndef __Phase_Shift_Algorithm_H
#define __Phase_Shift_Algorithm_H
/* MODULE Phase_Shift_Algorithm */

#define KERNEL_SIZE 120
#define KERNELS 8

enum algo_version
{
	ORIGINAL, SET_INTENSITY
};

void init_kernel(void);
float convIntFloat(unsigned int i);
unsigned int convFloatInt(float f);
void phase_shift(unsigned int *rec_reg_ptr, unsigned int *stim_reg_ptr);

/* END Phase_Shift_Algorithm */
#endif

