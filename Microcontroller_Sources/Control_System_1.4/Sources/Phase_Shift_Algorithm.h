/* ###################################################################
**     Filename    : Phase_Shift_Algorithm.h
**     Project     : Control_System_1.4
**     Processor   : MK22FN512VDC12
**     Component   : Phase_Shift_Algorithm
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-03-06, 09:31, # CodeGen: 0
**     Abstract    :
**         	Contains function declarations related to the phase shift
**         	algorithms.
** ###################################################################*/

#ifndef __Phase_Shift_Algorithm_H
#define __Phase_Shift_Algorithm_H
/* MODULE Phase_Shift_Algorithm */

#include "Algorithms.h"

#define ALGO			0
#define MANUAL			1

#define NO_OF_TAPS 		512			// Number of taps per kernel
#define PHASE_CONDS 	8			// Phase conditions (0-7)
#define DEGREE_STEP		45.0f		// Phase = (Phase condition) * (degree step) - (0-315)

// Phase and Gain options
#define NO_LOOP 		0			// Fixed phase or gain (no loop)
#define SEQ				1			// Sequential iteration through the set of possible phase conditions or gains
#define RAND			2			// Random iteration through the set of possible phase conditions or gains

// Phase shift algorithms
#define ORIGINAL		0			// Original algorithm
#define SET_INTENSITY 	1			// Set Intensity algorithm

// Sampling period (Ts) and frequency (Fs)
#define Ts				0.001f		// Sampling period (s)
#define Fs				1.0f/Ts		// Sampling frequency (Hz)

#define PI_DEG			180.0f 		// pi number in degrees

extern algorithm		phaseShift;
extern GUI				GUIParams;

extern unsigned short *phase_indx;
extern unsigned short *gain_indx;
extern unsigned short *set_int_indx;

extern unsigned short size;

extern unsigned char configured;

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
float convIntFloat(unsigned short i);

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
unsigned short convFloatInt(float f);

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
void init_kernel(void);

/*
** ===================================================================
** void update_param(unsigned char * parameters)
** ===================================================================
** Description: Updating the parameters of the algorithm and the GUI
** 				quick determines if the update is only about variables
** 				that do not affect the filter kernel. Alternatively, all
** 				the variables are updated and the kernel is re-initialised.
**
** Inputs: 	unsigned char param[]
** 			unsigned char quick
**
** Outputs: None
/* ===================================================================*/
void update_param(unsigned char param[], unsigned char quick);

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
void phase_shift(unsigned short *rec_reg_ptr, unsigned short *stim_reg_ptr);

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
void manual_LED(unsigned char method);

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
void calc_conds(void);

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
void gen_indices(void);

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
void shuffle_indices(void);

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
void sequential(void);

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
void pseudo_random(void);

void set_algo_params(void);

void reset_params(void);

unsigned char calc_param_combs(void);
/* END Phase_Shift_Algorithm */
#endif


