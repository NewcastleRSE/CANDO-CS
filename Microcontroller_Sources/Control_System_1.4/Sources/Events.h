/* ###################################################################
**     Filename    : Events.h
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
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
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

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char cycle_comp, cycle_cnt;									   
extern unsigned short stim_reg, rec_reg;
extern unsigned char algo_on_off_flag, start;

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
void Cpu_OnNMI(void);

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
void ALGO_OnInterrupt(LDD_TUserData *UserDataPtr);

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
void AS1_OnError(void);

void CANDO3_interface_OnError(void);
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

void DAC_interface_OnError(void);
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

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
