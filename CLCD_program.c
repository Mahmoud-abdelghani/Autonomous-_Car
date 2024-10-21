/*****************************************************/
/********** SWC : CLCD *******************************/
/********** Date : 19 August 2024 ********************/
/********** Author : MAHMOUD ABDELGHANI **************/
/********** Version :1.0          ********************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "CLCD_private.h"
#include "CLCD_interface.h"
#include "CLCD_config.h"
#include <util/delay.h>

static void CLCD_voidSendData(u8 Copy_u8Data)
{
	//RS=1 , RW=0
	DIO_voidSetPinValue(CTRL_PORT,RS,PIN_HIGH);
	DIO_voidSetPinValue(CTRL_PORT,RW,PIN_LOW);
	//Set data to the required port
	DIO_voidSetPortValue(DATA_PORT,Copy_u8Data);
	//Enable pulse
	DIO_voidSetPinValue(CTRL_PORT,EN,PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(CTRL_PORT,EN,PIN_LOW);
}
static void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	//RS=0 , RW=0
	DIO_voidSetPinValue(CTRL_PORT,RS,PIN_LOW);
	DIO_voidSetPinValue(CTRL_PORT,RW,PIN_LOW);
	//Set data to the required port
	DIO_voidSetPortValue(DATA_PORT,Copy_u8Command);
	//Enable pulse
	DIO_voidSetPinValue(CTRL_PORT,EN,PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(CTRL_PORT,EN,PIN_LOW);
}
void CLCD_voidInit(void)
{
	_delay_ms(40);
	CLCD_voidSendCommand(0b00111000);
	_delay_ms(1);
	CLCD_voidSendCommand(0b00001100);
	_delay_ms(1);
	CLCD_voidSendCommand(1);
	_delay_ms(2);
}
void CLCD_voidSendString(const char *pcString)
{
	u8 Local_u8Iterator=0;
	while(pcString[Local_u8Iterator]!='\0')
	{
		CLCD_voidSendData(pcString[Local_u8Iterator]);
		Local_u8Iterator++;
	}
}
void CLCD_voidSetPosition(u8 Copy_u8x,u8 Copy_u8y)
{
	u8 Local_u8Position;
	switch(Copy_u8x)
	{
	case 0:Local_u8Position=Copy_u8y;break;
	case 1:Local_u8Position=Copy_u8y+LINE1_BASE;break;
	}
	CLCD_voidSendCommand(Local_u8Position+MSB);
}
void CLCD_voidSendSpecialChar(u8 *pu8_arr,
		u8 Copy_u8BlockNum,
		u8 Copy_u8x,
		u8 Copy_u8y)
{
	//calculate starting address in cgram
	u8 Local_u8StartingAdress=Copy_u8BlockNum*8;
	//send command -> cgram
	CLCD_voidSendCommand(Local_u8StartingAdress+CGRAM_CONS);
	//START DRAWING PATTERN
	for(u8 Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		CLCD_voidSendData(pu8_arr[Local_u8Iterator]);
	}
	//SET DDRAM ADDRESS
	CLCD_voidSetPosition(Copy_u8x,Copy_u8y);
	//Display char from i  ts block
	CLCD_voidSendData(Copy_u8BlockNum);

}

void CLCD_voidClearDisplay()
{
	_delay_ms(1);
	CLCD_voidSendCommand(1);
}
void CLCD_voidSendNum(u16 Copy_u16Num)
{
	u8  arr[10],i=0,j;
	if(Copy_u16Num == 0)
	{
		CLCD_voidSendData('0');
	}
	else
	{
		while (Copy_u16Num)
		{
			arr[i]= Copy_u16Num%10+'0';
			Copy_u16Num /=10;
			i++;
		}
	}
	for(j=i;j>0;j--)
	{
		CLCD_voidSendData(arr[j-1]);
	}
}
