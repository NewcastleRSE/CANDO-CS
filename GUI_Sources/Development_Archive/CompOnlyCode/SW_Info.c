/* ###################################################################
**     Filename    : SW_Info.c
**     Project     : RCS_Box_2.2
**     Processor   : MK22FN512VDC12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-01-29, 21:43, # CodeGen: 0
**     Abstract    :
**         	Contains function definitions providing information
**         	such as software version.
** ###################################################################*/

#include "SW_Info.h"

void send_SW_version(void)
{
	unsigned char tx_error = 0, bytes_sent = 0;

	tx_error = AS1_SendBlock(SW_VERSION, sizeof(SW_VERSION), &bytes_sent);

	if (tx_error || (bytes_sent != sizeof(SW_VERSION)))
	{
		// Add error handling code
	}
}
