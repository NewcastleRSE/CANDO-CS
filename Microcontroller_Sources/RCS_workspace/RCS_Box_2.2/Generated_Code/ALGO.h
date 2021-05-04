/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : ALGO.h
**     Project     : RCS_Box_2.2
**     Processor   : MK22FN512VLH12
**     Component   : FreeCntr_LDD
**     Version     : Component 01.005, Driver 01.01, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-02-06, 20:24, # CodeGen: 0
**     Abstract    :
**          This device "FreeCntr_LDD" implements Free Running Counter
**          This FreeCntr component provides a high level API for unified
**          hardware access to various timer devices using the TimerUnit
**          component.
**     Settings    :
**          Component name                                 : ALGO
**          Module name                                    : FTM0
**          Counter                                        : FTM0_CNT
**          Counter direction                              : Up
**          Counter frequency                              : 1.31072 MHz
**          Mode                                           : Compare match
**            Period/offset device                         : FTM0_MOD
**            Period/offset                                : 2 ms
**            Interrupt service/event                      : Enabled
**              Interrupt                                  : INT_FTM0
**              Interrupt priority                         : medium priority
**          Value type                                     : Optimal
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : yes
**            Event mask                                   : 
**              OnInterrupt                                : Enabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**          Referenced components                          : 
**            Linked TimerUnit                             : TU1
**     Contents    :
**         Init            - LDD_TDeviceData* ALGO_Init(LDD_TUserData *UserDataPtr);
**         Deinit          - void ALGO_Deinit(LDD_TDeviceData *DeviceDataPtr);
**         Enable          - LDD_TError ALGO_Enable(LDD_TDeviceData *DeviceDataPtr);
**         Disable         - LDD_TError ALGO_Disable(LDD_TDeviceData *DeviceDataPtr);
**         GetCounterValue - ALGO_TValueType ALGO_GetCounterValue(LDD_TDeviceData *DeviceDataPtr);
**         ResetCounter    - LDD_TError ALGO_ResetCounter(LDD_TUserData *DeviceDataPtr);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file ALGO.h
** @version 01.01
** @brief
**          This device "FreeCntr_LDD" implements Free Running Counter
**          This FreeCntr component provides a high level API for unified
**          hardware access to various timer devices using the TimerUnit
**          component.
*/         
/*!
**  @addtogroup ALGO_module ALGO module documentation
**  @{
*/         

#ifndef __ALGO_H
#define __ALGO_H

/* MODULE ALGO. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "TU1.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 


#ifndef __BWUserType_ALGO_TValueType
#define __BWUserType_ALGO_TValueType
  typedef TU1_TValueType ALGO_TValueType ; /* Type for data parameters of methods */
#endif
#define ALGO_CNT_INP_FREQ_U_0 TU1_CNT_INP_FREQ_U_0 /* Counter input frequency in Hz */
#define ALGO_CNT_INP_FREQ_R_0 TU1_CNT_INP_FREQ_R_0 /* Counter input frequency in Hz */
#define ALGO_CNT_INP_FREQ_COUNT TU1_CNT_INP_FREQ_COUNT /* Count of predefined counter input frequencies */
#ifdef TU1_PERIOD_TICKS
#define ALGO_PERIOD_TICKS  TU1_PERIOD_TICKS /* Initialization value of period in 'counter ticks' */
#endif
#define ALGO_COUNTER_DIR   0U          /* Direction of counting UP */
#define ALGO_RESET_ON_COMPARE 1        /* This constant is defined if 'Compare match ' mode is selected. */
/*! Peripheral base address of a device allocated by the component. This constant can be used directly in PDD macros. */
#define ALGO_PRPH_BASE_ADDRESS  0x40038000U
  
/*! Device data structure pointer used when auto initialization property is enabled. This constant can be passed as a first parameter to all component's methods. */
#define ALGO_DeviceData  ((LDD_TDeviceData *)PE_LDD_GetDeviceStructure(PE_LDD_COMPONENT_ALGO_ID))

/* Methods configuration constants - generated for all enabled component's methods */
#define ALGO_Init_METHOD_ENABLED       /*!< Init method of the component ALGO is enabled (generated) */
#define ALGO_Deinit_METHOD_ENABLED     /*!< Deinit method of the component ALGO is enabled (generated) */
#define ALGO_Enable_METHOD_ENABLED     /*!< Enable method of the component ALGO is enabled (generated) */
#define ALGO_Disable_METHOD_ENABLED    /*!< Disable method of the component ALGO is enabled (generated) */
#define ALGO_GetCounterValue_METHOD_ENABLED /*!< GetCounterValue method of the component ALGO is enabled (generated) */
#define ALGO_ResetCounter_METHOD_ENABLED /*!< ResetCounter method of the component ALGO is enabled (generated) */

/* Events configuration constants - generated for all enabled component's events */
#define ALGO_OnInterrupt_EVENT_ENABLED /*!< OnInterrupt event of the component ALGO is enabled (generated) */



/*
** ===================================================================
**     Method      :  ALGO_Init (component FreeCntr_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the
**         property ["Enable in init. code"] is set to "yes" value then
**         the device is also enabled (see the description of the
**         [Enable] method). In this case the [Enable] method is not
**         necessary and needn't to be generated. This method can be
**         called only once. Before the second call of Init the [Deinit]
**         must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* ALGO_Init(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  ALGO_Deinit (component FreeCntr_LDD)
*/
/*!
**     @brief
**         Deinitializes the device. Switches off the device, frees the
**         device data structure memory, interrupts vectors, etc.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by Init method
*/
/* ===================================================================*/
void ALGO_Deinit(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  ALGO_Enable (component FreeCntr_LDD)
*/
/*!
**     @brief
**         Enables the component - the internal clocks are counted.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError ALGO_Enable(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  ALGO_Disable (component FreeCntr_LDD)
*/
/*!
**     @brief
**         Disables the component - the internal clocks are not counted.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError ALGO_Disable(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  ALGO_GetCounterValue (component FreeCntr_LDD)
*/
/*!
**     @brief
**         Returns the content of counter register. This method can be
**         used both if counter is enabled and if counter is disabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Counter value (number of counted ticks).
*/
/* ===================================================================*/
ALGO_TValueType ALGO_GetCounterValue(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  ALGO_ResetCounter (component FreeCntr_LDD)
*/
/*!
**     @brief
**         Resets counter. If counter is counting up then it is set to
**         zero. If counter is counting down then counter is updated to
**         the reload value.
**         The method is not available if HW doesn't allow resetting of
**         the counter.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK 
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError ALGO_ResetCounter(LDD_TUserData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  ALGO_TU1_OnCounterRestart (component FreeCntr_LDD)
**
**     Description :
**         The method services the event of the linked component TU1 and 
**         eventually invokes other events.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void TU1_OnCounterRestart(LDD_TUserData *UserDataPtr);

/* END ALGO. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __ALGO_H */
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
