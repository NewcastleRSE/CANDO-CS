/* ###################################################################
**     Filename    : main.c
**     Project     : RCS_Box_2.2
**     Processor   : MK22FN512VLH12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-01-29, 16:05, # CodeGen: 0
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
##double*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
/*
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "DA1.h"
#include "DacLdd1.h"
#include "TmDt1.h"
#include "TimeDateLdd1.h"
https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm#include "TU2.h"
#include "WAIT1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "ALGO.h"
#include "TU1.h"
*/
/* Including shared modules, which are used for whole project */

/*
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
*/

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Phase_Shift_Algorithm.h"
#include "Phase_Shift_Algorithm.c"
//#include "SW_Info.h"
//#include "SW_Info.c"
#include <stdio.h>
#include <math.h>
#include <string.h>
//LDD_TDeviceData *ALGOptr;

FILE *fp; //*fp;
char buff[522];
char buffcheck[522] = "Nope";
unsigned short sig_in;
unsigned short stim_out;
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	//PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/
    //send_SW_version();
	//ALGO_Disable(&ALGOptr); 	// Disable interrupts from the ALGO timer prior to kernel initialisation
	init_kernel();	// Initialise the kernels
	printf("Initialised the algorithm\n");
    printf("First kernel value is %.7g \n", kernel[1][1]);
    
    //ALGO_Enable(&ALGOptr);	// Enable the interrupts from ALGO timer

    //   printf("Made it to the main loop!\n"); 
    while(1)
	{

        //monitor a folder for incoming data, when data is detected trigger the
        //algorithm interrupt code
        //   printf("Made it to the main loop!\n"); 
        fp = fopen("incoming.bin","r");
        fscanf(fp, "%s",buff);
        fo = fopen("output.bin","w");
        if(strcmp(buffcheck,buff)!=0)
        {
            strcpy(buffcheck, buff);
            //buffcheck = buff;
            printf(fo,"%s",buff); // print to stdout
            
            stim_out = phase_shift(buff, stim_out); // either call directly, or use the
            // Events.c function ALGO_OnInterrupt(LDD_TUserData *UserDataPtr)
             fprintf(fo,"%s",stim_out); // now save the output to a file:
            
        }
        
        fclose(fp);
	}
    //fclose(fp);
	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
	/*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  	//#ifdef PEX_RTOS_START
    //	PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
	//#endif
    /*** End of RTOS startup code.  ***/
    /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
    for(;;){}
    /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} 	/*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
