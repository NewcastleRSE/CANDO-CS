/* ###################################################################
**     Filename    : Phase_Shift_Algorithm.h
**     Project     : RCS_Box_2.1
**     Processor   : MK22FN512VDC12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-01-29, 16:48, # CodeGen: 0
**     Abstract    :
**         	Contains function declarations related to the phase shift
**         	algorithms.
** ###################################################################*/

#ifndef __Phase_Shift_Algorithm_H
#define __Phase_Shift_Algorithm_H
/* MODULE Phase_Shift_Algorithm */

#define NO_OF_TAPS 		512			// Number of taps per kernel
#define PHASE_CONDS 	8			// Phase conditions (0-7)
#define DEGREE_STEP		45.0f		// Phase = (Phase condition) * (degree step) - (0-315)

// Phase shift algorithms
#define ORIGINAL		0
#define SET_INTENSITY 	1

#define DAC_MAX_LEVEL	4095		// Maximum value for 12-bit DAC

// Sampling period (Ts) and frequency (Fs)
#define Ts				0.002f
#define Fs				1.0f/Ts

#define PI_DEG			180.0f 		// pi number in degrees

extern unsigned char phase_cond;

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

/* END Phase_Shift_Algorithm */
#endif


