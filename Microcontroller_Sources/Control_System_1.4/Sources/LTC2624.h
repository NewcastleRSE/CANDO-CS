/* ###################################################################
**     Filename    : LTC2604.h
**     Project     : Control_System_1.4
**     Processor   : MK22FN512VDC12
**     Component   : LTC2604
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-03-06, 09:31, # CodeGen: 0
**     Abstract    :
**         	Contains function declarations the LTC2624 external DAC
** ###################################################################*/

#ifndef SOURCES_LTC2624_H_
#define SOURCES_LTC2624_H_

/*
 * LTC2624 - Device Driver API
 *
 * The CS/LD input is level triggered. When this input is taken
 * low, it acts as a chip-select signal, powering-on the SDI
 * and SCK buffers and enabling the input shift register. Data
 * (SDI input) is transferred at the next 24 rising SCK edges.
 * The 4-bit command, C3-C0, is loaded first; then the 4-bit
 * DAC address, A3-A0; and finally the 16-bit data word. The
 * data word comprises the 16-, 14- or 12-bit input code,
 * ordered MSB-to-LSB, followed by 0, 2 or 4 don’t-care bits
 * (LTC2604, LTC2614 and LTC2624 respectively). Data can
 * only be transferred to the device when the CS/LD signal
 * is low. The rising edge of CS/LD ends the data transfer
 * and causes the device to carry out the action specified in
 * the 24-bit input word.
 */

// Commands
typedef enum
{
	WRITE_n,				// Write to Input Register n
	UPDATE_n,				// Update (Power Up) DAC Register n
	WRITE_n_UPDATE_ALL,		// Write to Input Register n, Update (Power Up) All n
	WRITE_UPDATE_n,			// Write to and Update (Power Up) n
	POWER_DOWN_n,			// Power Down n
	NO_OPERATION = 0b1111	// No operation
} DAC_cmds;

// Addresses
typedef enum
{
	DAC_A,					// DAC A
	DAC_B,					// DAC B
	DAC_C,					// DAC C
	DAC_D,					// DAC D
	ALL_DACS = 0b1111		// All DACs
} DAC_addr;

typedef struct ltc2624 ltc2624;

extern ltc2624 ltc2624_DAC_A;
extern ltc2624 ltc2624_DAC_B;
extern ltc2624 ltc2624_DAC_C;
extern ltc2624 ltc2624_DAC_D;

void ltc2624_init(void);
void ltc2624_setValue(ltc2624 *ltc2624, unsigned short level);
void ltc2624_setValueAll(unsigned short level);
void ltc2624_update(ltc2624 *ltc2624);
void ltc2624_updateAll(void);
void ltc2624_powerDown(ltc2624 *ltc2624);
void ltc2624_powerDownAll(void);
void ltc2624_setValAndUpdate(ltc2624 *ltc2624, unsigned short level);
void ltc2624_setValAndUpdateAll(unsigned short level);

#endif /* SOURCES_LTC2624_H_ */
