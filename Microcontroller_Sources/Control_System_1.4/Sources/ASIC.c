/* ###################################################################
**     Filename    : ASIC.c
**     Project     : Control_System_1.4
**     Processor   : MK22FN512VDC12
**     Component   : ASIC
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-03-06, 09:31, # CodeGen: 0
**     Abstract    :
**         	Contains function definitions that provide control over the
**         	ASIC.
** ###################################################################*/

#include "ASIC.h"
#include "LED_Calibration.h"
#include "Glossary.h"
#include "CANDO3_interface.h"
#include "CANDO3_RST.h"
#include "CANDO3_CS1.h"
#include "CANDO3_CS2.h"
#include "CANDO3_CS3.h"
#include "CANDO3_CS4.h"

/*******************************************************************************
* ASIC Commands
********************************************************************************/
#define NO_COMMAND			0b000000
#define	LED_ON				0b000010
#define LED_OFF				0b000001
#define READ_LED			0b000011
#define SET_BRE				0b000100
#define SET_VLED			0b000101
#define READ_DIAG			0b000110
#define PROG_DELAY_DIAG		0b000111
#define PROG_OP_MEM			0b001000
#define LED_ALL_OFF			0b001001
#define RUN_MEM				0b001010
#define READ_LFP			0b010000
#define PROG_CLK_CNT		0b010001
#define	RESET_ANA			0b010011
#define SET_ANA				0b010100
#define CONFIG_REC			0b010101
#define PROG_ID				0b100000
#define DUMMY				0b111111

#define NO_DATA				0

enum ASIC_addr
{
	NO_ASIC, _ASIC1, _ASIC2, _ASIC3, _ASIC4
};

amplifier ASIC1_ch0 =
{
	.en_lp 	= 0,
	.bit_g0 = 0,
	.bit_g1 = 0,
	.pd		= 0
};

amplifier ASIC1_ch1 =
{
	.en_lp 	= 0,
	.bit_g0 = 0,
	.bit_g1 = 0,
	.pd		= 0
};

amplifier ASIC2_ch0 =
{
	.en_lp 	= 0,
	.bit_g0 = 0,
	.bit_g1 = 0,
	.pd		= 0
};

amplifier ASIC2_ch1 =
{
	.en_lp 	= 0,
	.bit_g0 = 0,
	.bit_g1 = 0,
	.pd		= 0
};

amplifier ASIC3_ch0 =
{
	.en_lp 	= 0,
	.bit_g0 = 0,
	.bit_g1 = 0,
	.pd		= 0
};

amplifier ASIC3_ch1 =
{
	.en_lp 	= 0,
	.bit_g0 = 0,
	.bit_g1 = 0,
	.pd		= 0
};

amplifier ASIC4_ch0 =
{
	.en_lp 	= 0,
	.bit_g0 = 0,
	.bit_g1 = 0,
	.pd		= 0
};

amplifier ASIC4_ch1 =
{
	.en_lp 	= 0,
	.bit_g0 = 0,
	.bit_g1 = 0,
	.pd		= 0
};

ASIC ASIC1 =
{
	.Optrode_addr 				= _ASIC1,
	.DAC_value 					= 0,
	.ADC_value					= 0,
	.LED_addr					= 0,
	.ch0						= &ASIC1_ch0,
	.ch1						= &ASIC1_ch1,
	.LED_status					= {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
	.command					= NO_COMMAND,
	.diag_delay					= 0,
	.mem_len					= 0,
	.master_delay				= 0,
	.on_off						= OFF,
	.fs_ratio_to_clk			= 0b0000010,
	.rec_config					= 0,
	.prog_ID					= 0,
	.burn						= 0
};

ASIC ASIC2 =
{
	.Optrode_addr 				= _ASIC2,
	.DAC_value 					= 0,
	.ADC_value					= 0,
	.LED_addr					= 0,
	.ch0						= &ASIC2_ch0,
	.ch1						= &ASIC2_ch1,
	.LED_status					= {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
	.command					= NO_COMMAND,
	.diag_delay					= 0,
	.mem_len					= 0,
	.master_delay				= 0,
	.on_off						= OFF,
	.fs_ratio_to_clk			= 0b0000010,
	.rec_config					= 0,
	.prog_ID					= 0,
	.burn						= 0
};

ASIC ASIC3 =
{
	.Optrode_addr 				= _ASIC3,
	.DAC_value 					= 0,
	.ADC_value					= 0,
	.LED_addr					= 0,
	.ch0						= &ASIC3_ch0,
	.ch1						= &ASIC3_ch1,
	.LED_status					= {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
	.command					= NO_COMMAND,
	.diag_delay					= 0,
	.mem_len					= 0,
	.master_delay				= 0,
	.on_off						= OFF,
	.fs_ratio_to_clk			= 0b0000010,
	.rec_config					= 0,
	.prog_ID					= 0,
	.burn						= 0
};

ASIC ASIC4 =
{
	.Optrode_addr 				= _ASIC4,
	.DAC_value 					= 0,
	.ADC_value					= 0,
	.LED_addr					= 0,
	.ch0						= &ASIC4_ch0,
	.ch1						= &ASIC4_ch1,
	.LED_status					= {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
	.command					= NO_COMMAND,
	.diag_delay					= 0,
	.mem_len					= 0,
	.master_delay				= 0,
	.on_off						= OFF,
	.fs_ratio_to_clk			= 0b0000010,
	.rec_config					= 0,
	.prog_ID					= 0,
	.burn						= 0
};

static unsigned long packet = 0;
unsigned long response = 0;

void enable_ASIC(ASIC *ASIC)
{
	if (ASIC->Optrode_addr == _ASIC1)
		CANDO3_CS1_SetVal();		// Set CS pin high
	else if (ASIC->Optrode_addr == _ASIC2)
		CANDO3_CS2_SetVal();		// Set CS pin high
	else if (ASIC->Optrode_addr == _ASIC3)
		CANDO3_CS3_SetVal();		// Set CS pin high
	else if (ASIC->Optrode_addr == _ASIC4)
		CANDO3_CS4_SetVal();		// Set CS pin high
	else
	{

	}
}

void disable_ASIC(ASIC *ASIC)
{
	if (ASIC->Optrode_addr == _ASIC1)
		CANDO3_CS1_ClrVal();		// Set CS pin high
	else if (ASIC->Optrode_addr == _ASIC2)
		CANDO3_CS2_ClrVal();		// Set CS pin high
	else if (ASIC->Optrode_addr == _ASIC3)
		CANDO3_CS3_ClrVal();		// Set CS pin high
	else if (ASIC->Optrode_addr == _ASIC4)
		CANDO3_CS4_ClrVal();		// Set CS pin high
	else
	{

	}
}

/*******************************************************************************
* Function: void resetASIC(void)
********************************************************************************
* Description:
* 	Called in order for an ASIC to start operating or restart.
* 	Initially the CS and RESET pins need to be set to high and low respectively.
* 	The RESET pin should then be pulsed (low->high->low).
*
* Parameters: void
* Returns: void
********************************************************************************/
void resetASIC(ASIC *ASIC)
{
	unsigned char i;

	enable_ASIC(ASIC);

	for(i = 0; i < 10; i++);	// Delay

	CANDO3_RST_SetVal();		// Set RESET pin high
	for(i = 0; i < 10; i++);	// Delay
	CANDO3_RST_ClrVal();
}

/*******************************************************************************
* Function: void rstAnalogue(void)
********************************************************************************
* Description:
* 	Resets the analogue electronic circuits
*
* Parameters: void
* Returns: void
********************************************************************************/
void rstAnalogue(ASIC *ASIC)
{
	unsigned long response;

	packet = ((((ASIC->Optrode_addr & BITS_6) << 18) | ((RESET_ANA & BITS_6) << 12) | (NO_DATA & BITS_12)) & BITS_24);

	send_packet(&packet);

	response = recv_packet();

//	CANDO3_interface_ClearRxBuf();
}

/*******************************************************************************
* Function: void setAnalogue(void)
********************************************************************************
* Description:
* 	Sets the analogue electronic circuits
*
* Parameters: void
* Returns: void
********************************************************************************/
void setAnalogue(ASIC *ASIC)
{
	unsigned long response;

	packet = ((((ASIC->Optrode_addr & BITS_6) << 18) | ((SET_ANA & BITS_6) << 12) | (NO_DATA & BITS_12)) & BITS_24);

	send_packet(&packet);

	response = recv_packet();

//	CANDO3_interface_ClearRxBuf();
}

/*******************************************************************************
* Function: void configRec(void)
********************************************************************************
* Description:
* 	Configure the front-end electronics.
*
*
* Parameters: void
* Returns: void
********************************************************************************/
void configRec(ASIC *ASIC)
{
	unsigned long response;

	packet = ((((ASIC->Optrode_addr & BITS_6) << 18) | ((CONFIG_REC & BITS_6) << 12) | (ASIC->rec_config & BITS_8)) & BITS_24);

	send_packet(&packet);

	response = recv_packet();

//	CANDO3_interface_ClearRxBuf();
}

/*******************************************************************************
* Function: void setSamplFreq(void)
********************************************************************************
* Description:
* 	Set the sampling frequency for the ADC module.
*
* Parameters: void
* Returns: void
********************************************************************************/
void setSamplFreq(ASIC *ASIC)
{
	unsigned long response;

	packet = ((((ASIC->Optrode_addr & BITS_6) << 18) | ((PROG_CLK_CNT & BITS_6) << 12) | (ASIC->fs_ratio_to_clk & BITS_8)) & BITS_24);

	send_packet(&packet);

	response = recv_packet();

//	CANDO3_interface_ClearRxBuf();
}

/*******************************************************************************
* Function: void readLFP(void)
********************************************************************************
* Description:
* 	Request for a recording to be performed by the chip
*
* Parameters: void
* Returns: void
********************************************************************************/
unsigned long readLFP(ASIC *ASIC)
{
	packet = ((((ASIC->Optrode_addr & BITS_6) << 18) | ((READ_LFP & BITS_6) << 12) | (NO_DATA & BITS_8)) & BITS_24);

	send_packet(&packet);

	return recv_packet();
}

/*******************************************************************************
* Function: void LED1_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED1_GND_tissue1(ASIC *ASIC)
{
	LEDOff(ASIC, LED1_1);
//	LEDOff(LED1_2);				// Turn memory cell off
//	LEDOff(LED1_3);				// Turn memory cell off
}

/*******************************************************************************
* Function: void LED2_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED2_GND_tissue1(ASIC *ASIC)
{
	LEDOff(ASIC, LED2_1);
//	LEDOff(LED2_2);				// Turn memory cell off
//	LEDOff(LED2_3);				// Turn memory cell off
}

/*******************************************************************************
* Function: void LED3_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED3_GND_tissue1(ASIC *ASIC)
{
	LEDOff(ASIC, LED3_1);
//	LEDOff(LED3_2);				// Turn memory cell off
//	LEDOff(LED3_3);				// Turn memory cell off
}

/*******************************************************************************
* Function: void LED4_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED4_GND_tissue1(ASIC *ASIC)
{
	LEDOff(ASIC, LED4_1);
//	LEDOff(LED4_2);				// Turn memory cell off
//	LEDOff(LED4_3);				// Turn memory cell off
}

/*******************************************************************************
* Function: void LED5_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED5_GND_tissue1(ASIC *ASIC)
{
	LEDOff(ASIC, LED5_1);
//	LEDOff(LED5_2);				// Turn memory cell off
//	LEDOff(LED5_3);				// Turn memory cell off
}

/*******************************************************************************
* Function: void LED6_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED6_GND_tissue1(ASIC *ASIC)
{
	LEDOff(ASIC, LED6_1);
//	LEDOff(LED6_2);				// Turn memory cell off
//	LEDOff(LED6_3);				// Turn memory cell off
}

/*******************************************************************************
* Function: void LED7_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED7_GND_tissue1(ASIC *ASIC)
{
	LEDOff(ASIC, LED7_1);
//	LEDOff(LED7_2);				// Turn memory cell off
//	LEDOff(LED7_3);				// Turn memory cell off
}

/*******************************************************************************
* Function: void LED1_forward(unsigned short ** stimVal)
********************************************************************************
* Description:
*	Turns an LED on and determines the current to flow through it by seting the
*	stimulation DAC value. The stimulation DAC value is determined by the value
*	store in the address where stimVal is pointing to.
*
* Parameters: (unsigned short ** stimVal) - Determines the stim DAC value
* Returns: void
********************************************************************************/
void LED1_forward(ASIC *ASIC)
{
//	unsigned short temp = 0, i = 0;

//	while(((*stimVal) > LEDCal[i]))
//		i++;

//	ASIC->DAC_value = LEDCal[i];	// Calibrated DAC value for linear current
//	ASIC->DAC_value = *stimVal;		// Determine DAC value
//	setStimDAC(ASIC);					// Set stimulation DAC value

	LEDOn(ASIC, LED1_1);
//	LEDOff(LED1_2);						// Turn memory cell off
//	LEDOff(LED1_3);						// Turn memory cell off
}

/*******************************************************************************
* Function: void LED2_forward(unsigned short ** stimVal)
********************************************************************************
* Description:
*	Turns an LED on and determines the current to flow through it by seting the
*	stimulation DAC value. The stimulation DAC value is determined by the value
*	store in the address where stimVal is pointing to.
*
* Parameters: (unsigned short ** stimVal) - Determines the stim DAC value
* Returns: void
********************************************************************************/
void LED2_forward(ASIC *ASIC)
{
//	unsigned short temp = 0, i = 0;

//	while(((**stimVal) > LEDCal[i]))
//		i++;
//
//	ASIC1.DAC_value = LEDCal[i];	// Calibrated DAC value for linear current
//	ASIC->DAC_value = *stimVal;		// Determine DAC value
//	setStimDAC(ASIC);					// Set stimulation DAC value

	LEDOn(ASIC, LED2_1);
//	LEDOff(LED2_2);						// Turn memory cell off
//	LEDOff(LED2_3);						// Turn memory cell off
}

/*******************************************************************************
* Function: void LED3_forward(unsigned short ** stimVal)
********************************************************************************
* Description:
*	Turns an LED on and determines the current to flow through it by seting the
*	stimulation DAC value. The stimulation DAC value is determined by the value
*	store in the address where stimVal is pointing to.
*
* Parameters: (unsigned short ** stimVal) - Determines the stim DAC value
* Returns: void
********************************************************************************/
void LED3_forward(ASIC *ASIC)
{
//	unsigned short temp = 0, i = 0;

//	while(((**stimVal) > LEDCal[i]))
//		i++;
//
//	ASIC1.DAC_value = LEDCal[i];	// Calibrated DAC value for linear current
//	ASIC->DAC_value = *stimVal;		// Determine DAC value
//	setStimDAC(ASIC);					// Set stimulation DAC value

	LEDOn(ASIC, LED3_1);
//	LEDOff(LED3_2);						// Turn memory cell off
//	LEDOff(LED3_3);						// Turn memory cell off
}

/*******************************************************************************
* Function: void LED4_forward(unsigned short ** stimVal)
********************************************************************************
* Description:
*	Turns an LED on and determines the current to flow through it by seting the
*	stimulation DAC value. The stimulation DAC value is determined by the value
*	store in the address where stimVal is pointing to.
*
* Parameters: (unsigned short ** stimVal) - Determines the stim DAC value
* Returns: void
********************************************************************************/
void LED4_forward(ASIC *ASIC)
{
//	unsigned short temp = 0, i = 0;

//	while(((**stimVal) > LEDCal[i]))
//		i++;
//
//	ASIC1.DAC_value = LEDCal[i];	// Calibrated DAC value for linear current
//	ASIC->DAC_value = *stimVal;		// Determine DAC value
//	setStimDAC(ASIC);					// Set stimulation DAC value

	LEDOn(ASIC, LED4_1);
//	LEDOff(LED4_2);						// Turn memory cell off
//	LEDOff(LED4_3);						// Turn memory cell off
}

/*******************************************************************************
* Function: void LED5_forward(unsigned short ** stimVal)
********************************************************************************
* Description:
*	Turns an LED on and determines the current to flow through it by seting the
*	stimulation DAC value. The stimulation DAC value is determined by the value
*	store in the address where stimVal is pointing to.
*
* Parameters: (unsigned short ** stimVal) - Determines the stim DAC value
* Returns: void
********************************************************************************/
void LED5_forward(ASIC *ASIC)
{
//	unsigned short temp = 0, i = 0;

//	while(((**stimVal) > LEDCal[i]))
//		i++;
//
//	ASIC1.DAC_value = LEDCal[i];	// Calibrated DAC value for linear current
//	ASIC->DAC_value = *stimVal;		// Determine DAC value
//	setStimDAC(ASIC);					// Set stimulation DAC value

	LEDOn(ASIC, LED5_1);
//	LEDOff(LED5_2);						// Turn memory cell off
//	LEDOff(LED5_3);						// Turn memory cell off
}

/*******************************************************************************
* Function: void LED6_forward(unsigned short ** stimVal)
********************************************************************************
* Description:
*	Turns an LED on and determines the current to flow through it by seting the
*	stimulation DAC value. The stimulation DAC value is determined by the value
*	store in the address where stimVal is pointing to.
*
* Parameters: (unsigned short ** stimVal) - Determines the stim DAC value
* Returns: void
********************************************************************************/
void LED6_forward(ASIC *ASIC)
{
//	unsigned short temp = 0, i = 0;

//	while(((**stimVal) > LEDCal[i]))
//		i++;
//
//	ASIC1.DAC_value = LEDCal[i];	// Calibrated DAC value for linear current
//	ASIC->DAC_value = *stimVal;		// Determine DAC value
//	setStimDAC(ASIC);					// Set stimulation DAC value

	LEDOn(ASIC, LED6_1);
//	LEDOff(LED6_2);						// Turn memory cell off
//	LEDOff(LED6_3);						// Turn memory cell off
}

/*******************************************************************************
* Function: void LED7_forward(unsigned short ** stimVal)
********************************************************************************
* Description:
*	Turns an LED on and determines the current to flow through it by seting the
*	stimulation DAC value. The stimulation DAC value is determined by the value
*	store in the address where stimVal is pointing to.
*
* Parameters: (unsigned short ** stimVal) - Determines the stim DAC value
* Returns: void
********************************************************************************/
void LED7_forward(ASIC *ASIC)
{
//	unsigned short temp = 0, i = 0;

//	while(((**stimVal) > LEDCal[i]))
//		i++;
//
//	ASIC1.DAC_value = LEDCal[i];	// Calibrated DAC value for linear current
//	ASIC->DAC_value = *stimVal;		// Determine DAC value
//	setStimDAC(ASIC);					// Set stimulation DAC value

	LEDOn(ASIC, LED7_1);
//	LEDOff(LED7_2);						// Turn memory cell off
//	LEDOff(LED7_3);						// Turn memory cell off
}

/*******************************************************************************
* Function: void setStimDAC(void)
********************************************************************************
* Description:
* 	Sets the stimulation DAC value
*
* Parameters: void
* Returns: void
********************************************************************************/
void setStimDAC(ASIC *ASIC)
{
	unsigned long response;

	// Construct packet to be transmitted.
	packet = ((((ASIC->Optrode_addr & BITS_6) << 18) | ((SET_VLED & BITS_6) << 12) | (NO_DATA & BITS_5)) & BITS_24);

	send_packet(&packet);
	response = recv_packet();

	CANDO3_interface_ClearRxBuf();

	// Construct packet to be transmitted.
	packet = ((((ASIC->Optrode_addr & BITS_6) << 18) | ((SET_VLED & BITS_6) << 12) | (ASIC->DAC_value & BITS_9)) & BITS_24);

	send_packet(&packet);
	response = recv_packet();

//	CANDO3_interface_ClearRxBuf();
}

/*******************************************************************************
* Function: void LEDOff(void)
********************************************************************************
* Description:
* 	Constructs the packet to be transmitted through SPI to the FSM of the optrode.
* 	The method will set a single memory cell - depending on the "LED_addr" member
* 	of the ASIC struct - in the H-tree of an LED to 0.
*
* Parameters: unsigned char mem_cell - memory cell to be written
* Returns: void
********************************************************************************/
void LEDOff(ASIC *ASIC, unsigned char mem_cell)
{
	unsigned long response;

	// Construct packet to be transmitted.
	packet = ((((ASIC->Optrode_addr & BITS_6) << 18) | ((LED_OFF & BITS_6) << 12) | (mem_cell & BITS_5)) & BITS_24);

	send_packet(&packet);
	response = recv_packet();

//	CANDO3_interface_ClearRxBuf();
}

/*******************************************************************************
* Function: void LEDOn(void)
********************************************************************************
* Description:
* 	Constructs the packet to be transmitted through SPI to the FSM of the optrode.
* 	The method will set a single memory cell - depending on the "LED_addr" member
* 	of the ASIC struct - in the H-tree of an LED to 1.
*
* Parameters: unsigned char mem_cell - memory cell to be written
* Returns: void
********************************************************************************/
void LEDOn(ASIC *ASIC, unsigned char mem_cell)
{
	unsigned long response;

	// Construct packet to be transmitted.
	packet = ((((ASIC->Optrode_addr & BITS_6) << 18) | ((LED_ON & BITS_6) << 12) | (mem_cell & BITS_5)) & BITS_24);

	send_packet(&packet);

	response = recv_packet();

//	CANDO3_interface_ClearRxBuf();
}

unsigned long dummy(ASIC *ASIC)
{
	// Construct packet to be transmitted.
	packet = ((((ASIC->Optrode_addr & BITS_6) << 18) | ((DUMMY & BITS_6) << 12) | (NO_DATA & BITS_5)) & BITS_24);

	send_packet(&packet);

	return recv_packet();
}

/**************************************************************************************************
* Function: void send_packet(void)
***************************************************************************************************
* Description:
* 	This method sends a packet over to the FSM through SPI. The packet is transmitted
* 	as 3 separate bytes. Packets are constructed in the functions representing 	a
* 	command of the optrode.
*
* 	Standard communication packet:
* 	------------------------------------------------------------------------------------------------
* 	|--------------ACK3-------------|--------------ACK2-------------|--------------ACK1-------------|
* 	| 23| 22| 21| 20| 19| 18| 17| 16| 15| 14| 13| 12| 11| 10| 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
* 	|---------Addr----------|--------Command--------|---------------------Data----------------------|
* 	-------------------------------------------------------------------------------------------------
*
*	- Data: supplementary data needed for each individual function (e.g LED address, DAC value, etc.).
*			What these bits represent differs for various functions.
*	- Command: command to be executed by the optrode's FSM
*	- Addr: Optrode address to receive the packet
*
* Parameters: unsigned long * packet - command packet to be transmitted to the ASIC
* Returns: void
***************************************************************************************************/
void send_packet(unsigned long * packet)
{
	unsigned char response = 0;

	response = 0;

	CANDO3_interface_SendChar((*packet & BITS_8));	// Send bits 1-8 of a data-packet over SPI
	*packet = *packet >> 8;							// Shift packet by 8 bits to the right

	CANDO3_interface_SendChar((*packet & BITS_8)); // Send bits 9-16 of a data-packet over SPI
	*packet = *packet >> 8;							// Shift packet by 8 bits to the right

	CANDO3_interface_SendChar((*packet & BITS_8)); // Send bits 16-24 of a data-packet over SPI
	*packet = *packet >> 8;							// Clear packet data
}

unsigned long recv_packet(void)
{
	unsigned long packet = 0;
	unsigned char data = 0;

	CANDO3_interface_RecvChar(&data);
	packet = data;
	CANDO3_interface_RecvChar(&data);
	packet |= (data << BYTE);
	CANDO3_interface_RecvChar(&data);
	packet |= (data << 16);

	return packet;
}
