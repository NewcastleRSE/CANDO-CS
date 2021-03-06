/* ###################################################################
**     Filename    : Phase_Shift_Algorithm.c
**     Project     : RCS_Box_2.2
**     Processor   : MK22FN512VDC12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-02-11, 17:04, # CodeGen: 0
**     Abstract    :
**         	Contains function definitions related to the phase shift
**         	algorithms.
** ###################################################################*/

#include "Algorithms.h"
#include "Phase_Shift_Algorithm.h"
#include "Events.h"
//#include "arm_math.h"
#include <math.h>

extern algorithm      phaseShift;
extern GUI            GUIParams;

algorithm 	phaseShift	= {ZERO, ONE, 10, ZERO, 100, NO_OF_TAPS};
GUI			GUIParams	= {ORIGINAL, FIXED, FIXED, OFF, OFF, 10, 10, ZERO,
							{ZERO, ONE, 10, ZERO, 100, NO_OF_TAPS}};

float kernel[PHASE_CONDS][NO_OF_TAPS] 	= {0.0f};
float conv_buf[NO_OF_TAPS] 				= {0.0f};
unsigned char phase_cond 				= 0;

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
* ===================================================================*/
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
* ===================================================================*/
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
* ===================================================================*/
void init_kernel(void)
{
	unsigned short taps_index = 0;

	unsigned char f 		= GUIParams.algorithm.phaseShift.f;			// Central frequency of the algorithm provided by the GUI
	unsigned short noOfTaps	= GUIParams.algorithm.phaseShift.kernelLen; 	// Kernel length provided by the GUI

	float total_e = 0.0f, //kernel_exp = 0.0f,
		    fai = 0.0f, k = 1.25f;
    double cosine = 0, kernel_exp = 0;
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
		for(taps_index = 0; taps_index < noOfTaps; taps_index++)
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
			kernel_exp = exp(-k*f*(taps_index*Ts));
			//total_e += kernel_exp;
			cosine = cos(2.0f*PI*f*taps_index*Ts - fai); 
			kernel[phase_cond][taps_index] = kernel_exp * cosine;
		    total_e += kernel[phase_cond][taps_index];
        }

		//total_e *= 0.5f;
        total_e /= noOfTaps;
		// Centre each of the kernels around zero
		for(taps_index = 0; taps_index < noOfTaps; taps_index++)
		{
			kernel[phase_cond][taps_index] -= total_e;
		}
	}
}


/*
** ===================================================================
** void update_param(unsigned char * parameters)
** ===================================================================
** Description: Updating the parameters of the algorithm and the GUI
**
** Inputs: unsigned char param[]
**
** Outputs: None
* ===================================================================*/
void update_param(unsigned char param[])
{
	GUIParams.algoOption 						= param[0];
	GUIParams.phaseOption 						= param[1];
	GUIParams.algorithm.phaseShift.phaseCond	= param[2];
	GUIParams.gainOption 						= param[3];
	GUIParams.algorithm.phaseShift.gain   		= param[4];
	GUIParams.algorithm.phaseShift.f			= param[5];
	GUIParams.algorithm.phaseShift.thr			= param[6];
	GUIParams.algorithm.phaseShift.setIntVal 	= (param[8] << BYTE) + param[7];
	GUIParams.algorithm.phaseShift.kernelLen	= (param[10] << BYTE) + param[9];
	GUIParams.dutyCycle							= param[11];
	GUIParams.onTime							= (param[13] << BYTE) + param[12];
	GUIParams.offTime							= (param[15] << BYTE) + param[14];
	GUIParams.manLED							= param[16];
	GUIParams.manLEDLvl							= (param[18] << BYTE) + param[17];

	init_kernel();
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
* ===================================================================*/
void phase_shift(unsigned short *rec_reg_ptr, unsigned short *stim_reg_ptr)
{
	float rconv = 0.0f;											// Value obtain after convolution is performed
	unsigned short j, i;										// For-loop indices
	unsigned char gain = GUIParams.algorithm.phaseShift.gain;	// Used to scale the output of the algorithm

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
		rconv = kernel[GUIParams.algorithm.phaseShift.phaseCond][j] * conv_buf[NO_OF_TAPS - 1 - j] + rconv;
	}

	*stim_reg_ptr = convFloatInt(rconv) * gain;	// Outputs scaling to fit DAC

	/*
	 * Checks if the output of the algorithm exceeds a user specified threshold.
	 */
	if(*stim_reg_ptr > GUIParams.algorithm.phaseShift.thr)
	{
		/*
		 * Check if the set intensity version of the algorithm is used instead of the
		 * original
		 */
		if (GUIParams.algoOption == SET_INTENSITY)
			*stim_reg_ptr = gain * GUIParams.algorithm.phaseShift.setIntVal;

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

