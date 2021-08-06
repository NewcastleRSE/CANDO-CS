/* ###################################################################
**     Filename    : SW_Info.c
**     Project     : Control_System_1.4
**     Processor   : MK22FN512VDC12
**     Component   : Phase_Shift_Algorithm
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-03-06, 09:31, # CodeGen: 0
**     Abstract    :
**         	Contains function definitions providing information
**         	such as software version.
** ###################################################################*/

#include "SW_Info.h"
#include "AS1.h"

#define SW_VERSION "Control_System_1.1"

void send_SW_version(void)
{
	unsigned char tx_error = 0;
	unsigned short bytes_sent = 0;

	tx_error = AS1_SendChar(sizeof(SW_VERSION));

	if (tx_error)
	{
		// Add error handling code
	}

	tx_error = AS1_SendBlock(SW_VERSION, sizeof(SW_VERSION), &bytes_sent);

	if (tx_error || (bytes_sent != sizeof(SW_VERSION)))
	{
		// Add error handling code
	}
}
