/*********************************************************************/
/******************************* SWC : I2C ***************************/ 
/******************************* DATE : 9 SEPTEMPER 2024 *************/
/********** Author : MAHMOUD ABDELGHANI ******************************/
/******************************* Version : 1.0 ***********************/
#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

#define TWBR      *((volatile u8*)0X20)

#define TWCR      *((volatile u8*)0X56)

#define TWCR_TWINT       7
#define TWCR_TWEA        6
#define TWCR_TWSTA       5
#define TWCR_TWSTO       4
#define TWCR_TWEN        2

#define TWSR      *((volatile u8*)0X21)

#define TWSR_TWPS1       1
#define TWSR_TWPS0       0

#define TWDR      *((volatile u8*)0X23)

#define TWAR      *((volatile u8*)0X22)
#endif
