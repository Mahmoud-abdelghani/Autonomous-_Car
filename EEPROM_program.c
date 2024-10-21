/*
 * EEPROM_program.c
 *
 *  Created on: Sep 10, 2024
 *      Author: mahmoud
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_private.h"

#include <util/delay.h>

void EEPROM_voidWriteDataByte(u8 Copy_u8DeviceNumber,u16 Copy_u16Location,u8 Copy_u8DataByte)
{
	u8 Copy_u8SlaveAddress;
	Copy_u8SlaveAddress=(0b01010000)|(Copy_u8DeviceNumber << 2)|(Copy_u16Location>>8);
	TWI_voidSendStartCondition();
	TWI_voidSendSlaveAdressWithWrite(Copy_u8SlaveAddress);
	TWI_voidMasterSendDataByte((u8)Copy_u16Location);
	TWI_voidMasterSendDataByte(Copy_u8DataByte);
	TWI_voidSendStopCondition();
	_delay_ms(5);
	_delay_ms(5);
}

u8 EEPROM_u8ReadDataByte(u8 Copy_u8DeviceNumber,u16 Copy_u16Location)
{
	u8 Local_u8ReturnData;
	u8 Copy_u8SlaveAddress;
	Copy_u8SlaveAddress=(0b01010000)|(Copy_u8DeviceNumber << 2)|(Copy_u16Location>>8);
	TWI_voidSendStartCondition();
	TWI_voidSendSlaveAdressWithWrite(Copy_u8SlaveAddress);
	TWI_voidMasterSendDataByte((u8)Copy_u16Location);
	TWI_voidSendStartCondition();
	TWI_voidSendSlaveAdressWithRead(Copy_u8SlaveAddress);
	Local_u8ReturnData=TWI_u8MasterRecieveDataByte();
	TWI_voidSendStopCondition();

	return Local_u8ReturnData;
}

