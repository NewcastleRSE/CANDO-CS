/* ###################################################################
**     Filename    : IO.c
**     Project     : Control_System_1.1
**     Processor   : MK22FN512VDC12
**     Component   : IO
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-03-06, 09:31, # CodeGen: 0
**     Abstract    :
**         	Contains function definitions for the functions that
**         	provide control of the input and output circuitry of the
**         	system.
** ###################################################################*/

#include <stdio.h>
#include "IO.h"
#include "DA1.h"
#include "AD1.h"
#include "Glossary.h"
#include "CANDO3_interface.h"
#include "ASIC.h"
#include "LED_Calibration.h"
#include "WAIT1.h"

#define BITS_9_TO_6		0.123288f
#define READ_LFP_CMD	0b010000
#define NO_CMD			0
#define CMD_MASK		0x3F000
#define RESP_MASK		0x400
#define DATA_MASK		0x3FF

unsigned char stim_method = _uC, rec_method = _uC, rec_channel = CH0, LED_number = LED1, lin_drv = OFF;
unsigned char buffer_index, prev_buffer_index, timeout_cnt = 0, uart_tx = 0, tx_cnt;
unsigned short ch0_reg = 0, ch1_reg = 0, prev_stim_val = 0;

//unsigned short cnt_tot = 0, cnt_rec = 0, cnt_rst = 0, cnt_non = 0;

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
void init_rec(ASIC *ASIC)
{
	setAnalogue(ASIC);

	configRec(ASIC);

	ASIC->fs_ratio_to_clk = 0b000111;
//	ASIC->fs_ratio_to_clk = 0b001000;
	setSamplFreq(ASIC);
}

void set_amplifier_ch0(ASIC *ASIC, unsigned char gain,
		unsigned char en_lp, unsigned char pd)
{
	switch (gain)
	{
		case(G300):
			ASIC->ch0->bit_g0 = ONE;
			ASIC->ch0->bit_g1 = ONE;
			break;

		case(G385):
			ASIC->ch0->bit_g0 = ZERO;
			ASIC->ch0->bit_g1 = ONE;
			break;

		case(G2100):
			ASIC->ch0->bit_g0 = ONE;
			ASIC->ch0->bit_g1 = ZERO;
			break;

		case(G4500):
			ASIC->ch0->bit_g0 = ZERO;
			ASIC->ch0->bit_g1 = ZERO;
			break;

		default:
			ASIC->ch0->bit_g0 = ONE;
			ASIC->ch0->bit_g1 = ONE;
			break;
	}

	ASIC->ch0->en_lp = en_lp;
	ASIC->ch0->pd = pd;

	ASIC->rec_config &= 0xF0;
	ASIC->rec_config |= (ASIC1.ch0->pd << BITS3) | (ASIC1.ch0->en_lp << BITS2) | (ASIC1.ch0->bit_g1 << BIT) | (ASIC1.ch0->bit_g0);

	configRec(ASIC);
}

void set_amplifier_ch1(ASIC *ASIC, unsigned char gain,
		unsigned char en_lp, unsigned char pd)
{
	switch (gain)
	{
		case(G300):
			ASIC->ch1->bit_g0 = ONE;
			ASIC->ch1->bit_g1 = ONE;
			break;

		case(G385):
			ASIC->ch1->bit_g0 = ZERO;
			ASIC->ch1->bit_g1 = ONE;
			break;

		case(G2100):
			ASIC->ch1->bit_g0 = ONE;
			ASIC->ch1->bit_g1 = ZERO;
			break;

		case(G4500):
			ASIC->ch1->bit_g0 = ZERO;
			ASIC->ch1->bit_g1 = ZERO;
			break;

		default:
			ASIC->ch1->bit_g0 = ONE;
			ASIC->ch1->bit_g1 = ONE;
			break;
	}

	ASIC->ch1->en_lp = en_lp;
	ASIC->ch1->pd = pd;

	ASIC->rec_config &= 0x0F;
	ASIC->rec_config |= (ASIC->ch1->pd << BITS7) | (ASIC->ch1->en_lp << BITS6) | (ASIC->ch1->bit_g1 << BITS5) | (ASIC->ch1->bit_g0 << BITS4);

	configRec(ASIC);
}

void record(unsigned short *recVal, unsigned char recMethod)
{
//	cnt_tot++;

	if (recMethod == _uC)
	{
//		cnt_rec++;

		AD1_Measure(TRUE);                  // Enable ADC
		AD1_GetValue8(recVal);        		// Obtain measurement (8 bits)

		uart_tx = EN;
	}
	else if (recMethod == _ASIC)
	{
		unsigned long response = 0;
		unsigned char cmd;

//		disable_ASIC(&ASIC2);
//		WAIT1_Waitus(50);
//		enable_ASIC(&ASIC1);
//		WAIT1_Waitus(50);
//		cnt_rec++;

//		CANDO3_interface_ClearRxBuf();

//		readLFP(&ASIC1);
//		readLFP(&ASIC1);
		cmd = NO_CMD;
		tx_cnt = ZERO;

		while (cmd != READ_LFP_CMD && tx_cnt <=5)
		{
			response = readLFP(&ASIC1);

			cmd = (response & CMD_MASK) >> BITS12;

			tx_cnt++;
		}

		if (cmd == READ_LFP_CMD)
		{
			// Obtain buffer index from received packet
			buffer_index = (response & RESP_MASK) >> BITS10;

			// Check if the buffer index is the same
			if (buffer_index != prev_buffer_index)
			{
				// Channel 0
				if(buffer_index==CH0)
					ch0_reg = response & DATA_MASK;

				// Channel 1
				if(buffer_index==CH1)
					ch1_reg = response & DATA_MASK;

				// Check which channel has been selected on the GUI
				if (rec_channel == CH0)
					*recVal = ch0_reg;
				else if (rec_channel == CH1)
					*recVal = ch1_reg;
				else
				{

				}
			}

			// Update current buffer index
			prev_buffer_index = buffer_index;

			/*
			 * The flag determines when data transmission over UART should occur
			 * It was introduced because the sampling frequency of the ASIC is half of the uC. The flag
			 * is toggled at every interrupt in order to avoid duplicate data being sent over UART.
			 */
			uart_tx = !uart_tx;
		}
		else if (cmd == NO_CMD)
		{
//			cnt_rst++;

			resetASIC(&ASIC1);
			setAnalogue(&ASIC1);
			configRec(&ASIC1);
			setSamplFreq(&ASIC1);

			// Add error message plus amount of times it attempted to receive a packet.

//			CANDO3_interface_ClearRxBuf();
		}
		else
		{
//			cnt_non++;
//			ch0_reg = 0;
//			ch1_reg = 0;
			if (rec_channel == CH0)
				*recVal = ch0_reg;
			else if (rec_channel == CH1)
				*recVal = ch1_reg;
			else
			{

			}
//			CANDO3_interface_ClearRxBuf();
		}

//		WAIT1_Waitus(50);

//		disable_ASIC(&ASIC1);
//		enable_ASIC(&ASIC2);
//		WAIT1_Waitus(10);
	}
	else
	{

	}

//	if (cnt_tot == 10000)
//	{
////		printf("Total ISR executions: %d\nRecording commands: %d\nChip Resets: %d\nNo Commands: %d\n\n",
////				cnt_tot, cnt_rec, cnt_rst, cnt_non);
//		cnt_tot = 0;
//		cnt_rec = 0;
//		cnt_rst = 0;
//		cnt_non = 0;
//	}
}

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
void stimulate(unsigned short *stimVal, unsigned char stimMethod)
{
	if (stimMethod == _uC)			// Stimulate using the uC DAC
	{
		/*
		 * Set the DAC according to the output of the algorithm stored
		 * in stim_reg (12 bits)
		 */
		DA1_SetValue(stimVal);
	}
	else if (stimMethod == _ASIC)	// Stimulate using the ASIC DAC
	{
//		disable_ASIC(&ASIC1);
//			WAIT1_Waitus(50);
//			enable_ASIC(&ASIC4);
//			WAIT1_Waitus(50);
//			enable_ASIC(&ASIC2);
//
//		WAIT1_Waitus(50);

		if (*stimVal != prev_stim_val)
		{
			if (*stimVal)
			{
				// Add LED Linear Driving Option
				if (lin_drv)
				{
					unsigned char index = *stimVal * BITS_9_TO_6; // stimVal * 63 / 511.0f;
					*stimVal =  LEDCal[index];
				}
				else
					*stimVal = *stimVal >> BITS3;

				ASIC1.DAC_value = *stimVal;		// Determine DAC value
				setStimDAC(&ASIC1);

				switch(LED_number)
				{
					case(LED_ALL):
						LED2_forward(&ASIC1);
						LED3_forward(&ASIC1);
						LED4_forward(&ASIC1);
						LED5_forward(&ASIC1);
						LED6_forward(&ASIC1);
	//					LED7_forward(&ASIC1);
						break;

					case(LED1):
						LED1_forward(&ASIC1);
						break;

					case(LED2):
						LED2_forward(&ASIC1);
						break;

					case(LED3):
						LED3_forward(&ASIC1);
						break;

					case(LED4):
						LED4_forward(&ASIC1);
						break;

					case(LED5):
						LED5_forward(&ASIC1);
						break;

					case(LED6):
						LED6_forward(&ASIC1);
						break;

					case(LED7):
						LED7_forward(&ASIC1);
						break;

					default:

						break;
				}
			}
			else
			{
				switch(LED_number)
				{
					case(LED_ALL):
						LED2_GND_tissue1(&ASIC1);
						LED3_GND_tissue1(&ASIC1);
						LED4_GND_tissue1(&ASIC1);
						LED5_GND_tissue1(&ASIC1);
						LED6_GND_tissue1(&ASIC1);
	//					LED7_GND_tissue1(&ASIC1);
						break;

					case(LED1):
						LED1_GND_tissue1(&ASIC1);
						break;

					case(LED2):
						LED2_GND_tissue1(&ASIC1);
						break;

					case(LED3):
						LED3_GND_tissue1(&ASIC1);
						break;

					case(LED4):
						LED4_GND_tissue1(&ASIC1);
						break;

					case(LED5):
						LED5_GND_tissue1(&ASIC1);
						break;

					case(LED6):
						LED6_GND_tissue1(&ASIC1);
						break;

					case(LED7):
						LED7_GND_tissue1(&ASIC1);
						break;

					default:

						break;
				}
			}

			prev_stim_val = *stimVal;
		}
		else
		{
			// Add error handling code
		}

//		disable_ASIC(&ASIC2);
////		WAIT1_Waitus(10);
//		enable_ASIC(&ASIC1);
	}
}

void choose_device(unsigned char param[])
{
	rec_method = param[0];
	stim_method = param[1];
	rec_channel = param[2];
	LED_number = param[3];
	set_amplifier_ch0(&ASIC1, param[4], 1, 0);
	set_amplifier_ch1(&ASIC1, param[4], 1, 0);
}
