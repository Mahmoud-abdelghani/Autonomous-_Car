/*
 * US_program.c
 *
 *  Created on: Sep 21, 2024
 *      Author: mahmoud
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "GI_interface.h"
#include "TIMER0_interface.h"
#include "US_interface.h"
#include "US_private.h"
#include <util/delay.h>

f64 Global_f64time=0;
f64 *Global_f64Reading=0;


static void TimeCalculation(void)
{
	Global_f64time+=100;
}
 void FuncOfTime(void)
{
	static u8 Local_u8Counter=0;
	Local_u8Counter++;
	if (Local_u8Counter==1)
	{
		TIMER0_voidCTCEnable();
		Global_f64time=0;
		EXTI_voidSetSenseCtrl(INT_0,falling_edge);
		//ECHO_FLAG++;
	}
	else if (Local_u8Counter==2)
	{

		Local_u8Counter=0;
		*Global_f64Reading=Global_f64time;
		TIMER0_voidCTCDisable();
		//ECHO_FLAG--;
	}
}

void US_voidGetDistance(u8 Copy_u8TrigPort,u8 Copy_u8TrigPin,f64 *Copy_f64Reading)
{
	GI_voidEnable();
	Global_f64Reading=Copy_f64Reading;
	TIMER0_e_SetCallBackCMP(TimeCalculation);
	TIMER0_voidSetCmpValue(100);
	TIMER0_voidInit();
	TIMER0_voidCTCDisable();
	DIO_voidSetPinValue(Copy_u8TrigPort,Copy_u8TrigPin,PIN_LOW);
	_delay_us(2);
	DIO_voidSetPinValue(Copy_u8TrigPort,Copy_u8TrigPin,PIN_HIGH);
	_delay_us(10);
	DIO_voidSetPinValue(Copy_u8TrigPort,Copy_u8TrigPin,PIN_LOW);
	EXTI_voidEnableDisable(INT_0,Enabled);
	EXTI_voidSetSenseCtrl(INT_0,rising_edge);
	EXTI_voidSetCallBack(INT_0,FuncOfTime);
	_delay_ms(20);
}
