/*********************************************************************/
/******************************* SWC : I2C ***************************/ 
/******************************* DATE : 9 SEPTEMPER 2024 *************/
/********** Author : MAHMOUD ABDELGHANI ******************************/
/******************************* Version : 1.0 ***********************/
#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

void TWI_voidMasterInit(u8 Copy_u8Address);

void TWI_voidSlaveInit(u8 Copy_u8Address);

void TWI_voidSendStartCondition(void);

void TWI_voidSendSlaveAdressWithWrite(u8 Copy_u8Address);

void TWI_voidSendSlaveAdressWithRead(u8 Copy_u8Address);

void TWI_voidMasterSendDataByte(u8 Copy_u8DataByte);

u8 TWI_u8MasterRecieveDataByte(void);

void TWI_voidSendStopCondition(void);
#endif
