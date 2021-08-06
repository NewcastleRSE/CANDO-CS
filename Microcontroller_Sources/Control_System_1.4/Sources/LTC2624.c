/* ###################################################################
**     Filename    : LTC2604.c
**     Project     : Control_System_1.4
**     Processor   : MK22FN512VDC12
**     Component   : LTC2604
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-03-06, 09:31, # CodeGen: 0
**     Abstract    :
**         	Contains commands for controlling the LTC2624 external DAC
** ###################################################################*/

#include "LTC2624.h"
#include "DAC_interface.h"
#include "DAC_CLR.h"
#include "DAC_CS.h"
#include "Phase_Shift_Algorithm.h"
#include "Events.h"

struct ltc2624
{
	const unsigned char addr;
	unsigned short level;
};

ltc2624 ltc2624_DAC_A = {.addr = DAC_A, .level = 0};
ltc2624 ltc2624_DAC_B = {.addr = DAC_B, .level = 0};
ltc2624 ltc2624_DAC_C = {.addr = DAC_C, .level = 0};
ltc2624 ltc2624_DAC_D = {.addr = DAC_D, .level = 0};

void ltc2624_init(void)
{
	DAC_CLR_SetVal();

	ltc2624_DAC_A.level = 0;
	ltc2624_DAC_B.level = 0;
	ltc2624_DAC_C.level = 0;
	ltc2624_DAC_D.level = 0;

	ltc2624_setValAndUpdateAll(0);
}

void ltc2624_setValue(ltc2624 *ltc2624, unsigned short level)
{
	unsigned char packet_tx[3] = {0};
	unsigned char packet_rx[3] = {0};
	unsigned short bytes_tx = 0, bytes_rx = 0;

	ltc2624->level = level;

	packet_tx[2] = (level & 0x000F) << 4;
	packet_tx[1] = (level & 0x0FF0) >> 4;
	packet_tx[0] = ((WRITE_n & 0x0F) << 4) | (ltc2624->addr & 0x0F);

	DAC_CS_ClrVal();

	DAC_interface_SendBlock(packet_tx, 3, &bytes_tx);

	DAC_interface_RecvBlock(packet_rx, 3, &bytes_rx);

	DAC_CS_SetVal();
}

void ltc2624_setValueAll(unsigned short level)
{
	unsigned char packet_tx[3] = {0};
	unsigned char packet_rx[3] = {0};
	unsigned short bytes_tx = 0, bytes_rx = 0;

	packet_tx[2] = (level & 0x000F) << 4;
	packet_tx[1] = (level & 0x0FF0) >> 4;
	packet_tx[0] = ((WRITE_n & 0x0F) << 4) | (ALL_DACS & 0x0F);

	DAC_CS_ClrVal();

	DAC_interface_SendBlock(packet_tx, 3, &bytes_tx);

	DAC_interface_RecvBlock(packet_rx, 3, &bytes_rx);

	DAC_CS_SetVal();
}

void ltc2624_update(ltc2624 *ltc2624)
{
	unsigned char packet_tx[3] = {0};
	unsigned char packet_rx[3] = {0};
	unsigned short bytes_tx = 0, bytes_rx = 0;

	packet_tx[2] = 0;
	packet_tx[1] = 0;
	packet_tx[0] = ((UPDATE_n & 0x0F) << 4) | (ltc2624->addr & 0x0F);

	DAC_CS_ClrVal();

	DAC_interface_SendBlock(packet_tx, 3, &bytes_tx);

	DAC_interface_RecvBlock(packet_rx, 3, &bytes_rx);

	DAC_CS_SetVal();
}

void ltc2624_updateAll(void)
{
	unsigned char packet_tx[3] = {0};
	unsigned char packet_rx[3] = {0};
	unsigned short bytes_tx = 0, bytes_rx = 0;

	packet_tx[2] = 0;
	packet_tx[1] = 0;
	packet_tx[0] = ((UPDATE_n & 0x0F) << 4) | (ALL_DACS & 0x0F);

	DAC_CS_ClrVal();

	DAC_interface_SendBlock(packet_tx, 3, &bytes_tx);

	DAC_interface_RecvBlock(packet_rx, 3, &bytes_rx);

	DAC_CS_SetVal();
}

void ltc2624_powerDown(ltc2624 *ltc2624)
{
	unsigned char packet_tx[3] = {0};
	unsigned char packet_rx[3] = {0};
	unsigned short bytes_tx = 0, bytes_rx = 0;

	packet_tx[2] = 0;
	packet_tx[1] = 0;
	packet_tx[0] = ((POWER_DOWN_n & 0x0F) << 4) | (ltc2624->addr & 0x0F);

	DAC_CS_ClrVal();

	DAC_interface_SendBlock(packet_tx, 3, &bytes_tx);

	DAC_interface_RecvBlock(packet_rx, 3, &bytes_rx);

	DAC_CS_SetVal();
}

void ltc2624_powerDownAll(void)
{
	unsigned char packet_tx[3] = {0};
	unsigned char packet_rx[3] = {0};
	unsigned short bytes_tx = 0, bytes_rx = 0;

	packet_tx[2] = 0;
	packet_tx[1] = 0;
	packet_tx[0] = ((POWER_DOWN_n & 0x0F) << 4) | (ALL_DACS & 0x0F);

	DAC_CS_ClrVal();

	DAC_interface_SendBlock(packet_tx, 3, &bytes_tx);

	DAC_interface_RecvBlock(packet_rx, 3, &bytes_rx);

	DAC_CS_SetVal();
}

void ltc2624_setValAndUpdate(ltc2624 *ltc2624, unsigned short level)
{
	unsigned char packet_tx[3] = {0};
	unsigned char packet_rx[3] = {0};
	unsigned short bytes_tx = 0, bytes_rx = 0;

	ltc2624->level = level;

	packet_tx[2] = (level & 0x000F) << 4;
	packet_tx[1] = (level & 0x0FF0) >> 4;
	packet_tx[0] = ((WRITE_UPDATE_n & 0x0F) << 4) | (ltc2624->addr & 0x0F);

	DAC_CS_ClrVal();

	DAC_interface_SendBlock(packet_tx, 3, &bytes_tx);

	DAC_interface_RecvBlock(packet_rx, 3, &bytes_rx);

	DAC_CS_SetVal();
}

void ltc2624_setValAndUpdateAll(unsigned short level)
{
	unsigned char packet_tx[3] = {0};
	unsigned char packet_rx[3] = {0};
	unsigned short bytes_tx = 0, bytes_rx = 0;

	packet_tx[2] = (level & 0x000F) << 4;
	packet_tx[1] = (level & 0x0FF0) >> 4;
	packet_tx[0] = ((WRITE_UPDATE_n & 0x0F) << 4) | (ALL_DACS & 0x0F);

	DAC_CS_ClrVal();

	DAC_interface_SendBlock(packet_tx, 3, &bytes_tx);

	DAC_interface_RecvBlock(packet_rx, 3, &bytes_rx);

	DAC_CS_SetVal();
}
