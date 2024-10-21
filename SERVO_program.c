/*
 * SERVO_program.c
 *
 *  Created on: Sep 24, 2024
 *      Author: mahmoud
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER1_interface.h"
#include "DIO_interface.h"

u32 Mapping (u32 Range1_max,u32 Range1_min,u32 Range2_max,u32 Range2_min,u32 Range1_reading){

	return (Range2_max-((Range2_max-Range2_min)*(Range1_max-Range1_reading)/(Range1_max-Range1_min)));
}

void SERVO_voidInit()
{
	DIO_voidSetPinDirection(PORT_u8D,PIN_5,PIN_OUT);
	TIMER1_voidInit();
}

void SERVO_voidMoveToAngle(u8 Copy_u8Angle)
{
	u32 Local_u32CMPValue=Mapping(180,0,2500,550,Copy_u8Angle);
	TIMER1_voidSeTCMPValue(Local_u32CMPValue);
}
