/*********************************************************************/
/******************************* SWC : DIO ***************************/ 
/******************************* DATE : 13 AUGUST 2024 ***************/
/********** Author : MAHMOUD ABDELGHANI ******************************/
/******************************* Version : 1.0 ***********************/
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


#define PORT_u8A   1
#define PORT_u8B   2
#define PORT_u8C   3 
#define PORT_u8D   4

#define PIN_0      0
#define PIN_1      1
#define PIN_2      2
#define PIN_3      3
#define PIN_4      4
#define PIN_5      5
#define PIN_6      6
#define PIN_7      7

#define PORT_IN    0X00
#define PORT_OUT   0XFF

#define PORT_LOW   0X00
#define PORT_HIGH  0XFF


#define PIN_IN      0
#define PIN_OUT     1

#define PIN_LOW     0
#define PIN_HIGH    1

void DIO_voidSetPortDirection(u8 Copy_u8PortNum ,u8 Copy_u8PortDir); //DDR
void DIO_voidSetPortValue(u8 Copy_u8PortNum ,u8 Copy_u8PortValue);//PORT

void DIO_voidSetPinDirection(u8 Copy_u8PortNum,u8 Copy_u8PinNum, u8 Copy_u8PinDir); //DDR FOR PIN
void DIO_voidSetPinValue(u8 Copy_u8PortNum ,u8 Copy_u8PinNum , u8 Copy_u8PinValue); //PORT FOR PIN

u8 DIO_u8GetPinValue(u8 Copy_u8PortNum ,u8 Copy_u8PinNum);
void DIO_voidTooglePin(u8 Copy_u8PortNum , u8 Copy_u8PinNum);



#endif