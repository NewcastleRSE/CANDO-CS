/* ###################################################################
**     Filename    : Glossary.h
**     Project     : Control_System_1.4
**     Processor   : MK22FN512VDC12
**     Component   : Glossary
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-03-06, 09:31
**     Abstract    :
**         	Contains macros common to multiple files
** ###################################################################*/

#ifndef SOURCES_GLOSSARY_H_
#define SOURCES_GLOSSARY_H_

/*******************************************************************************
* Bit definitions for bitwise operations
********************************************************************************/
#define BITS_1		0x01
#define BITS_5		0x1F
#define BITS_6		0x3F
#define BITS_8		0xFF
#define BITS_9		0x1FF
#define BITS_10		0x2FF
#define BITS_12		0xFFF
#define BITS_24		0xFFFFFF

/*******************************************************************************
* Bit definitions for bit-shift operations
********************************************************************************/
#define BIT			1
#define BITS2		2
#define BITS3		3
#define BITS4		4
#define BITS5		5
#define BITS6		6
#define BITS7		7
#define BYTE 		8
#define BITS10		10
#define BITS12		12

/*******************************************************************************
* Ways of applying the stimulation and the recording. Both functions
* can be applied either through the microcontroller (uC) DAC and ADC,
* or through the recording and stimulation circuitry in the CMOS ASIC
* (ASIC).
********************************************************************************/
#define _uC 	0
#define _ASIC 	1

/*******************************************************************************
*
********************************************************************************/
#define DIS				0			// Disable
#define EN				1			// Enable
#define ZERO			0			// Value of zero
#define ONE				1			// Value of one
#define OFF				0			// Off
#define ON				1			// On
#define DAC_MAX_LEVEL	4095		// Maximum value for 12-bit DAC

#define G300			0			// Amplifier gain = 300
#define G385			1			// Amplifier gain = 385
#define G2100			2			// Amplifier gain = 2100
#define G4500			3			// Amplifier gain = 4000

#define CH0				0
#define CH1				1

#define LED_ALL			0
#define LED1			1
#define LED2			2
#define LED3			3
#define LED4			4
#define LED5			5
#define LED6			6
#define LED7			7

/*******************************************************************************
 * Error Codes
 *******************************************************************************/
enum error_codes
{
	OK,
	UART_TX_ERR,
	UART_RX_ERR,
	SPI0_TX_ERR,
	SPI0_RX_ERR,
	SPI1_TX_ERR,
	SPI1_RX_ERR
};

#endif /* SOURCES_GLOSSARY_H_ */
