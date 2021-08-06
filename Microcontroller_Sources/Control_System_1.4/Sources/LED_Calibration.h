/* ###################################################################
**     Filename    : LED_Calibration.h
**     Project     : Control_System_1.4
**     Processor   : MK22FN512VDC12
**     Component   : LED_Calibration
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-03-06, 09:31, # CodeGen: 0
**     Abstract    :
**         	Contains calibration values for the LED current
** ###################################################################*/

#ifndef __LED_Calibration_H
#define __LED_Calibration_H
/* MODULE LED_Calibration */

// The current resolution was chosen to be 6 bits (1 << 6 = 64 values)
#define NO_OF_BITS 	6
#define NO_OF_VAL 	1 << NO_OF_BITS

extern unsigned short LEDCal[NO_OF_VAL];

/* END LED_Calibration */
#endif
