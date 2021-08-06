/* ###################################################################
**     Filename    : ASIC.h
**     Project     : Control_System_1.4
**     Processor   : MK22FN512VDC12
**     Component   : ASIC
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-03-06, 09:31, # CodeGen: 0
**     Abstract    :
**         	Contains function declarations that provide control over
**         	the	ASIC.
** ###################################################################*/

#ifndef __ASIC_H
#define __ASIC_H
/* MODULE ASIC */

/*******************************************************************************
* LED addresses
********************************************************************************/
enum
{
	NO_LED_ADDR,			// 0
	LED1_1, LED1_2, LED1_3,	// LED1 addresses: 1-3
	LED2_1, LED2_2, LED2_3,	// LED2 addresses: 4-6
	LED3_1, LED3_2, LED3_3,	// LED3 addresses: 7-9
	LED4_1, LED4_2, LED4_3,	// LED4 addresses: 10-12
	LED5_1, LED5_2, LED5_3,	// LED5 addresses: 13-15
	LED6_1, LED6_2, LED6_3,	// LED6 addresses: 16-18
	LED7_1, LED7_2, LED7_3,	// LED7 addresses: 19-21
	LED8_1, LED8_2, LED8_3,	// LED8 addresses: 22-24
	NUMBER_OF_LEDS = 8
} led_addr;

typedef struct amplifier amplifier;
typedef struct ASIC ASIC;

struct ASIC
{
	const unsigned char Optrode_addr;
	unsigned short 		DAC_value;
	unsigned short		ADC_value;
	unsigned char 		LED_addr;
	amplifier*			ch0;
	amplifier*			ch1;
	unsigned char 		LED_status[NUMBER_OF_LEDS];
	unsigned char		command;
	unsigned short		diag_delay;
	unsigned char		mem_len;
	unsigned char   	master_delay;
	unsigned char 		on_off;
	unsigned char		fs_ratio_to_clk;
	unsigned char		rec_config;
	unsigned char		prog_ID;
	unsigned char		burn;
};

struct amplifier
{
	unsigned char en_lp;
	unsigned char bit_g0;
	unsigned char bit_g1;
	unsigned char pd;
};

extern struct ASIC ASIC1;
extern struct ASIC ASIC2;
extern struct ASIC ASIC3;
extern struct ASIC ASIC4;

extern unsigned long response;

void enable_ASIC(ASIC *ASIC);
void disable_ASIC(ASIC *ASIC);

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
void resetASIC(ASIC *ASIC);

/*******************************************************************************
* Function: void rstAnalogue(void)
********************************************************************************
* Description:
* 	Resets the analogue electronic circuits
*
* Parameters: void
* Returns: void
********************************************************************************/
void rstAnalogue(ASIC *ASIC);

/*******************************************************************************
* Function: void setAnalogue(void)
********************************************************************************
* Description:
* 	Sets the analogue electronic circuits
*
* Parameters: void
* Returns: void
********************************************************************************/
void setAnalogue(ASIC *ASIC);

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
void configRec(ASIC *ASIC);

/*******************************************************************************
* Function: void setSamplFreq(void)
********************************************************************************
* Description:
* 	Set the sampling frequency for the ADC module.
*
* Parameters: void
* Returns: void
********************************************************************************/
void setSamplFreq(ASIC *ASIC);

/*******************************************************************************
* Function: void readLFP(void)
********************************************************************************
* Description:
* 	Request for a recording to be performed by the chip
*
* Parameters: void
* Returns: unsigned long response - returns the data received from the ASIC
********************************************************************************/
unsigned long readLFP(ASIC *ASIC);

/*******************************************************************************
* Function: void LED1_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED1_GND_tissue1(ASIC *ASIC);

/*******************************************************************************
* Function: void LED2_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED2_GND_tissue1(ASIC *ASIC);

/*******************************************************************************
* Function: void LED3_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED3_GND_tissue1(ASIC *ASIC);

/*******************************************************************************
* Function: void LED4_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED4_GND_tissue1(ASIC *ASIC);

/*******************************************************************************
* Function: void LED5_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED5_GND_tissue1(ASIC *ASIC);

/*******************************************************************************
* Function: void LED6_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED6_GND_tissue1(ASIC *ASIC);

/*******************************************************************************
* Function: void LED7_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED7_GND_tissue1(ASIC *ASIC);

/*******************************************************************************
* Function: void LED8_GND_tissue1(void)
********************************************************************************
* Description:
* 	Turns an LED off by grounding the anode and cathode contacts.
*
* Parameters: void
* Returns: void
********************************************************************************/
void LED8_GND_tissue1(ASIC *ASIC);

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
void LED1_forward(ASIC *ASIC);

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
void LED2_forward(ASIC *ASIC);

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
void LED3_forward(ASIC *ASIC);

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
void LED4_forward(ASIC *ASIC);

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
void LED5_forward(ASIC *ASIC);

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
void LED6_forward(ASIC *ASIC);

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
void LED7_forward(ASIC *ASIC);

/*******************************************************************************
* Function: void LED8_forward(unsigned short ** stimVal)
********************************************************************************
* Description:
*	Turns an LED on and determines the current to flow through it by seting the
*	stimulation DAC value. The stimulation DAC value is determined by the value
*	store in the address where stimVal is pointing to.
*
* Parameters: (unsigned short ** stimVal) - Determines the stim DAC value
* Returns: void
********************************************************************************/
void LED8_forward(ASIC *ASIC);

/*******************************************************************************
* Function: void setStimDAC(void)
********************************************************************************
* Description:
* 	Sets the stimulation DAC value
*
* Parameters: void
* Returns: void
********************************************************************************/
void setStimDAC(ASIC *ASIC);

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
void LEDOff(ASIC *ASIC, unsigned char mem_cell);

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
void LEDOn(ASIC *ASIC, unsigned char mem_cell);

unsigned long dummy(ASIC *ASIC);

/**************************************************************************************************
* Function: void sendPacket(void)
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
* Parameters: void
* Returns: void
***************************************************************************************************/
void send_packet(unsigned long * packet);

unsigned long recv_packet(void);

/* END ASIC */
#endif
