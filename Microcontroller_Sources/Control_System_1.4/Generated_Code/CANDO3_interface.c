/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : CANDO3_interface.c
**     Project     : Control_System_1.4
**     Processor   : MK22FN512VLH12
**     Component   : SynchroMaster
**     Version     : Component 02.347, Driver 01.01, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-06-14, 14:04, # CodeGen: 15
**     Abstract    :
**         This component "SynchroMaster" implements MASTER part of synchronous
**         serial master-slave communication.
**     Settings    :
**          Component name                                 : CANDO3_interface
**          Channel                                        : SPI1
**          Interrupt service/event                        : Enabled
**            Interrupt                                    : 
**            Interrupt from input                         : INT_SPI1
**            Interrupt input priority                     : medium priority
**            Interrupt from output                        : INT_SPI1
**            Interrupt output priority                    : medium priority
**            Input buffer size                            : 1000
**            Output buffer size                           : 1000
**          Settings                                       : 
**            Width                                        : 8 bits
**            Input pin                                    : Enabled
**              Pin                                        : PTD7/UART0_TX/FTM0_CH7/FTM0_FLT1/SPI1_SIN
**            Output pin                                   : Enabled
**              Pin                                        : ADC0_SE7b/PTD6/LLWU_P15/SPI0_PCS3/UART0_RX/FTM0_CH6/FBa_AD0/FTM0_FLT0/SPI1_SOUT
**            Clock pin                                    : 
**              Pin                                        : ADC0_SE6b/PTD5/SPI0_PCS2/UART0_CTS_b/FTM0_CH5/FBa_AD1/EWM_OUT_b/SPI1_SCK
**            Slave select pin                             : Disabled
**            Clock edge                                   : falling edge
**            Shift clock rate                             : 2 MHz
**            Delay between chars                          : 0.291735 �s
**            CS to CLK delay                              : 0.291735 �s
**            CLK to CS delay                              : 0.291735 �s
**            Empty character                              : 0
**            Ignore empty char.                           : no
**            Send MSB first                               : no
**            Shift clock idle polarity                    : Low
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Events enabled in init.                      : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : This component enabled
**            Low speed mode                               : This component disabled
**            Slow speed mode                              : This component disabled
**          Referenced components                          : 
**            SPIMaster_LDD                                : SPIMaster_LDD
**     Contents    :
**         RecvChar        - byte CANDO3_interface_RecvChar(CANDO3_interface_TComData *Chr);
**         SendChar        - byte CANDO3_interface_SendChar(CANDO3_interface_TComData Chr);
**         RecvBlock       - byte CANDO3_interface_RecvBlock(CANDO3_interface_TComData *Ptr, word Size,...
**         SendBlock       - byte CANDO3_interface_SendBlock(CANDO3_interface_TComData *Ptr, word Size,...
**         ClearRxBuf      - byte CANDO3_interface_ClearRxBuf(void);
**         ClearTxBuf      - byte CANDO3_interface_ClearTxBuf(void);
**         GetCharsInRxBuf - word CANDO3_interface_GetCharsInRxBuf(void);
**         GetCharsInTxBuf - word CANDO3_interface_GetCharsInTxBuf(void);
**         GetError        - byte CANDO3_interface_GetError(CANDO3_interface_TError *Err);
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
** @file CANDO3_interface.c
** @version 01.01
** @brief
**         This component "SynchroMaster" implements MASTER part of synchronous
**         serial master-slave communication.
*/         
/*!
**  @addtogroup CANDO3_interface_module CANDO3_interface module documentation
**  @{
*/         

/* MODULE CANDO3_interface. */

#include "Events.h"
#include "CANDO3_interface.h"

#ifdef __cplusplus
extern "C" {
#endif 

#define OVERRUN_ERR      0x01U         /* Overrun error flag bit   */
#define TX_BUF_EMPTY     0x02U         /* Tx buffer state flag bit   */
#define CHAR_IN_RX       0x08U         /* Char is in RX buffer     */
#define FULL_TX          0x10U         /* Full transmit buffer     */
#define RUNINT_FROM_TX   0x20U         /* Interrupt is in progress */
#define FULL_RX          0x40U         /* Full receive buffer      */

LDD_TDeviceData *SMasterLdd2_DeviceDataPtr; /* Device data pointer */
static byte SerFlag;                   /* Flags for serial communication */
                                       /* Bits: 0 - OverRun error */
                                       /*       1 - Tx buffer state after init */
                                       /*       2 - Unused */
                                       /*       3 - Char in RX buffer */
                                       /*       4 - Full TX buffer */
                                       /*       5 - Running int from TX */
                                       /*       6 - Full RX buffer */
                                       /*       7 - Unused */
static byte ErrFlag;                   /* Error flags for GetError method */
static volatile word CANDO3_interface_InpLen; /* Length of input buffer's content */
static byte InpIndexR;                 /* Index for reading from input buffer */
static byte InpIndexW;                 /* Index for writing to input buffer */
static CANDO3_interface_TComData InpBuffer[CANDO3_interface_INP_BUF_SIZE]; /* Input buffer SPI communication */
static CANDO3_interface_TComData BufferRead; /* Input char SPI communication */
static volatile word CANDO3_interface_OutLen; /* Length of output bufer's content */
static byte OutIndexR;                 /* Index for reading from output buffer */
static byte OutIndexW;                 /* Index for writing to output buffer */
static CANDO3_interface_TComData OutBuffer[CANDO3_interface_OUT_BUF_SIZE]; /* Output buffer for SPI communication */

/*
** ===================================================================
**     Method      :  CANDO3_interface_RecvChar (component SynchroMaster)
**     Description :
**         If any data is received, this method returns one character,
**         otherwise it returns an error code (it does not wait for
**         data). 
**         For information about SW overrun behavior please see
**         <General info page>.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - A pointer to the received character
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK - The valid data is received.
**                           ERR_SPEED - This device does not work in
**                           the active speed mode.
**                           ERR_RXEMPTY - No data in receiver.
**                           ERR_OVERRUN - Overrun error was detected
**                           from the last char or block received. In
**                           polling mode, this error code is returned
**                           only when the hardware supports detection
**                           of the overrun error. If interrupt service
**                           is enabled, and input buffer allocated by
**                           the component is full, the component
**                           behaviour depends on <Input buffer size>
**                           property : if property is 0, last received
**                           data-word is preserved (and previous is
**                           overwritten), if property is greater than 0,
**                           new received data-word are ignored.
**                           ERR_FAULT - Fault error was detected from
**                           the last char or block received. In the
**                           polling mode the ERR_FAULT is return until
**                           the user clear the fault flag bit, but in
**                           the interrupt mode ERR_FAULT is returned
**                           only once after the fault error occured.
**                           This error is supported only on the CPUs
**                           supports the faul mode function - where
**                           <Fault mode> property is available.
** ===================================================================
*/
byte CANDO3_interface_RecvChar(CANDO3_interface_TComData *Chr)
{
  register byte FlagTmp;

  if (CANDO3_interface_InpLen > 0U) {  /* Is number of received chars greater than 0? */
    EnterCritical();                   /* Disable global interrupts */
    CANDO3_interface_InpLen--;         /* Decrease number of received chars */
    *Chr = InpBuffer[InpIndexR++];     /* Read the char */
    if (InpIndexR >= CANDO3_interface_INP_BUF_SIZE) { /* Is the index out of the receive buffer? */
      InpIndexR = 0x00U;               /* Set index to the first item into the receive buffer */
    }
    FlagTmp = SerFlag;                 /* Safe the flags */
    SerFlag &= (byte)~(OVERRUN_ERR | FULL_RX); /* Clear flag "char in RX buffer" */
    ExitCritical();                    /* Enable global interrupts */
  } else {
    return ERR_RXEMPTY;                /* Receiver is empty */
  }
  if ((FlagTmp & (OVERRUN_ERR | FULL_RX)) != 0U) { /* Is the overrun occurred? */
    return ERR_OVERRUN;                /* If yes then return error */
  } else {
    return ERR_OK;
  }
}

/*
** ===================================================================
**     Method      :  CANDO3_interface_SendChar (component SynchroMaster)
**     Description :
**         Sends one character to the channel.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled (only if
**                           output DMA is supported and enabled)
**                           ERR_TXFULL - Transmitter is full
** ===================================================================
*/
byte CANDO3_interface_SendChar(CANDO3_interface_TComData Chr)
{
  if (CANDO3_interface_OutLen == CANDO3_interface_OUT_BUF_SIZE) { /* Is number of chars in buffer the same as the size of transmit buffer? */
    return ERR_TXFULL;                 /* If yes then error */
  }
  EnterCritical();                     /* Disable global interrupts */
  CANDO3_interface_OutLen++;           /* Increase number of bytes in the transmit buffer */
  OutBuffer[OutIndexW++] = Chr;        /* Store char to buffer */
  if (OutIndexW >= CANDO3_interface_OUT_BUF_SIZE) { /* Is the index out of the transmit buffer? */
    OutIndexW = 0x00U;                 /* Set index to the first item in the transmit buffer */
  }
  if ((SerFlag & RUNINT_FROM_TX) == 0U) {
    SerFlag |= RUNINT_FROM_TX;         /* Set flag "running int from TX"? */
    (void)SMasterLdd2_SendBlock(SMasterLdd2_DeviceDataPtr, (LDD_TData *)&OutBuffer[OutIndexR], 1U); /* Send one data byte */
  }
  ExitCritical();                      /* Enable global interrupts */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  CANDO3_interface_RecvBlock (component SynchroMaster)
**     Description :
**         If any data received, this method returns the block of the
**         data and its length (and incidental error), otherwise it
**         returns error code (it does not wait for data).
**         If less than requested number of characters is received only
**         the available data is copied from the receive buffer to the
**         user specified destination and the ERR_EXEMPTY value is
**         returned.
**         This method is available only if non-zero length of input
**         buffer is defined.
**         For information about SW overrun behavior please see
**         <General info page>.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - A pointer to the block of received data
**         Size            - The size of the block
**       * Rcv             - Pointer to a variable where an actual
**                           number of copied characters is stored
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK - The valid data is received.
**                           ERR_SPEED - This device does not work in
**                           the active speed mode.
**                           ERR_RXEMPTY - It was not possible to read
**                           requested number of bytes from the buffer.
**                           ERR_OVERRUN - Overrun error was detected
**                           from the last char or block received. If
**                           interrupt service is enabled, and input
**                           buffer allocated by the component is full,
**                           the component behaviour depends on <Input
**                           buffer size> property : if property is 0,
**                           last received data-word is preserved (and
**                           previous is overwritten), if property is
**                           greater than 0, new received data-word are
**                           ignored.
**                           ERR_FAULT - Fault error was detected from
**                           the last char or block received. In the
**                           polling mode the ERR_FAULT is return until
**                           the user clear the fault flag bit, but in
**                           the interrupt mode ERR_FAULT is returned
**                           only once after the fault error occured.
**                           This error is supported only on the CPUs
**                           supports the faul mode function - where
**                           <Fault mode> property is available.
** ===================================================================
*/
byte CANDO3_interface_RecvBlock(CANDO3_interface_TComData *Ptr,word Size,word *Rcv)
{
  register word count;                 /* Number of received chars */
  register byte Result = ERR_OK;       /* Most serious error */
  register byte ResultTmp;             /* Last error */


  count = 0U;
  while (count < Size) {
    ResultTmp = CANDO3_interface_RecvChar(Ptr++); /* Receive one character */
    if (ResultTmp > Result) {          /* Is last error most serious than through error state? */
      Result = ResultTmp;              /* If yes then prepare error value to return */
    }
    if ((ResultTmp != ERR_OK)&&(ResultTmp != ERR_OVERRUN)) { /* Receiving given number of chars */
      break;                           /* Break data block receiving */
    }
    count++;
  }
  *Rcv = count;                        /* Return number of received chars */
  return Result;                       /* Return most serious error */
}

/*
** ===================================================================
**     Method      :  CANDO3_interface_SendBlock (component SynchroMaster)
**     Description :
**         Send a block of characters to the channel. This method is
**         only available if a non-zero length of output buffer is
**         defined.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - Pointer to the block of data to send
**         Size            - Size of the block
**       * Snd             - Pointer to number of data that are sent
**                           (moved to buffer)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled (only if
**                           output DMA is supported and enabled)
**                           ERR_TXFULL - It was not possible to send
**                           requested number of bytes
** ===================================================================
*/
byte CANDO3_interface_SendBlock(CANDO3_interface_TComData *Ptr, word Size, word *Snd)
{
  word count = 0x00U;                  /* Number of sent chars */
  CANDO3_interface_TComData *TmpPtr = Ptr; /* Temporary output buffer pointer */

  while((count < Size) && (CANDO3_interface_OutLen < CANDO3_interface_OUT_BUF_SIZE)) { /* While there is some char desired to send left and output buffer is not full do */
    EnterCritical();                   /* Enter the critical section */
    CANDO3_interface_OutLen++;         /* Increase number of bytes in the transmit buffer */
    OutBuffer[OutIndexW++] = *TmpPtr++; /* Store char to buffer */
    if (OutIndexW >= CANDO3_interface_OUT_BUF_SIZE) { /* Is the index out of the transmit buffer? */
      OutIndexW = 0x00U;               /* Set index to the first item in the transmit buffer */
    }
    count++;                           /* Increase the count of sent data */
    if ((SerFlag & RUNINT_FROM_TX) == 0U) {
      SerFlag |= RUNINT_FROM_TX;       /* Set flag "running int from TX"? */
      (void)SMasterLdd2_SendBlock(SMasterLdd2_DeviceDataPtr, (LDD_TData *)&OutBuffer[OutIndexR], 1U); /* Send one data byte */
    }
    ExitCritical();                    /* Exit the critical section */
  }
  *Snd = count;                        /* Return number of sent chars */
  if (count != Size) {                 /* Is the number of sent chars less then desired number of chars */
    return ERR_TXFULL;                 /* If yes then error */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  CANDO3_interface_ClearRxBuf (component SynchroMaster)
**     Description :
**         Clears the receive buffer. This method is available only if
**         a non-zero length of input buffer is defined.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte CANDO3_interface_ClearRxBuf(void)
{
  EnterCritical();                     /* Disable global interrupts */
  CANDO3_interface_InpLen = 0U;        /* Set number of chars in the transmit buffer to 0 */
  InpIndexW = 0x00U;                   /* Set index on the first item in the transmit buffer */
  InpIndexR = 0x00U;
  SerFlag &= (byte)~(OVERRUN_ERR | FULL_RX); /* Clear flags */
  ExitCritical();                      /* Enable global interrupts */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  CANDO3_interface_ClearTxBuf (component SynchroMaster)
**     Description :
**         Clears the transmit buffer. This method is only available if
**         a non-zero length of output buffer is defined.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte CANDO3_interface_ClearTxBuf(void)
{
  EnterCritical();                     /* Disable global interrupts */
  CANDO3_interface_OutLen = 0U;        /* Set number of chars in the receive buffer to 0 */
  OutIndexW = 0x00U;                   /* Set index on the first item in the receive buffer */
  OutIndexR = 0x00U;
  ExitCritical();                      /* Enable global interrupts */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  CANDO3_interface_GetCharsInRxBuf (component SynchroMaster)
**     Description :
**         Returns the number of characters in the input buffer.
**         Note: If the Interrupt service is disabled, and the Ignore
**         empty character is set to yes, and a character has been
**         received, then this method returns 1 although it was an
**         empty character.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the input buffer.
** ===================================================================
*/
word CANDO3_interface_GetCharsInRxBuf(void)
{
  return CANDO3_interface_InpLen;      /* Return number of chars in receive buffer */
}

/*
** ===================================================================
**     Method      :  CANDO3_interface_GetCharsInTxBuf (component SynchroMaster)
**     Description :
**         Returns the number of characters in the output buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the output buffer.
** ===================================================================
*/
word CANDO3_interface_GetCharsInTxBuf(void)
{
  return CANDO3_interface_OutLen;      /* Return number of chars in the transmit buffer */
}

/*
** ===================================================================
**     Method      :  CANDO3_interface_GetError (component SynchroMaster)
**     Description :
**         Returns a set of errors on the channel (errors that cannot
**         be returned in given methods). The component accumulates
**         errors in a set; after calling [GetError] this set is
**         returned and cleared. This method is available only if the
**         "Interrupt service/event" property is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Err             - A pointer to the returned set of errors
**     Returns     :
**         ---             - Error code (if GetError did not succeed),
**                           possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte CANDO3_interface_GetError(CANDO3_interface_TError *Err)
{
  EnterCritical();                     /* Disable global interrupts */
  Err->err = 0U;
  Err->errName.OverRun = (((ErrFlag & OVERRUN_ERR) != 0U)? 1U : 0U); /* Overrun error */
  Err->errName.RxBufOvf = (((ErrFlag & FULL_RX) != 0U)? 1U : 0U); /* Buffer overflow */
  ErrFlag = 0x00U;                     /* Reset error flags */
  ExitCritical();                      /* Enable global interrupts */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  CANDO3_interface_Init (component SynchroMaster)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void CANDO3_interface_Init(void)
{
  SerFlag = 0U;                        /* Reset all flags */
  ErrFlag = 0U;                        /* Reset all flags in mirror */
  CANDO3_interface_InpLen = 0U;        /* No char in the receive buffer */
  InpIndexR = 0x00U;                   /* Set index on the first item in the receive buffer */
  InpIndexW = 0x00U;
  CANDO3_interface_OutLen = 0U;        /* No char in the transmit buffer */
  OutIndexR = 0x00U;                   /* Set index on the first item in the transmit buffer */
  OutIndexW = 0x00U;
  SMasterLdd2_DeviceDataPtr = SMasterLdd2_Init(NULL); /* Calling init method of the inherited component */
  (void)SMasterLdd2_ReceiveBlock(SMasterLdd2_DeviceDataPtr, &BufferRead, 1U); /* Receive one data byte */
}

#define ON_ERROR        0x01U
#define ON_FULL_RX      0x02U
#define ON_RX_CHAR      0x04U
#define ON_RX_CHAR_EXT  0x08U
/*
** ===================================================================
**     Method      :  CANDO3_interface_SMasterLdd2_OnBlockReceived (component SynchroMaster)
**
**     Description :
**         This event is called when the requested number of data is 
**         moved to the input buffer. This method is available only if 
**         the ReceiveBlock method is enabled. The event services the 
**         event of the inherited component and eventually invokes other 
**         events.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void SMasterLdd2_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
  register byte Flags = 0U;            /* Temporary variable for flags */

  (void)UserDataPtr;                   /* Parameter is not used, suppress unused argument warning */
  if (CANDO3_interface_InpLen < CANDO3_interface_INP_BUF_SIZE) { /* Is number of bytes in the receive buffer lower than size of buffer? */
    CANDO3_interface_InpLen++;         /* Increase number of chars in the receive buffer */
    InpBuffer[InpIndexW++] = (CANDO3_interface_TComData)BufferRead; /* Save received char to the receive buffer */
    if (InpIndexW >= CANDO3_interface_INP_BUF_SIZE) { /* Is the index out of the receive buffer? */
      InpIndexW = 0x00U;               /* Set index on the first item into the receive buffer */
    }
  } else {
    SerFlag |= FULL_RX;                /* Set flag "full RX buffer" */
    ErrFlag |= FULL_RX;                /* Set flag "full RX buffer" for GetError method */
    Flags |= ON_ERROR;                 /* Set the OnError flag */
  }
  if ((Flags & ON_ERROR) != 0U) {      /* Is any error flag set? */
    CANDO3_interface_OnError();        /* Invoke user event */
  }
  (void)SMasterLdd2_ReceiveBlock(SMasterLdd2_DeviceDataPtr, &BufferRead, 1U); /* Receive one data byte */
}

#define ON_FREE_TX  0x01U
#define ON_TX_CHAR  0x02U
/*
** ===================================================================
**     Method      :  CANDO3_interface_SMasterLdd2_OnBlockSent (component SynchroMaster)
**
**     Description :
**         This event is called after the last character from the output 
**         buffer is moved to the transmitter. This event is available 
**         only if the SendBlock method is enabled. The event services 
**         the event of the inherited component and eventually invokes 
**         other events.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void SMasterLdd2_OnBlockSent(LDD_TUserData *UserDataPtr)
{
  (void)UserDataPtr;                   /* Parameter is not used, suppress unused argument warning */
  OutIndexR++;
  if (OutIndexR >= CANDO3_interface_OUT_BUF_SIZE) { /* Is the index out of the transmit buffer? */
    OutIndexR = 0x00U;                 /* Set index on the first item into the transmit buffer */
  }
  CANDO3_interface_OutLen--;           /* Decrease number of chars in the transmit buffer */
  if (CANDO3_interface_OutLen != 0U) { /* Is number of bytes in the transmit buffer greater then 0? */
    SerFlag |= RUNINT_FROM_TX;         /* Set flag "running int from TX"? */
    (void)SMasterLdd2_SendBlock(SMasterLdd2_DeviceDataPtr, (LDD_TData *)&OutBuffer[OutIndexR], 1U); /* Send one data byte */
  } else {
    SerFlag &= (byte)~(RUNINT_FROM_TX | FULL_TX); /* Clear "running int from TX" and "full TX buff" flags */
  }
}

/* END CANDO3_interface. */

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