/* ###################################################################
**     Filename    : Algorithms.h
**     Project     : Control_System_1.4
**     Processor   : MK22FN512VDC12
**     Component   : Algorithms
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-03-06, 09:31, # CodeGen: 0
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
		unsigned short 	phaseValue;		// Current phase value
		unsigned short 	phaseStart;		// Starting phase value
		unsigned short 	phaseStep;		// Step size for phase
		unsigned short 	phaseEnd;		// Final phase value
		unsigned short 	phaseConds;		// Number of phase conditions
		unsigned char 	gainValue;		// Current gain value
		unsigned char 	gainStart;		// Starting gain value - DAC scaled up according to gain value
		unsigned char 	gainStep; 		// Step size for gain
		unsigned char 	gainEnd; 		// Final gain value
		unsigned char   gainConds;		// Number of gain conditions
		unsigned char 	f;				// Central frequency of the algorithm
		unsigned short 	thr;			// Threshold applied on the output of the algorithm
		unsigned short  setIntConds;	// Number of set intensity conditions
		unsigned short 	setIntVal;		// Current set intensity value
		unsigned short 	setIntValStart;	// Starting set intensity value - Defines the amplitude of the set-intensity algorithm output
		unsigned short 	setIntValStep; 	// Step size for set intensity value
		unsigned short	setIntValEnd;	// Final set intensity value
		unsigned short 	kernelLen;		// Defines the length of the filter kernel
	} phaseShift;

	// More algorithms can be added here

} algorithm;

typedef struct
{
	unsigned char 	manLEDOption;	// Choice between (manual control of LED)/Algorithm	(MANUAL/ALGO)
	unsigned char	algoOption;		// Holds the current algorithm option				(Original/Set Intensity)
	unsigned char 	loopOption;		// Holds the current phase option					(No Loop(0)/Sequential(1)/Random(2))
	unsigned char 	gainOption;		// Holds the current gain option					(Fixed/Sequential/Random)
	unsigned short 	manLEDLvl;		// Defines the DAC level for the manual LED case	(0 - 4095)
	unsigned char 	manLEDState;	// Defines the LED state 							(OFF/ON)
	unsigned char 	dutyCycle;		// Perform the algorithm in a duty-cycled manner	(OFF/ON)
	unsigned long 	onTime;			// Defines the on period of the duty cycle			(0 - 65535)
	unsigned long 	offTime;		// Defines the off period of the duty cycle			(0 - 65535)
	unsigned char	cmd;			// Defines the command to be executed				(start/stop sending data, update parameters, etc.)
	algorithm*		algo;			// Algorithm structure
} GUI;

/* END Algorithms */
#endif
