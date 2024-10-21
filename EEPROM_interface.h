/*
 * EEPROM_interface.h
 *
 *  Created on: Sep 10, 2024
 *      Author: mahmoud
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

#define DEVICE1       0
#define DEVICE2       1

void EEPROM_voidWriteDataByte(u8 Copy_u8DeviceNumber,u16 Copy_u16Location,u8 Copy_u8DataByte);

u8 EEPROM_u8ReadDataByte(u8 Copy_u8DeviceNumber,u16 Copy_u16Location);
#endif /* EEPROM_INTERFACE_H_ */
