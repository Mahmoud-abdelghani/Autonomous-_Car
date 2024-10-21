/*********************************************************************/
/******************************* SWC : I2C ***************************/ 
/******************************* DATE : 9 SEPTEMPER 2024 *************/
/********** Author : MAHMOUD ABDELGHANI ******************************/
/******************************* Version : 1.0 ***********************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_config.h"

void TWI_voidMasterInit(u8 Copy_u8Address)
{
	// Set Clock Frequency TWPR= 12 CLR PS1,PS0 -> 160KHZ
	TWBR=12;
	CLR_BIT(TWSR,TWSR_TWPS0);
	CLR_BIT(TWSR,TWSR_TWPS1);
	// ENABLE ACK
	SET_BIT(TWCR,TWCR_TWEA);
	// SET ADDRESS
	TWAR=Copy_u8Address<<1;
	// ENABLE ERIPHRAL
	SET_BIT(TWCR,TWCR_TWEN);
}

void TWI_voidSlaveInit(u8 Copy_u8Address)
{
	// ENABLE ACK
	SET_BIT(TWCR,TWCR_TWEA);
	// SET ADDRESS
	TWAR=Copy_u8Address<<1;
	// ENABLE ERIPHRAL
	SET_BIT(TWCR,TWCR_TWEN);
}

void TWI_voidSendStartCondition(void)
{
	// SEND START CONDITION
	SET_BIT(TWCR,TWCR_TWSTA);
	// DOWN FLAG
	SET_BIT(TWCR,TWCR_TWINT);
	// WAIT FLAG
	while(GET_BIT(TWCR,TWCR_TWINT)==0);
}

void TWI_voidSendSlaveAdressWithWrite(u8 Copy_u8Address)
{
	//Set slave Adrees in Data Reg  -> 7MSB ,CLR BIT0
	TWDR=Copy_u8Address<<1;
	CLR_BIT(TWDR,0);
	//CLR BIT START CONDITION
	CLR_BIT(TWCR,TWCR_TWSTA);
	// FLAG DOWN
	SET_BIT(TWCR,TWCR_TWINT);
	//wait for flag
	while(GET_BIT(TWCR,TWCR_TWINT)==0);
}

void TWI_voidSendSlaveAdressWithRead(u8 Copy_u8Address)
{
	//Set slave Adrees in Data Reg  -> 7MSB ,CLR BIT0
	TWDR=Copy_u8Address<<1;
	SET_BIT(TWDR,0);
	//CLR BIT START CONDITION
	CLR_BIT(TWCR,TWCR_TWSTA);
	// FLAG DOWN
	SET_BIT(TWCR,TWCR_TWINT);
	//wait for flag
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

}

void TWI_voidMasterSendDataByte(u8 Copy_u8DataByte)
{
	TWDR=Copy_u8DataByte;
	// DOWN FLAG
	SET_BIT(TWCR,TWCR_TWINT);
	// WAIT FLAG
	while(GET_BIT(TWCR,TWCR_TWINT)==0);
}

u8 TWI_u8MasterRecieveDataByte(void)
{
	// DOWN FLAG
	SET_BIT(TWCR,TWCR_TWINT);
	// WAIT FLAG
	while(GET_BIT(TWCR,TWCR_TWINT)==0);
	return TWDR;
}

void TWI_voidSendStopCondition(void)
{
	SET_BIT(TWCR,TWCR_TWSTO);
}
