/* ###################################################################
**     Filename    : Phase_Shift_Algorithm.c
**     Project     : RCS_Box_2.1
**     Processor   : MK22FN512VDC12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-01-29, 16:48, # CodeGen: 0
**     Abstract    :
**         	Contains function definitions related to the phase shift
**         	algorithms.
** ###################################################################*/

#include "Phase_Shift_Algorithm.h"
#include "arm_math.h"

unsigned char algorithm = ORIGINAL;

float kernel[PHASE_CONDS][NO_OF_TAPS] = {0.0f};
float conv_buf[NO_OF_TAPS] = {0.0f};

float fai = 0.0f;
float k = 1.25f;
unsigned short threshold = 0*10;
unsigned char phase_cond = 0;
unsigned short f = 10;

/*
** ===================================================================
** float convIntFloat(unsigned short i)
** ===================================================================
** Description: Converts an unsigned short (16-bits) value to a float.
** 				The value is then scaled between -1.0 to 1.0f
**
** Inputs:	(unsigned short i): variable to be converted
**
** Outputs: (float f): result from the conversion
/* ===================================================================*/
float convIntFloat(unsigned short i)
{
	float f;			// Result of the conversion

	f = i/255.0f*2.0f; 	// Scale the integer value from 0.0f to 2.0f
	f -= 1.0f;			// Shift the value between -1.0f to 1.0f

	return f;			// Return the result
}


/*
** ===================================================================
** unsigned short convFloatInt(float f)
** ===================================================================
** Description: Converts a float to a short (16-bit) value
**
** Inputs:	(float f): variable to be converted
**
** Outputs: (unsigned short i): result from the conversion
/* ===================================================================*/
unsigned short convFloatInt(float f)
{
	unsigned short i; 	// Result of the conversion

	/*
	 * The value is scaled up to 3.3V. This can be achieved only when the
	 * input signal covers the full range (0-3.3V)
	 */
	i = f*4095;

	return i;			// Return the result
}

/*
** ===================================================================
** void init_kernel(void)
** ===================================================================
** Description: Define the kernels for each of the phase conditions
** 				(0-7). The phase value for each of the conditions can
** 				be obtained as follows: phase = phase_cond*45 (0-315,
** 				with a 45 degree step).
**
** Inputs:	None
**
** Outputs: None
/* ===================================================================*/
void init_kernel(void)
{
	unsigned short taps_index = 0;

	float total_e = 0.0f, max = 0.0f, kernel_exp = 0.0f, cosine = 0.0f;

	/*
	 * Define the kernels for each of the phase conditions (0-7).
	 * The phase value for each of the conditions can be obtained as
	 * follows: phase = phase_cond*45 (0-315, with a 45 degree step).
	 */
	for(phase_cond = 0; phase_cond < PHASE_CONDS; phase_cond++)
	{
		fai = phase_cond*DEGREE_STEP*PI/PI_DEG; 		// Convert phase from degrees to radians

		total_e = 0.0f;

		// Define the kernels
		for(taps_index = 0; taps_index < NO_OF_TAPS; taps_index++)
		{
			/*
			 * The kernel is a result between the multiplication of an exponential and a cosine function.
			 * k:			where k is the decay constant of the exponential function
			 * f: 			central frequency of the filter
			 * Ts: 			data sampling period
			 * taps_index:	index for the taps of the kernel
			 * PI:			pi number
			 * fai:			phase of the cosine function
			 */
			kernel_exp = exp(-k*(taps_index*Ts));
			total_e += kernel_exp;
			cosine = cos(2.0f*PI*f*taps_index*Ts - fai);
			kernel[phase_cond][taps_index] = kernel_exp * cosine;
		}

		total_e *= 0.5f;

		// Centre each of the kernels around zero
		for(taps_index = 0; taps_index < NO_OF_TAPS; taps_index++)
		{
			kernel[phase_cond][taps_index] /= total_e;
		}
	}

	phase_cond = 0;
}

/*
** ===================================================================
** void phase_shift(unsigned short *rec_reg_ptr,
** 					unsigned short *stim_reg_ptr)
** ===================================================================
** Description:	Performs the phase-shift algorithm. The recorded data
** 				is convolved with the kernel, the coice of which depends
** 				on the phase condition. The result is then stored in
** 				the stimulation register.
**
** Inputs: 	(unsigned short *rec_reg_ptr): pointer to the rec register
** 			(unsigned short *stim_reg_ptr): pointer to the stim register
**
** Outputs: None
/* ===================================================================*/
void phase_shift(unsigned short *rec_reg_ptr, unsigned short *stim_reg_ptr)
{
	float rconv = 0.0f;					// Value obtain after convolution is performed
	unsigned short j, i;				// For-loop indices
	unsigned char scale = 1;			// Used to scale the output of the algorithm

	/*
	 * Shift all the values in the convolution register by one place to the left,
	 * leaving the last place empty for the new recording to be inserted to the array.
	 */
	for(i = 0; i < (NO_OF_TAPS - 1); i++)
	{
		conv_buf[i] = conv_buf[i + 1];
	}

	/*
	 * Recorded data is converted to float and then stored in the last place of the
	 * convolution buffer.
	 */
	conv_buf[NO_OF_TAPS - 1] = convIntFloat(*rec_reg_ptr);

	/*
	 * Convolution is performed between the kernel and the recorded data. The result
	 * is the stored in rconv.
	 */
	for(j = 0; j < NO_OF_TAPS; j++)
	{
		rconv = kernel[phase_cond][j] * conv_buf[NO_OF_TAPS - 1 - j] + rconv;
	}

	*stim_reg_ptr = convFloatInt(rconv) * scale;	// Outputs scaling to fit DAC

	/*
	 * Checks if the output of the algorithm exceeds a user specified threshold.
	 */
	if(*stim_reg_ptr > threshold)
	{
		/*
		 * Check if the set intensity version of the algorithm is used instead of the
		 * original
		 */
		if (algorithm == SET_INTENSITY)
			*stim_reg_ptr = scale * 400;

		/*
		 * Ensures the DAC level will not exceed the maximum value (4095)
		 */
		if (*stim_reg_ptr >= DAC_MAX_LEVEL)
		{
			*stim_reg_ptr = DAC_MAX_LEVEL;
		}
	}
	else
	{
		/*
		 * If the output of the algorithm does not exceed the threshold DAC is set to 0.
		 */
		*stim_reg_ptr = 0;
	}
}
