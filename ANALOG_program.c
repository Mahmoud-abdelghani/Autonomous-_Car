/*
 * ANALOG_program.c
 *
 *  Created on: Sep 25, 2024
 *      Author: mahmoud
 */


#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "GI_interface.h"
#include "TIMER2_interface.h"

static u8 Global_u8AnalogValue;
static u8 Global_u8PortNum;
static u8 Global_u8PinNum_1;
void AnalogGenerator(void)
{
	static u8 Local_u8Counter=0;
	Local_u8Counter++;
	if(Local_u8Counter==Global_u8AnalogValue)
	{
		DIO_voidSetPinValue(Global_u8PortNum,Global_u8PinNum_1,PIN_HIGH);
	}
	else if(Local_u8Counter==20)
	{
		Local_u8Counter=0;
		DIO_voidSetPinValue(Global_u8PortNum,Global_u8PinNum_1,PIN_LOW);
	}
}
void ANALOG_voidSendSignal(u8 Copy_u8PortNum,u8 Copy_u8PinNum_1,u8 Copy_u8AnalogValue)
{
	Global_u8AnalogValue=20-Copy_u8AnalogValue;
	Global_u8PortNum=Copy_u8PortNum;
	Global_u8PinNum_1=Copy_u8PinNum_1;
	TIMER2_voidSetCmpValue(125);
	TIMER2_e_SetCallBackCMP(AnalogGenerator);
	TIMER2_voidInit();
	GI_voidEnable();
}
