/* ###################################################################
**     Filename    : Events.c
**     Project     : Control_System_1.4
**     Processor   : MK22FN512VDC12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-03-06, 09:31, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMI - void Cpu_OnNMI(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "Init_Config.h"
#include "PDD_Includes.h"

#include "Algorithms.h"
#include "Phase_Shift_Algorithm.h"
#include "SW_Info.h"
#include "IO.h"
#include "Glossary.h"
#include "LTC2624.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UART_TX_PACKETS 10
#define UART_RX_PACKETS 35

unsigned char start = 0, quick_update = 0, algo_on_off_flag = OFF, cycle_comp = ZERO, cycle_cnt = ZERO, read_packet = FALSE;
unsigned short rec_reg = 0, stim_reg = 0;
float on_off_cntr = 0;

unsigned short uart_chars_in_rx_buff;

/*
 * TX buffer contents
 *
 * Byte 1:	Recorded data 			(10 bits ASIC/8 bits MCU)
 * Byte 2: 	Recorded data cont.		(10 bits ASIC)
 * Byte 3: 	Algorithm output		(12 bits)
 * Byte 4: 	Algorithm output cont.	(12 bits)
 * Byte 5: 	Phase condition			(9 bits)
 * Byte 6:  Phase condition cont. 	(9 bits)
 * Byte 6:	Cycles completed		(1 bit)
 * Byte 6:	Algo option				(1 bit)
 * Byte 6:  Algo On/Off status		(1 bit)
 * Byte 7:  Gain					(8 bits)
 * Byte 8:  Set Int value			(12 bits)
 * Byte 9: Set Int value	cont.	(12 bits)
 */
unsigned char 	uart_tx_buf[UART_TX_PACKETS] 	= {0};

/*
 * RX buffer contents
 *
 * Byte 1: 	Algorithm option 			(Original/Set Intensity) 	- Default: Original
 * Byte 2: 	Phase options				(Fixed/Sequential/Random) 	- Default: Fixed
 * Byte 3: 	Phase condition				(0-7)						- Default: 0
 * Byte 4: 	Gain options				(Fixed/Sequential/Random) 	- Default: Fixed
 * Byte 5: 	Gain value					(1-255)						- Default: 1
 * Byte 6: 	Central frequency			(10 Hz)						- Default: 10
 * Byte 7: 	Threshold					(0-65535)					- Default: 0
 * Byte 8: 	Set intensity value 		(0-4096)					- Default: 1000
 * Byte 9:  Set intensity value cont.
 * Byte 10:	Kernel length				(?-?)						- Default: 512
 * Byte 11: Kernel length cont.
 * Byte 12: Duty cycle					(Off/On)					- Default: Off
 * Byte 13: On-time						(1s - 1000s)				- Default: 1s
 * Byte 14: On-time cont.
 * Byte 15: Off-time					(100ms - 1000s)				- Default: 1s
 * Byte 16: Off-time cont.
 * Byte 17: Manual Algo/LED control 	(Algo/LED)					- Default: Algo
 * Byte 18: Manual LED DAC level		(0-4095)					- Default: 0
 * Byte 19: Manual LED DAC level cont.
 */
unsigned char uart_rx_buf[UART_RX_PACKETS] = {0};


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMI (module Events)
**
**     Component   :  Cpu [MK22FN512DC12]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMI(void)
{

}

/*
** ===================================================================
**     Event       :  ALGO_OnInterrupt (module Events)
**
**     Component   :  ALGO [FreeCntr_LDD]
*/
/*!
**     @brief
**         This event is called when a compare matches the counter
**         value (if compare or reload is selected as a interrupt
**         source) or a counter overflows (for free-running devices).
**         Component and OnInterrupt event must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt service/event] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void ALGO_OnInterrupt(LDD_TUserData *UserDataPtr)
{
	/*
	 * tx_error: holds the status of tx communication. A value of zero is expected when no errors occur.
	 * bytes_sent: holds the number of bytes received through UART
	 */

	unsigned char tx_error = 0;
	unsigned short bytes_sent = 0;
	float DAC_phase = 0;

	/*
	 * The start flag is set when the start button is pressed on the GUI. Until the flag is set only the
	 * recording will be performed and the UART tx and rx operations. Once the flag is set the algorithm
	 * and stimulation operations are also enabled.
	 */
	if (start)
	{
		record(&rec_reg, rec_method);								// Perform a recording

		/*
		 * Determines whether a predetermined on/off cycling will be performed or a manual control instead.
		 * This is also determined by the "Manual Override" button on the GUI.
		 */
		cycle_comp = ZERO;

		if (GUIParams.dutyCycle == ON)
		{
			// On time
			if (on_off_cntr < GUIParams.onTime)
			{
				// Algorithm operation was chosen
				if (GUIParams.manLEDOption == ALGO)
				{
					DConnector_2_SetVal();
					phase_shift(&rec_reg, &stim_reg);			// Perform the phase shift algorithm
					DConnector_2_ClrVal();

					stimulate(&stim_reg, stim_method);			// Perform the stimulation
					algo_on_off_flag = ON;						// Set the on/off flag (Algorithm on)
				}
				// Manual control of the LED controlled by the user
				else if (GUIParams.manLEDOption == MANUAL)
				{
					stim_reg = GUIParams.manLEDLvl;				// Sets the stimulation level according to
																// the value passed from the GUI (slider)
					stimulate(&stim_reg, stim_method);			// Perform the stimulation
					algo_on_off_flag = OFF;						// Clear the on/off flag (Algorithm off)
				}
				// Should not reach here (no such option)
				else
				{
					// Turning the LED off for safety.
					stim_reg = 0;
					stimulate(&stim_reg, stim_method);

					// Setting the flag and GUI options
					algo_on_off_flag = OFF;
					GUIParams.manLEDOption = MANUAL;
					GUIParams.manLEDState = OFF;
				}
			}
			// Off time
			else
			{
				stim_reg = 0;									// Set the stimulation register to 0
				stimulate(&stim_reg, stim_method);				// Turn the LED off
				algo_on_off_flag = OFF;							// Clear the algorithm flag (algorithm off)

				if (on_off_cntr >= (GUIParams.onTime + GUIParams.offTime))
				{
					// Reset the counter and determine the new algorithm parameters
					on_off_cntr = 0;								// Reset the counter

					if (++cycle_cnt == size)
					{
						cycle_comp = ONE;
						cycle_cnt = ZERO;
					}

					// Algorithm operation
					if (GUIParams.manLEDOption == ALGO)
					{
						size = calc_param_combs();
						// Sequential: The algorithm parameters are updated sequentially
						if (GUIParams.loopOption == SEQ)
							sequential();
						// Pseudo-random: The algorithm parameters are updated in a random order
						else if (GUIParams.loopOption == RAND)
							pseudo_random();
						// No loop: The algorithm parameters are not updated, and only the current parameter is used
						else if (GUIParams.loopOption == NO_LOOP)
						{
							// Currently nothing needs to be done here
						}
						// Shouldn't reach this point
						else
						{
							// Turning the LED off for safety
							stim_reg = 0;
							stimulate(&stim_reg, stim_method);

							// Setting the flag and GUI options
							algo_on_off_flag = OFF;
							GUIParams.manLEDOption = MANUAL;
							GUIParams.manLEDState = OFF;
						}
					}
				}
			}

			on_off_cntr += Ts;									// Increment counter
		}
		// The "Manual Override" button is pressed and the user takes control
		else
		{
			cycle_comp = ZERO;
			// Algorithm option
			if (GUIParams.manLEDOption == ALGO)
			{
				// The LED ON button is pressed on the GUI
				if (GUIParams.manLEDState == ON)
				{
					phase_shift(&rec_reg, &stim_reg);			// Perform the phase shift algorithm

					stimulate(&stim_reg, stim_method);					// Apply the stimulation
					algo_on_off_flag = ON;						// Set the algorithm flag
				}
				// The LED OFF button is pressed on the GUI
				else
				{
					// Turning the LED off for safety
					stim_reg = 0;
					stimulate(&stim_reg, stim_method);

					// Setting the flag and GUI options
					algo_on_off_flag = OFF;
					GUIParams.manLEDState = OFF;
				}
			}
			// Manual LED control
			else if (GUIParams.manLEDOption == MANUAL)
			{
				manual_LED(stim_method);
				algo_on_off_flag = OFF;
			}
			// Shouldn't come here
			else
			{
				// Turning the LED off for safety
				stim_reg = 0;
				stimulate(&stim_reg, stim_method);

				// Setting the flag and GUI options
				algo_on_off_flag = OFF;
				GUIParams.manLEDState = OFF;
			}
		}

		uart_tx_buf[0] = rec_reg & 0xFF;											// Recorded data
		uart_tx_buf[1] = (rec_reg & 0x0300) >> BYTE;
		uart_tx_buf[2] = stim_reg & 0xFF;											// First 8-bits (0-7) of the DAC value
		uart_tx_buf[3] = (stim_reg & 0x0F00) >> BYTE;								// Bits 8-11 of the DAC value
		uart_tx_buf[4] = GUIParams.algo->phaseShift.phaseValue & 0x00FF;			// First 8-bits (0-7) of the phase value
		uart_tx_buf[5] = (GUIParams.algo->phaseShift.phaseValue & 0x0100) >> BYTE;	// Bit 9 of the phase value
		uart_tx_buf[5] += (cycle_comp & 0x01) << 5;
		uart_tx_buf[5] += (GUIParams.algoOption & 0x01) << 6;						// This bit determines which algorithm is being used
		uart_tx_buf[5] += (algo_on_off_flag & 0x01) << 7;							// This bit determines if the algorithm is on or off
		uart_tx_buf[6] = GUIParams.algo->phaseShift.gainValue;						// Holds the gain value
		uart_tx_buf[7] = GUIParams.algo->phaseShift.setIntVal & 0x00FF;				// Bits (0-7) of the set intensity value
		uart_tx_buf[8] = (GUIParams.algo->phaseShift.setIntVal & 0x0F00) >> BYTE;	// Bits (8-11) of the set intensity value

		if (uart_tx)
			/*
			 * Transmit the data stored in the UART tx buffer.
			 * The status of the transmission is stored in tx_error.
			 */
			tx_error = AS1_SendBlock(uart_tx_buf, UART_TX_PACKETS, &bytes_sent);

		/*
		 * Check if the error status and bytes transmitted are as expected.
		 * If otherwise, handle the error.
		 */
		if (tx_error || (bytes_sent != UART_TX_PACKETS))
		{
			// Add error handling code
		}
	}
	// Stop button is pressed
	else
	{
		// Turn the LED off
		stim_reg = 0;
		stimulate(&stim_reg, _uC);
		
		// Reset the parameter cycle completion counter and flag
		cycle_cnt = 0;
		cycle_comp = ZERO;
	}

	uart_chars_in_rx_buff = AS1_GetCharsInRxBuf();

	if (uart_chars_in_rx_buff >= UART_RX_PACKETS)
	{
		/*
		 * rx_error: holds the status of rx communication. A value of zero is expected when no errors occur.
		 * bytes_rec: holds the number of bytes received through UART
		 */
		unsigned char rx_error = 0;
		unsigned short bytes_rec = 0;

		/*
		 * Receive the data through UART and store in the UART rx buffer.
		 * The status of the reception is stored in rx_error.
		 */
		rx_error = AS1_RecvBlock(uart_rx_buf, UART_RX_PACKETS, &bytes_rec);

		/*
		 * Check if the error status and bytes received are as expected.
		 * If otherwise, handle the error.
		 */
		if (rx_error || (bytes_rec != UART_RX_PACKETS))
		{
			// Add error handling code
		}

		switch(uart_rx_buf[UART_RX_PACKETS-1])
		{
			// Start sending data
			case(1):
				start = 1;
				break;

			// Stop sending data
			case(2):
				start = 0;
				AS1_ClearRxBuf();
				reset_params();		  					   
				break;

			// Send version info
			case(5):
				send_SW_version();
				break;

			// Choose ASIC or uC
			case(7):
				choose_device(uart_rx_buf);
				break;

			// Update parameters
			case(10):
				quick_update = 0;
				update_param(uart_rx_buf, quick_update);
				break;

			// Quick update of parameters
			case(11):
				quick_update = 1;
				update_param(uart_rx_buf, quick_update);
				break;

			// Shouldn't reach this point (error handler)
			default:

				break;
		}

		read_packet = 1;

	}
	else if (read_packet && uart_chars_in_rx_buff > 0 && uart_chars_in_rx_buff < UART_RX_PACKETS)
	{
		AS1_ClearRxBuf();

		read_packet = 0;
	}
	else
	{
		read_packet = 0;
	}
}

/*
** ===================================================================
**     Event       :  AS1_OnError (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnError(void)
{

}

/*
** ===================================================================
**     Event       :  CANDO3_interface_OnError (module Events)
**
**     Component   :  CANDO3_interface [SynchroMaster]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void CANDO3_interface_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  DAC_interface_OnError (module Events)
**
**     Component   :  DAC_interface [SynchroMaster]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void DAC_interface_OnError(void)
{
  /* Write your code here ... */
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
