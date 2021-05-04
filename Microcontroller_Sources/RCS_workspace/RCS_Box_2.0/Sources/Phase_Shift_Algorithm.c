/* ###################################################################
**     Filename    : Phase_Shift_Algorithm.c
**     Project     : RCS_Box_2.0
**     Processor   : MK22FN512VDC12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-01-27, 16:48, # CodeGen: 0
**     Abstract    :
**         	Contains function definitions related to the phase shift
**         	algorithms.
** ###################################################################*/

#include "Phase_Shift_Algorithm.h"
#include "arm_math.h"

enum algo_version algorithm = ORIGINAL;

float taps[KERNELS][KERNEL_SIZE] = {0};
unsigned int conv_reg[KERNEL_SIZE] = {0};
unsigned short index = 0;

float fai = 0.0f;
float alpha = 1.25f;
unsigned short threshold = 0*10;
unsigned short phase = 0;
unsigned short f = 10;
unsigned short offset = 0;

float convIntFloat(unsigned int i)
{
	float f;

	f = i/255.0f * 0.255f;

	f -= 0.127f;

	return f;
}

unsigned int convFloatInt(float f)
{
	unsigned int i;

	i = f/0.255f*255;

	return i;
}

void init_kernel(void)
{
	unsigned char taps_index;

	float total = 0.0f;

	for(taps_index = 0; taps_index < KERNELS; taps_index++)
	{
		fai = taps_index*45.0f/180.0f;
		fai = fai*3.14;

		total = 0.0f;

		for(index = 0; index < KERNEL_SIZE; index++)
		{
			taps[taps_index][index] = exp(-alpha*f*(0.002*index))*cos(2*3.14*f*index*0.002-fai);
			total += taps[taps_index][index];
		}

		total = total / 120.0f;

		for(index = 0; index < KERNEL_SIZE; index++)
		{
			taps[taps_index][index] -= total;
		}
	}
}

void phase_shift(unsigned int *rec_reg_ptr, unsigned int *stim_reg_ptr)
{
	float rconv = 0.0f;
	unsigned short j, i;
	unsigned char scale = 1;

	*rec_reg_ptr = *rec_reg_ptr - offset;

	conv_reg[KERNEL_SIZE - 1] = *rec_reg_ptr;

	for(j = 0; j < KERNEL_SIZE; j++)                    // * the P-index value decides filter taps
	{
		rconv = taps[0][j] * convIntFloat(conv_reg[KERNEL_SIZE - 1 - j]) + rconv;
	}

	*stim_reg_ptr = convFloatInt(rconv) * scale;             // Outputs scaling to fit DAC

	if(*stim_reg_ptr > threshold)                          	// Set intensity process
	{
		if (algorithm == SET_INTENSITY)
			*stim_reg_ptr = scale * 400;                     // Set output as the maximum value

		if (*stim_reg_ptr >= 4000)
		{
			*stim_reg_ptr = 4000;
		}
	}
	else
	{
		*stim_reg_ptr = 0;
	}

	for(i = 0; i < (KERNEL_SIZE - 1); i++)
	{
		conv_reg[i] = conv_reg[i + 1];
	}
}
