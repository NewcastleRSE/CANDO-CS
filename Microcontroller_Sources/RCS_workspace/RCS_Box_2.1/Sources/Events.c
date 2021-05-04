/* ###################################################################
**     Filename    : Events.c
**     Project     : RCS_Box_2.1
**     Processor   : MK22FN512VLH12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-01-29, 16:05, # CodeGen: 0
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

#include "Phase_Shift_Algorithm.h"
#include "SW_Info.h"

#ifdef __cplusplus
extern "C" {
#endif 

unsigned short rec_reg = 0;
unsigned short stim_reg = 0;
unsigned char uart_rx_buf[13] = {0};
unsigned char uart_tx_buf[6] = {0};

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
	unsigned char tx_error = 0, bytes_sent = 0;

	AD1_Measure(TRUE);                                  // Enable ADC
	AD1_GetValue8(&rec_reg);                            // Obtain measurement (8 bits)

	uart_tx_buf[0] = rec_reg;							// Recorded data
//	uart_tx_buf[1] = 0;									// Not used with ADC


	phase_shift(&rec_reg, &stim_reg);					// Perform the phase shift algorithm

	DA1_SetValue(&stim_reg);							// Set the DAC according to the output of the
														// algorithm stored in stim_reg (12 bits)

//	uart_tx_buf[2] 	= stim_reg & 0xFF;					// First 8-bits (0-7) of the DAC value
//	uart_tx_buf[3] 	= (stim_reg & 0x0F00) >> BYTE;		// Bits 8-11 of the DAC value
//	uart_tx_buf[3] |= (phase_cond & 0x0F) << BITS_4;	// The phase value (4 bits) is encoded in the stimulation data
//														// It is then decomposed once received by the GUI

	stim_reg = stim_reg / 4095.0f * 255;
	uart_tx_buf[1] = stim_reg;

	/*
	 * Transmit the data stored in the UART tx buffer.
	 * The status of the transmission is stored in tx_error.
	 */
//	tx_error = AS1_SendBlock(uart_tx_buf, UART_TX_PACKETS, &bytes_sent);
	tx_error = AS1_SendBlock(uart_tx_buf, 2, &bytes_sent);

	/*
	 * Check if the error status and bytes transmitted are as expected.
	 * If otherwise, handle the error.
	 */
	if (tx_error || (bytes_sent != UART_TX_PACKETS))
	{
		// Add error handling code
	}
}

/*
** ===================================================================
**     Event       :  AS1_OnFullRxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnFullRxBuf(void)
{
	/*
	 * rx_error: holds the status of rx communication. A value of zero is expected when no errors occur.
	 * bytes_rec: holds the number of bytes received through UART
	 */
	unsigned char rx_error = 0, bytes_rec = 0;

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
