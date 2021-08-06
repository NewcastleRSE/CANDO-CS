/* ###################################################################
**     Filename    : Phase_Shift_Algorithm.c
**     Project     : Control_System_1.4
**     Processor   : MK22FN512VDC12
**     Component   : Phase_Shift_Algorithm
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-03-06, 09:31, # CodeGen: 0
**     Abstract    :
**         	Contains function definitions related to the phase shift
**         	algorithms.
** ###################################################################*/

#include "Phase_Shift_Algorithm.h"
#include "Events.h"
#include "arm_math.h"
#include "IO.h"
#include <stdlib.h>
#include <math.h>
#include "LTC2624.h"
#include "Glossary.h"

float **kernel;
float *conv_buf;
unsigned short *phase_indx;
unsigned short *gain_indx;
unsigned short *set_int_indx;

unsigned short offset = 0;

unsigned short size = 0;
unsigned short pseudo_cntr = 1;
unsigned char init = 0;
unsigned char configured = 0;

algorithm phaseShift = 	// Phase shift algorithm parameters
{		ZERO,			// phaseValue		- Current phase value
		ZERO,			// phaseStart		- Starting phase value
		45,				// phaseStep		- Step size for phase
		315,			// phaseEnd			- Final phase value
		PHASE_CONDS,	// phaseConds		- Number of phase conditions
		ONE,			// gainValue		- Current gain value
		ONE,			// gainStart		- Starting gain value - DAC scaled up according to gain value
		ONE,			// gainStep 		- Step size for gain
		ONE,			// gainEnd 			- Final gain value
		ONE,			// gainConds		- Number of gain conditions
		10,				// f				- Central frequency of the algorithm
		ONE,			// thr				- Threshold applied on the output of the algorithm
		ONE,			// setIntConds		- Number of set intensity conditions
		1000,			// setIntVal		- Current set intensity value
		1000,			// setIntValStart	- Starting set intensity value - Defines the amplitude of the set-intensity algorithm output
		1000,			// setIntValStep 	- Step size for set intensity value
		1000,			// setIntValEnd		- Final set intensity value
		NO_OF_TAPS		// kernelLen		- Defines the length of the filter kernel
};

GUI		GUIParams	=
{		MANUAL, 		// manLEDOption 	- Choice between (manual control of LED)/Algorithm	(MANUAL/ALGO)
		ORIGINAL, 		// algoOption 		- Holds the current algorithm option				(Original/Set Intensity)
		SEQ, 			// loopOption		- Holds the current phase option					(No Loop(0)/Sequential(1)/Random(2))
		NO_LOOP,		// gainOption		- Holds the current gain option						(Fixed/Sequential/Random)
		ZERO,			// manLEDLvl		- Defines the DAC level for the manual LED case  	(0 - 4095)
		OFF,			// manLEDState		- Defines the LED state 							(OFF/ON)
		OFF,			// dutyCycle		- Perform the algorithm in a duty-cycled manner		(OFF/ON)
		ZERO,			// onTime			- Defines the on period (ms) of the duty cycle 		(0 - 65535)
		ZERO,			// offTime			- Defines the off period (ms) of the duty cycle 	(0 - 65535)
		ONE, 			// cmd				- Defines the command to be executed				(start/stop sending data, update parameters, etc.)
		&phaseShift		// algo				- Algorithm structure
};

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
	float f;				// Result of the conversion

	f = i / 255.0f * 2.0f; 	// Scale the integer value from 0.0f to 2.0f
	f -= 1.0f;				// Shift the value between -1.0f to 1.0f

	return f;				// Return the result
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
	i = f / 20.0f * 4095;

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
	unsigned short 	taps_index 	= 0;
	unsigned short 	phase_cond 	= 0;
	unsigned short 	phaseValue;
	unsigned short 	phaseStart 	= GUIParams.algo->phaseShift.phaseStart;
	unsigned short 	phaseStep 	= GUIParams.algo->phaseShift.phaseStep;
	unsigned short 	phaseEnd	= GUIParams.algo->phaseShift.phaseEnd;
	unsigned short 	noOfTaps	= GUIParams.algo->phaseShift.kernelLen; // Kernel length provided by the GUI
	unsigned char 	f	 		= GUIParams.algo->phaseShift.f;			// Central frequency of the algo provided by the GUI

	float 	total 	= 0.0f, kernel_exp 	= 0.0f,
			cosine 	= 0.0f, fai 		= 0.0f,
			k 		= 1.25f;

	pseudo_cntr = 0;

	calc_conds();

	if (init)
	{
		kernel = (float**) realloc(kernel, GUIParams.algo->phaseShift.phaseConds * sizeof(float*));

		for (int i = 0; i < GUIParams.algo->phaseShift.phaseConds; i++)
			kernel[i] = (float*) realloc(kernel[i], GUIParams.algo->phaseShift.kernelLen * sizeof(float));

		conv_buf = (float*) realloc(conv_buf, GUIParams.algo->phaseShift.kernelLen * sizeof(float));
	}
	else
	{
		kernel = (float**) calloc(GUIParams.algo->phaseShift.phaseConds, sizeof(float*));

		for (int i = 0; i < GUIParams.algo->phaseShift.phaseConds; i++)
			kernel[i] = (float*) calloc(GUIParams.algo->phaseShift.kernelLen, sizeof(float));

		conv_buf = (float*) calloc(GUIParams.algo->phaseShift.kernelLen, sizeof(float));

		init = 1;
	}

	gen_indices();

	shuffle_indices();

	/*
	 * Define the kernels for each of the phase conditions (0-7).
	 * The phase value for each of the conditions can be obtained as
	 * follows: phase = phase_cond*45 (0-315, with a 45 degree step).
	 */
	for(phaseValue = phaseStart; phaseValue <= phaseEnd; phaseValue += phaseStep)
	{
		fai = phaseValue*PI/PI_DEG; 		// Convert phase from degrees to radians

		total = 0.0f;

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
			kernel_exp = exp(-k * f * taps_index * Ts);
			cosine = cos(2.0f * PI * f * taps_index * Ts - fai);
			kernel[phase_cond][taps_index] = kernel_exp * cosine;
			total += kernel[phase_cond][taps_index];
		}

		total /= noOfTaps;

		// Centre each of the kernels around zero
		for(taps_index = 0; taps_index < noOfTaps; taps_index++)
		{
			kernel[phase_cond][taps_index] -= total;
		}

		phase_cond++;
	}

	configured = 1;
}

/*
** ===================================================================
** void update_param(unsigned char * parameters)
** ===================================================================
** Description: Updating the parameters of the algo and the GUI
** 				quick determines if the update is only about variables
** 				that do not affect the filter kernel. Alternatively, all
** 				the variables are updated and the kernel is re-initialised.
**
** Inputs: 	unsigned char param[]
** 			unsigned char quick
**
** Outputs: None
/* ===================================================================*/
void update_param(unsigned char param[], unsigned char quick)
{
//	updating = 1;

	// Reset the parameter cycle completion counter and flag
	cycle_cnt = 0;
	cycle_comp = ZERO;														 
	/*
	 * The parameters received from the GUI are stored into the corresponding
	 * struct fields in order to be used in the code
	 */
	GUIParams.manLEDOption						= param[0];
	GUIParams.algoOption 						= param[1];
	GUIParams.loopOption 						= param[2];

	GUIParams.algo->phaseShift.gainValue		= param[11];
	GUIParams.algo->phaseShift.gainStart		= param[11];
	GUIParams.algo->phaseShift.gainStep			= param[12];
	GUIParams.algo->phaseShift.gainEnd			= param[13];
	GUIParams.algo->phaseShift.setIntVal		= (param[15] << BYTE) + param[14];
	GUIParams.algo->phaseShift.setIntValStart 	= (param[15] << BYTE) + param[14];
	GUIParams.algo->phaseShift.setIntValStep	= (param[17] << BYTE) + param[16];
	GUIParams.algo->phaseShift.setIntValEnd		= (param[19] << BYTE) + param[18];
	GUIParams.algo->phaseShift.thr				= (param[21] << BYTE) + param[20];
	GUIParams.dutyCycle							= param[22];
	GUIParams.onTime							= (param[24] << BYTE) + param[23];
	GUIParams.offTime							= (param[26] << BYTE) + param[25];
	GUIParams.manLEDLvl							= (param[28] << BYTE) + param[27];
	GUIParams.manLEDState						= param[29];
	GUIParams.cmd								= param[34];

	/*
	 * If the "quick update" command was sent from the GUI the parameters that
	 * correspond to the kernel of the FIR filter are skipped. Otherwise if the
	 * "update parameters" command is sent the following part will be executed
	 * and the kernel will be re-initialised.
	 */
	if (!quick)
	{
		GUIParams.algo->phaseShift.kernelLen	= (param[4] << BYTE) + param[3];
		GUIParams.algo->phaseShift.phaseValue	= (param[6] << BYTE) + param[5];
		GUIParams.algo->phaseShift.phaseStart   = (param[6] << BYTE) + param[5];
		GUIParams.algo->phaseShift.phaseStep    = param[7];
		GUIParams.algo->phaseShift.phaseEnd		= (param[9] << BYTE) + param[8];
		GUIParams.algo->phaseShift.f			= param[10];

		init_kernel();							// Initialise the kernel
	}

//	updating = 0;
}

/*
** ===================================================================
** void phase_shift(unsigned short *rec_reg_ptr,
** 					unsigned short *stim_reg_ptr)
** ===================================================================
** Description:	Performs the phase-shift algo. The recorded data
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
	float rconv = 0.0f;												// Value obtain after convolution is performed
	unsigned short j, i;											// For-loop indices
	unsigned char gain = GUIParams.algo->phaseShift.gainValue;		// Used to scale the output of the algo
//	float gain = GUIParams.algo->phaseShift.gainValue / 10.0f;
	unsigned char phaseIndx = (GUIParams.algo->phaseShift.phaseValue - GUIParams.algo->phaseShift.phaseStart)
									/ GUIParams.algo->phaseShift.phaseStep;

	float *k_head = kernel[phaseIndx];
	float *k_tail = kernel[phaseIndx] + GUIParams.algo->phaseShift.kernelLen;

	float *buf_val = conv_buf + offset;

	*buf_val = convIntFloat(*rec_reg_ptr);

	while(buf_val >= conv_buf)
		rconv += *buf_val-- * *k_head++;

	buf_val = conv_buf + GUIParams.algo->phaseShift.kernelLen - 1;

	while(k_head < k_tail)
		rconv += *buf_val-- * *k_head++;

	if (++offset >= GUIParams.algo->phaseShift.kernelLen)
		offset = 0;


	/*
	 * Shift all the values in the convolution register by one place to the left,
	 * leaving the last place empty for the new recording to be inserted to the array.
	 */
//	for(i = 0; i < (GUIParams.algo->phaseShift.kernelLen - 1); i++)
//	{
//		conv_buf[i] = conv_buf[i + 1];
//	}

	/*
	 * Recorded data is converted to float and then stored in the last place of the
	 * convolution buffer.
	 */
//	conv_buf[GUIParams.algo->phaseShift.kernelLen - 1] = convIntFloat(*rec_reg_ptr);

	/*
	 * Convolution is performed between the kernel and the recorded data. The result
	 * is the stored in rconv.
	 */
	for(j = 0; j < GUIParams.algo->phaseShift.kernelLen; j++)
	{
		rconv += kernel[phaseIndx][j] * conv_buf[NO_OF_TAPS - 1 - j];
	}

	*stim_reg_ptr = convFloatInt(rconv) * gain;	// Outputs scaling to fit DAC

	/*
	 * Checks if the output of the algo exceeds a user specified threshold.
	 */
	if(*stim_reg_ptr > GUIParams.algo->phaseShift.thr)
	{

		*stim_reg_ptr -= GUIParams.algo->phaseShift.thr;
		/*
		 * Check if the set intensity version of the algo is used instead of the
		 * original
		 */
		if (GUIParams.algoOption == SET_INTENSITY)
			*stim_reg_ptr = GUIParams.algo->phaseShift.setIntVal & 0x0FFF;

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

/*
** ===================================================================
** void manual_LED(unsigned char method)
** ===================================================================
** Description:	Determines the state of the LED depending on the options
** 				passed from the GUI.
**
** Inputs: 	(unsigned char method): determines the method of stimulation
** 									(uC DAC or ASIC LED driver)
**
** Outputs: None
/* ===================================================================*/
void manual_LED(unsigned char method)
{
	// The LED on button was pressed in the GUI
	if (GUIParams.manLEDState == ON)
	{
		stim_reg = GUIParams.manLEDLvl;				// The LED level determined from the slider on
													// the GUI is passed to the stimulation register
		stimulate(&stim_reg, method);				// Sets the DAC to the appropriate level
	}
	// The LED off button was pressed in the GUI
	else if (GUIParams.manLEDState == OFF)
	{
		stim_reg = 0;								// Sets the stimulation register to 0
		stimulate(&stim_reg, method);				// Sets the DAC level to 0
	}
	// Should't reach this point
	else
	{
		// Turning the LED off for safety
		stim_reg = 0;
		stimulate(&stim_reg, _uC);

		// Setting the flag and GUI options
		GUIParams.manLEDOption = MANUAL;
		GUIParams.manLEDState = OFF;
	}
}

/*
** ===================================================================
** void calc_conds(void)
** ===================================================================
** Description:	Calculates the conditions for each parameter (phase,
** 				gain and set intensity).
**
** Inputs: 	None
**
** Outputs: None
/* ===================================================================*/
void calc_conds(void)
{
	// Calculate the phase conditions
	GUIParams.algo->phaseShift.phaseConds = (GUIParams.algo->phaseShift.phaseEnd - GUIParams.algo->phaseShift.phaseStart)
												/ GUIParams.algo->phaseShift.phaseStep + 1;

	// Calculate the gain conditions
	GUIParams.algo->phaseShift.gainConds = (GUIParams.algo->phaseShift.gainEnd - GUIParams.algo->phaseShift.gainStart)
														/ GUIParams.algo->phaseShift.gainStep + 1;

	// Calculate the set intensity level conditions
	GUIParams.algo->phaseShift.setIntConds = (GUIParams.algo->phaseShift.setIntValEnd - GUIParams.algo->phaseShift.setIntValStart)
																/ GUIParams.algo->phaseShift.setIntValStep + 1;
}

/*
** ===================================================================
** void gen_indices(void)
** ===================================================================
** Description:	Generates indices for each of the parameters. These can
** 				then be used to determine the order in which the
** 				parameters are applied during the pseudo-random option.
**
** Inputs: 	None
**
** Outputs: None
/* ===================================================================*/
void gen_indices(void)
{
	// Variable declarations and definition
	unsigned short i, j, k, l = 0;
	
	size = calc_param_combs();

	// If the Set Intensity algorithm is chosen then the set intensity conditions should be taken into account
	if (GUIParams.algoOption == SET_INTENSITY)
		size = GUIParams.algo->phaseShift.phaseConds * GUIParams.algo->phaseShift.gainConds * GUIParams.algo->phaseShift.setIntConds;
	// else only the phase and gain conditions
	else
		size = GUIParams.algo->phaseShift.phaseConds * GUIParams.algo->phaseShift.gainConds;

	// If memory has already been allocated for the arrays that hold the indices reallocate it according to the new size
	if (init)
	{
		phase_indx 		= (unsigned short*) realloc(phase_indx, 	size * sizeof(unsigned short));
		gain_indx		= (unsigned short*) realloc(gain_indx, 		size * sizeof(unsigned short));
		set_int_indx 	= (unsigned short*) realloc(set_int_indx,   size * sizeof(unsigned short));
	}
	// else allocate memory and initialise the elements to 0
	else
	{
		phase_indx 		= (unsigned short*) calloc(size, sizeof(unsigned short));
		gain_indx 		= (unsigned short*) calloc(size, sizeof(unsigned short));
		set_int_indx 	= (unsigned short*) calloc(size, sizeof(unsigned short));
	}

	// Again for the set intensity algorithm the set intensity indices need to be initialised
	if (GUIParams.algoOption == SET_INTENSITY)
	{
		for (i = 0; i < GUIParams.algo->phaseShift.phaseConds; i++)
		{
			for (j = 0; j < GUIParams.algo->phaseShift.gainConds; j++)
			{
				for (k = 0; k < GUIParams.algo->phaseShift.setIntConds; k++)
				{
					phase_indx[l] 	= i;
					gain_indx[l]  	= j;
					set_int_indx[l] = k;

					l++;
				}
			}
		}
	}
	// If the original algorithm has been selected then only the phase and gain need to be utilised
	else
	{
		for (i = 0; i < GUIParams.algo->phaseShift.phaseConds; i++)
		{
			for (j = 0; j < GUIParams.algo->phaseShift.gainConds; j++)
			{
				phase_indx[l] 	= i;
				gain_indx[l]  	= j;

				l++;
			}
		}
	}
}

/*
** ===================================================================
** void shuffle_indices(unsigned short size)
** ===================================================================
** Description:	Shuffles the order of the indices in the arrays for the
** 				algortithm parameters
**
** Inputs: 	(unsigned short size): the size of the indices arrays
**
** Outputs: None
/* ===================================================================*/
void shuffle_indices(void)
{
	unsigned short i, temp, r;

	/*
	 * The indices in the arrays are shuffled in the same manner so that
	 * the order of occurrence of each parameter combination is randomised.
	 */
	for (i = 0; i < size; i++)
	{
		r = rand() % size;
		temp = phase_indx[i];
		phase_indx[i] = phase_indx[r];
		phase_indx[r] = temp;

		temp = gain_indx[i];
		gain_indx[i] = gain_indx[r];
		gain_indx[r] = temp;

		if (GUIParams.algoOption == SET_INTENSITY)
		{
			temp = set_int_indx[i];
			set_int_indx[i] = set_int_indx[r];
			set_int_indx[r] = temp;
		}
	}
}

/*
** ===================================================================
** void sequential(void)
** ===================================================================
** Description:	The parameters of the algorithm are applied sequentially
**
** Inputs: 	None
**
** Outputs: None
/* ===================================================================*/
void sequential(void)
{
	// For the set intensity algorithm the set intensity value also needs to be incremented
	if (GUIParams.algoOption == SET_INTENSITY && GUIParams.algo->phaseShift.setIntVal < GUIParams.algo->phaseShift.setIntValEnd)
		GUIParams.algo->phaseShift.setIntVal += GUIParams.algo->phaseShift.setIntValStep;
	// For the origianl algorithm only the gain and phase values need to be incremented
	else
	{
		GUIParams.algo->phaseShift.setIntVal = GUIParams.algo->phaseShift.setIntValStart;

		if (GUIParams.algo->phaseShift.gainValue < GUIParams.algo->phaseShift.gainEnd)
			GUIParams.algo->phaseShift.gainValue += GUIParams.algo->phaseShift.gainStep;
		else
		{
			GUIParams.algo->phaseShift.gainValue = GUIParams.algo->phaseShift.gainStart;

			if (GUIParams.algo->phaseShift.phaseValue < GUIParams.algo->phaseShift.phaseEnd)
				GUIParams.algo->phaseShift.phaseValue += GUIParams.algo->phaseShift.phaseStep;
			else
				GUIParams.algo->phaseShift.phaseValue = GUIParams.algo->phaseShift.phaseStart;
		}
	}
}

/*
** ===================================================================
** void pseudo_random(void)
** ===================================================================
** Description:	The parameters of the algorithm are applied in a random
** 				sequence according to the indices generated and stored
** 				in the arrays.
**
** Inputs: 	None
**
** Outputs: None
/* ===================================================================*/
void pseudo_random(void)
{
	// For the set intensity algorithm the set intensity value also needs to be updated
	if (GUIParams.algoOption == SET_INTENSITY)
	{
		GUIParams.algo->phaseShift.setIntVal =
				GUIParams.algo->phaseShift.setIntValStart + set_int_indx[pseudo_cntr] * GUIParams.algo->phaseShift.setIntValStep;
	}

	// Here the gain and phase values are updated
	GUIParams.algo->phaseShift.gainValue = GUIParams.algo->phaseShift.gainStart + gain_indx[pseudo_cntr]  * GUIParams.algo->phaseShift.gainStep;
	GUIParams.algo->phaseShift.phaseValue = GUIParams.algo->phaseShift.phaseStart + phase_indx[pseudo_cntr++] * GUIParams.algo->phaseShift.phaseStep;

	// Once all the parameter combinations have been applied the indices in the arrays are shuffled again
	if (pseudo_cntr >= size)
	{
		shuffle_indices();

		pseudo_cntr = 0;
	}
}

void set_algo_params(void)
{
	float DAC_phase = GUIParams.algo->phaseShift.phaseValue /
			(float)(GUIParams.algo->phaseShift.phaseEnd - GUIParams.algo->phaseShift.phaseStart) * 4095;

	ltc2624_setValAndUpdate(&ltc2624_DAC_A, (rec_reg<<2));
	ltc2624_setValAndUpdate(&ltc2624_DAC_C, DAC_phase);
	ltc2624_setValAndUpdate(&ltc2624_DAC_D, algo_on_off_flag * DAC_MAX_LEVEL);
}

void reset_params(void)
{
	GUIParams.algoOption 						= MANUAL;
	GUIParams.manLEDOption 						= MANUAL;
	GUIParams.manLEDState 						= OFF;
	GUIParams.manLEDLvl							= ZERO;
	GUIParams.onTime 							= ZERO;
	GUIParams.offTime 							= ZERO;
	GUIParams.algo->phaseShift.f 				= 10;
	GUIParams.algo->phaseShift.thr 				= 1;
	GUIParams.algo->phaseShift.kernelLen		= NO_OF_TAPS;

	GUIParams.algo->phaseShift.gainValue 		= ONE;
	GUIParams.algo->phaseShift.gainStart 		= ONE;
	GUIParams.algo->phaseShift.gainStep 		= ONE;
	GUIParams.algo->phaseShift.gainEnd 			= ONE;
	GUIParams.algo->phaseShift.gainConds		= ONE;

	GUIParams.algo->phaseShift.phaseValue 		= ZERO;
	GUIParams.algo->phaseShift.phaseStart 		= ZERO;
	GUIParams.algo->phaseShift.phaseStep 		= 45;
	GUIParams.algo->phaseShift.phaseEnd 		= 315;
	GUIParams.algo->phaseShift.phaseConds 		= PHASE_CONDS;

	GUIParams.algo->phaseShift.setIntVal 		= 1000;
	GUIParams.algo->phaseShift.setIntValStart 	= 1000;
	GUIParams.algo->phaseShift.setIntValStep 	= ONE;
	GUIParams.algo->phaseShift.setIntValEnd 	= 1000;
	GUIParams.algo->phaseShift.setIntConds		= ONE;
}

unsigned char calc_param_combs(void)
{
	unsigned char combs;

	// If the Set Intensity algorithm is chosen then the set intensity conditions should be taken into account
	if (GUIParams.algoOption == SET_INTENSITY)
		combs = GUIParams.algo->phaseShift.phaseConds * GUIParams.algo->phaseShift.gainConds * GUIParams.algo->phaseShift.setIntConds;
	// else only the phase and gain conditions
	else
		combs = GUIParams.algo->phaseShift.phaseConds * GUIParams.algo->phaseShift.gainConds;

	return combs;
}																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																 																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																															 
