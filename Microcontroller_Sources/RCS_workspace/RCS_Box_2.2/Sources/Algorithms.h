/* ###################################################################
**     Filename    : Algorithms.h
**     Project     : RCS_Box_2.2
**     Processor   : MK22FN512VDC12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-02-11, 17:04, # CodeGen: 0
**     Abstract    :
**     		Contains type definitions of each algorithm and its GUI
**     		parameters.
** ###################################################################*/

#ifndef __Algorithms_H
#define __Algorithms_H
/* MODULE Algorithms */

typedef union
{
	// Phase Shift algorithm
	struct
	{
		unsigned char 	phaseCond;	// Phase condition (0-7)
		unsigned char 	gain;		// DAC scaled up according to gain value
		unsigned char 	f;			// Central frequency of the algorithm
		unsigned char 	thr;		// Threshold applied on the output of the algorithm
		unsigned short 	setIntVal;	// Defines the amplitude of the set-intensity algorithm output
		unsigned short 	kernelLen;	// Defines the length of the filter kernel
	} phaseShift;

	// More algorithms can be added here

} algorithm;

typedef struct
{
	unsigned char	algoOption;		// Holds the current algorithm option				(Original/Set Intensity)
	unsigned char 	phaseOption;	// Holds the current phase option					(Fixed/Sequential/Random)
	unsigned char 	gainOption;		// Holds the current gain option					(Fixed/Sequential/Random)
	unsigned char 	dutyCycle;		// Perform the algorithm in a duty-cycled manner	(Off/On)
	unsigned short 	onTime;			// Defines the on period of the duty cycle
	unsigned short 	offTime;		// Defines the off period of the duty cycle
	unsigned char 	manLED;			// Choice between Algorithm/(manual control of LED)	(Algo/LED)
	unsigned short 	manLEDLvl;		// Defines the DAC level for the manual LED case
	algorithm		algorithm;
} GUI;

/* END Algorithms */
#endif
