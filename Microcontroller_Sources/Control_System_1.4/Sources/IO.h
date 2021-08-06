/* ###################################################################
**     Filename    : IO.h
**     Project     : Control_System_1.4
**     Processor   : MK22FN512VDC12
**     Component   : IO
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-03-06, 09:31, # CodeGen: 0
**     Abstract    :
**         	Contains function declarations for the functions that
**         	provide control of the input and output circuitry of the
**         	system.
** ###################################################################*/

#ifndef __IO_H
#define __IO_H
/* MODULE IO */
#include "ASIC.h"

extern unsigned char stim_method;
extern unsigned char rec_method;
extern unsigned char rec_channel;
extern unsigned char uart_tx;

/*
** ===================================================================
** void init_rec(void)
** ===================================================================
** Description: Initialise recording electronics
**
** Inputs:	none
**
** Outputs: none
/* ===================================================================*/
void init_rec(ASIC *ASIC);

void set_amplifier_ch0(ASIC *ASIC, unsigned char gain,
		unsigned char en_lp, unsigned char pd);

void set_amplifier_ch1(ASIC *ASIC, unsigned char gain,
		unsigned char en_lp, unsigned char pd);

/*
** ===================================================================
** void stim(unsigned short * stimVal, unsigned char stimMethod)
** ===================================================================
** Description: Defines the method of stimulation (microcontroller or
** 				ASIC) and defines the value of the stimulation.
**
** Inputs:	(unsigned short * stimVal): Pointer to the stimulation
** 			register
**
** 			(unsigned char stimMethod): Determines the method of
** 			stimulation
**
** Outputs: none
/* ===================================================================*/
void stimulate(unsigned short * stimVal, unsigned char stimMethod);

/*
** ===================================================================
** void record(unsigned short *recVal, unsigned char recordMethod)
** ===================================================================
** Description: Defines the method of recording (microcontroller or
** 				ASIC) and defines the value of the recording.
**
** Inputs:	(unsigned short * recVal): Pointer to the recording
** 			register
**
** 			(unsigned char recMethod): Determines the method of
** 			recording
**
** Outputs: none
/* ===================================================================*/
void record(unsigned short *recVal, unsigned char recMethod);

void choose_device(unsigned char param[]);

/* END IO */
#endif
