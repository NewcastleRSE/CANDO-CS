/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : DA1.h
**     Project     : RCS_Box_2.1
**     Processor   : MK22FN512VLH12
**     Component   : DAC
**     Version     : Component 01.096, Driver 01.00, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-01-29, 20:24, # CodeGen: 1
**     Abstract    :
**         This component "DAC" implements an internal D/A converter
**         of the MCU. It allows select channels of D/A converter and
**         contains methods for converting various format of a value to
**         supported format of the D/A converter.
**
**     Settings    :
**          Component name                                 : DA1
**          DAC_LDD                                        : DAC_LDD
**          D/A converter                                  : DAC0
**          D/A channels                                   : 1
**            Channel0                                     : 
**              Channel output pin                         : Enabled
**                D/A channel (pin)                        : DAC0_OUT/CMP1_IN3/ADC0_SE23
**              Init value                                 : 0
**          D/A resolution                                 : 12 bits
**          Data mode                                      : Right justified/unsigned
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**     Contents    :
**         SetValue - byte DA1_SetValue(void* Values);
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
** @file DA1.h
** @version 01.00
** @brief
**         This component "DAC" implements an internal D/A converter
**         of the MCU. It allows select channels of D/A converter and
**         contains methods for converting various format of a value to
**         supported format of the D/A converter.
**
*/         
/*!
**  @addtogroup DA1_module DA1 module documentation
**  @{
*/         

#ifndef __DA1_H
#define __DA1_H

/* MODULE DA1. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "DacLdd1.h"

#ifdef __cplusplus
extern "C" {
#endif 

#include "Cpu.h"




/*
** ===================================================================
**     Method      :  DA1_SetValue (component DAC)
**     Description :
**         This method sets values of all channels.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Values          - Pointer to array that contains the
**                           data. Data type is byte, word or int. It
**                           depends on supported modes, resolution, etc.
**                           of the D/A converter. See version specific
**                           information for the current CPU in <General
**                           Info>.
**     Returns     :
**         ---             - Error code, possible codes: 
**                           - ERR_OK - OK
** ===================================================================
*/
#define DA1_SetValue(Values) (byte)DacLdd1_SetValue(DacLdd1_DeviceData, (LDD_DAC_TData)(*(word*)(Values)))

/* END DA1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __DA1_H */
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
