/* ###################################################################
**     Filename    : Phase_Shift_Algorithm.h
**     Project     : RCS_Box_2.2
**     Processor   : MK22FN512VDC12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-02-11, 17:04, # CodeGen: 0
**     Abstract    :
**         	Contains function declarations related to the phase shift
**         	algorithms.
** ###################################################################*/

//#ifndef __Phase_Shift_Algorithm_H
//#define __Phase_Shift_Algorithm_H
/* MODULE Phase_Shift_Algorithm */

#define NO_OF_TAPS 		512			// Number of taps per kernel
#define PHASE_CONDS 	8			// Phase conditions (0-7)
#define DEGREE_STEP		45.0f		// Phase = (Phase condition) * (degree step) - (0-315)

// Phase and Gain options
#define FIXED 			0			// Fixed phase or gain
#define SEQ				1			// Sequential iteration through the set of possible phase conditions or gains
#define RAND			2			// Random iteration through the set of possible phase conditions or gains

// Algorithm options
#define ZERO			0			// Value of zero
#define ONE				1			// Value of one
#define OFF				0			// Off
#define ON				1			// On

// Phase shift algorithms
#define ORIGINAL		0			// Original algorithm
#define SET_INTENSITY 	1			// Set Intensity algorithm

#define DAC_MAX_LEVEL	4095		// Maximum value for 12-bit DAC

// Sampling period (Ts) and frequency (Fs)
#define Ts				0.002f		// Sampling period (s)
#define Fs				1.0f/Ts		// Sampling frequency (Hz)

#define PI_DEG			180.0f 		// pi number in degrees

// Defining PI, as used in arm_math.h, for the comp only version to avoid using
// arm_math.h
#ifndef PI
#define PI                 3.14159265358979f



extern unsigned char 	phase_cond;
//extern algorithm 		phaseShift;
//extern GUI				GUIParams;

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
**
** Inputs: 	unsigned char param[]
**
** Outputs: None
/* ===================================================================*/
void update_param(unsigned char param[]);

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


