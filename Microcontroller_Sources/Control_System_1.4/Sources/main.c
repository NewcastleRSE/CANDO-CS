/* ###################################################################
**     Filename    : main.c
**     Project     : Control_System_1.4
**     Processor   : MK22FN512VLH12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-03-06, 09:31, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "AD2.h"
#include "AdcLdd1.h"
#include "DA1.h"
#include "DacLdd1.h"
#include "WAIT1.h"
#include "MCUC1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "DAC_interface.h"
#include "SMasterLdd1.h"
#include "DAC_CS.h"
#include "BitIoLdd7.h"
#include "DAC_CLR.h"
#include "BitIoLdd6.h"
#include "CANDO3_interface.h"
#include "SMasterLdd2.h"
#include "CANDO3_CLK.h"
#include "CANDO3_CS1.h"
#include "BitIoLdd1.h"
#include "CANDO3_CS2.h"
#include "BitIoLdd2.h"
#include "CANDO3_CS3.h"
#include "BitIoLdd3.h"
#include "CANDO3_CS4.h"
#include "BitIoLdd4.h"
#include "CANDO3_RST.h"
#include "BitIoLdd5.h"
#include "ALGO.h"
#include "TU1.h"
#include "LED_GREEN.h"
#include "BitIoLdd9.h"
#include "LED_RED.h"
#include "BitIoLdd10.h"
#include "DConnector_1.h"
#include "BitIoLdd8.h"
#include "DConnector_2.h"
#include "BitIoLdd11.h"
#include "DConnector_3.h"
#include "BitIoLdd12.h"
#include "DConnector_4.h"
#include "BitIoLdd13.h"
#include "DConnector_5.h"
#include "BitIoLdd14.h"
#include "DConnector_6.h"
#include "BitIoLdd15.h"
#include "DConnector_7.h"
#include "BitIoLdd16.h"
#include "DConnector_8.h"
#include "BitIoLdd17.h"
#include "AD1.h"
#include "AdcLdd2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"

#include "Phase_Shift_Algorithm.h"
#include "IO.h"
#include "LTC2624.h"
#include "ASIC.h"
#include "Glossary.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

LDD_TUserData	*ALGO_TUserDataPtr;

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	resetASIC(&ASIC1);

	LED1_GND_tissue1(&ASIC1);
	LED2_GND_tissue1(&ASIC1);
	LED3_GND_tissue1(&ASIC1);
	LED4_GND_tissue1(&ASIC1);
	LED5_GND_tissue1(&ASIC1);
	LED6_GND_tissue1(&ASIC1);
	LED7_GND_tissue1(&ASIC1);

	init_rec(&ASIC1);
	set_amplifier_ch0(&ASIC1, G2100, 1, 0);
	set_amplifier_ch1(&ASIC1, G2100, 1, 0);

	ltc2624_init();
	init_kernel();					// Initialise the kernels

	ALGO_Init(&ALGO_TUserDataPtr);	// Initialise the algorithm ISR

	while(1)
	{
		if (start)
			set_algo_params();
		else
			ltc2624_powerDownAll();
	}

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
}
