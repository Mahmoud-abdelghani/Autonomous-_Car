/*
 * main.c
 *
 *  Created on: Sep 25, 2024
 *      Author: mahmoud
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "GI_interface.h"
#include "TIMER0_interface.h"
#include "TIMER1_interface.h"
#include "TIMER2_interface.h"
#include "ANALOG_interface.h"
#include "UART_interface.h"
#include "TWI_interface.h"
#include "US_interface.h"
#include "SERVO_interface.h"
#include "CLCD_interface.h"
#include "EEPROM_interface.h"
#include <util/delay.h>

#define BLUETOOTH     1
#define ULTRASONIC    0

void SWITCH(void);

// used flags
u8 ForwardFlag=0;
u8 CaseFlag=0;
u8 WDTFLAG=0;
// UART receiver variable
u8 Local_u8Controler='f';
// variable used to display these values
u8 SPEEDCARRIER=0;
u8 OBSTECLSNUM=0;
u8 SPEEDCARRIER_B=0;
// used to carry the time from ultrasonic function
f64 Global_f64ForwardTime=0;
f64 Global_f64RightTime=0;
f64 Global_f64LeftTime=0;
// variable to carry distance
f32 Global_f32ForwardDistance=0;
f32 Global_f32RightDistance=0;
f32 Global_f32LeftDistance=0;
f32 Global_f32LastForwardDistance=0;
//display function used to update the display of LCD screen used in case of changing speed, mode and number of obstecls
void Display(void)
{
	CLCD_voidClearDisplay();
	switch(CaseFlag)
	{
	case BLUETOOTH:
	{
		CLCD_voidSendString("BLUETOOTH");
		break;
	}
	case ULTRASONIC:
	{
		CLCD_voidSendString("ULTRASONIC");
		break;
	}
	}
	CLCD_voidSetPosition(0,11);
	CLCD_voidSendString("SP:");
	if(CaseFlag==BLUETOOTH)
	{
		CLCD_voidSendNum(SPEEDCARRIER_B);
	}
	else
	{
		CLCD_voidSendNum(SPEEDCARRIER);
	}
	CLCD_voidSetPosition(1,0);
	CLCD_voidSendString("OBS:");
	CLCD_voidSendNum(OBSTECLSNUM);
}
// this functions used to move forward in ultrasonic mode
void Forward(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	ANALOG_voidSendSignal(PORT_u8B,PIN_7,10);
	SPEEDCARRIER=10;
	EEPROM_voidWriteDataByte(DEVICE1,10,SPEEDCARRIER);
	ForwardFlag = 1;
	Display();
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);

}
// this function used forward in bluetooth mode
void Forward_BLUE(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
}
// this function used to stop in ultrasonic mode
void Stop(void)
{
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
	//ForwardFlag=0;
	ForwardFlag=0;
	SPEEDCARRIER=0;
	EEPROM_voidWriteDataByte(DEVICE1,20,SPEEDCARRIER);
	Display();
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);

}
// this function used to stop in bluetooth mode
void Stop_BLUE(void)
{
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);

}
// this function used to Back in ultrasonic mode
void Back(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	ANALOG_voidSendSignal(PORT_u8B,PIN_7,8);
	SPEEDCARRIER=8;
	EEPROM_voidWriteDataByte(DEVICE1,30,SPEEDCARRIER);
	Display();
	Global_f32LastForwardDistance=Global_f32ForwardDistance;
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_HIGH);
	while(Global_f32ForwardDistance < Global_f32LastForwardDistance+3)
	{
		US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64ForwardTime);
		Global_f32ForwardDistance=0.0175*Global_f64ForwardTime;
	}
}
// this function used to stop in bluetooth mode
void Back_BLUE(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_HIGH);

	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_HIGH);
}
// this function used to Back in ultrasonic mode
void Right(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_HIGH);
	ANALOG_voidSendSignal(PORT_u8B,PIN_7,7);
	SPEEDCARRIER=7;
	EEPROM_voidWriteDataByte(DEVICE1,40,SPEEDCARRIER);
	Display();
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
	while(Global_f32ForwardDistance < 10 )
	{
		US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64ForwardTime);
		Global_f32ForwardDistance=0.0175*Global_f64ForwardTime;
	}
	/*we now rotated until we found that the forward direction is free of obsticles but don't forget the width of the car
	 * because this width there are 2 blind angles so we must make sure that these angle are empty or diatance allow the car to
	 * move forward safely*/
	Stop();
	SERVO_voidMoveToAngle(135);
	_delay_ms(500);
	US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64RightTime);
	Global_f32RightDistance=0.0175*Global_f64RightTime;
	if (Global_f32RightDistance < 10)
	{
		Display();
		DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_HIGH);
		DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_HIGH);
		DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
		DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
		DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
		while(Global_f32RightDistance < 10 )
		{
			US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64RightTime);
			Global_f32RightDistance=0.0175*Global_f64RightTime;
		}
	}
	SERVO_voidMoveToAngle(90);
}
// this function used to Right in bluetooth mode
void Right_BLUE(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
}
// this function used to Left in ultrasonic mode
void Left(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_HIGH);
	ANALOG_voidSendSignal(PORT_u8B,PIN_7,7);
	SPEEDCARRIER=7;
	EEPROM_voidWriteDataByte(DEVICE1,50,SPEEDCARRIER);
	Display();
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
	while(Global_f32ForwardDistance < 10 )
	{
		US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64ForwardTime);
		Global_f32ForwardDistance=0.0175*Global_f64ForwardTime;
	}
	/*we now rotated until we found that the forward direction is free of obsticles but don't forget the width of the car
	 * because this width there are 2 blind angles so we must make sure that these angle are empty or diatance allow the car to
	 * move forward safely*/
	Stop();
	SERVO_voidMoveToAngle(45);
	_delay_ms(500);
	US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64LeftTime);
	Global_f32LeftDistance=0.0175*Global_f64LeftTime;
	if (Global_f32LeftDistance < 10)
	{
		Display();
		DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_HIGH);
		DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
		DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
		DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_HIGH);
		DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
		while(Global_f32LeftDistance < 10 )
		{
			US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64LeftTime);
			Global_f32LeftDistance=0.0175*Global_f64LeftTime;
		}
	}
	SERVO_voidMoveToAngle(90);
}
// this function used to Left in bluetooth mode
void Left_BLUE(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
}
//bluetooth mode function
void BLUETOOTHMODE(void)
{
	// stop at the beginning of switching between mode to make system stable and avoid to enter this function while moving
	//and move in high speed until UART sends f
	Stop_BLUE();
	ANALOG_voidSendSignal(PORT_u8B,PIN_7,SPEEDCARRIER_B);
	while (1)
	{
		Display();
		UART_u8RecieveDataSynch(&Local_u8Controler);
		if(Local_u8Controler-'0' <= 9)
		{
			// this if checks if UART received numerical info so it is a value for speed else it is a direction
			SPEEDCARRIER_B=2*(Local_u8Controler-'0');
			ANALOG_voidSendSignal(PORT_u8B,PIN_7,SPEEDCARRIER_B);
			EEPROM_voidWriteDataByte(DEVICE1,60,SPEEDCARRIER_B);
		}
		// notice that each case ended with Local_u8Controler='f' to make the car stops once user gets off his finger from direction icon in mobile application
		switch(Local_u8Controler)
		{
		case 'w':
		{
			Forward_BLUE();
			Local_u8Controler='f';
			break;
		}
		case 'd':
		{
			Right_BLUE();
			Local_u8Controler='f';
			break;
		}
		case 's':
		{
			Back_BLUE();
			Local_u8Controler='f';
			break;
		}
		case 'a':
		{
			Left_BLUE();
			Local_u8Controler='f';
			break;
		}
		default :
		{
			Stop_BLUE();
			Local_u8Controler='f';
			break;
		}
		}


	}
}
// ultrasonic mode
void ULTRASONICMODE(void)
{
	while (1)
	{
		// check forward
		US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64ForwardTime);
		Global_f32ForwardDistance=0.0175*Global_f64ForwardTime;
		//check if there are accepted distance to move forward or not
		if(Global_f32ForwardDistance > 6)
		{
			// the next if here make the system to git in forward function fore one time only after car stop
			//this saves the time in this case for checking operation only
			if(ForwardFlag != 1)
			{
				Forward();
			}
		}
		else if(Global_f32ForwardDistance <= 6)
		{
			//increment the number of obsticles any time the car stops
			//specilay in this line to make sure that is a new obsticles
			OBSTECLSNUM++;
			EEPROM_voidWriteDataByte(DEVICE1,0,OBSTECLSNUM);
			label1:
			Stop();
			SERVO_voidMoveToAngle(0);
			_delay_ms(500);
			US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64RightTime);
			Global_f32RightDistance=0.0175*Global_f64RightTime;
			SERVO_voidMoveToAngle(180);
			_delay_ms(500);
			US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64LeftTime);
			Global_f32LeftDistance=0.0175*Global_f64LeftTime;
			SERVO_voidMoveToAngle(90);
			_delay_ms(500);
			if(Global_f32RightDistance < 8 && Global_f32LeftDistance <8)
			{
				Back();
				goto label1;
			}
			else if(Global_f32RightDistance >= Global_f32LeftDistance)
			{
				Right();
			}
			else if(Global_f32RightDistance < Global_f32LeftDistance)
			{
				Left();
			}
		}

	}

}
// ISR for switching between modes we choose interrupt to make sure that our compiler will not waste its time to
//execute unneeded function at this time
void SWITCH(void)
{
	switch(CaseFlag)
	{
	case BLUETOOTH :
	{
		CaseFlag = ULTRASONIC;
		ULTRASONICMODE();
		break;
	}
	case ULTRASONIC :
	{
		CaseFlag = BLUETOOTH;
		BLUETOOTHMODE();
		break;
	}
	}
}

void main ()
{
	// FOR SWITCH MODE
	DIO_voidSetPinDirection(PORT_u8B,PIN_0,PIN_IN);
	DIO_voidSetPinValue(PORT_u8B,PIN_0,PIN_HIGH);
	// FOR MOTOR DRIVER
	DIO_voidSetPinDirection(PORT_u8B,PIN_3,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8B,PIN_4,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8B,PIN_5,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8B,PIN_6,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8B,PIN_7,PIN_OUT);
	// FOR US
	DIO_voidSetPinDirection(PORT_u8D,PIN_2,PIN_IN);
	DIO_voidSetPinDirection(PORT_u8B,PIN_1,PIN_OUT); // TRIG
	// FOR SERVO
	SERVO_voidInit();
	SERVO_voidMoveToAngle(90);
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
	US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64ForwardTime);
	Global_f32ForwardDistance=0.0175*Global_f64ForwardTime;
	// for switch
	DIO_voidSetPinDirection(PORT_u8D,PIN_3,PIN_IN);
	DIO_voidSetPinValue(PORT_u8D,PIN_3,PIN_HIGH);
	GI_voidEnable();
	EXTI_voidEnableDisable(INT_1,Enabled);
	EXTI_voidSetSenseCtrl(INT_1,falling_edge);
	EXTI_voidSetCallBack(INT_1,SWITCH);
	UART_voidInit();
	// for blue module
	DIO_voidSetPinDirection(PORT_u8D,PIN_0,PIN_IN);
	DIO_voidSetPinDirection(PORT_u8D,PIN_1,PIN_OUT);
	//for leds
	DIO_voidSetPinDirection(PORT_u8D,PIN_7,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8D,PIN_6,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8D,PIN_4,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8C,PIN_3,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8C,PIN_4,PIN_OUT);
	// FOR CLCD
	DIO_voidSetPortDirection(PORT_u8A,PORT_OUT);
	DIO_voidSetPinDirection(PORT_u8C,PIN_7,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8C,PIN_6,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8C,PIN_5,PIN_OUT);
	CLCD_voidInit();
	// EEPROM
	TWI_voidMasterInit(0);
	DIO_voidSetPinDirection(PORT_u8C,PIN_0,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8C,PIN_1,PIN_OUT);
	SPEEDCARRIER_B=EEPROM_u8ReadDataByte(DEVICE1,60);
	OBSTECLSNUM=EEPROM_u8ReadDataByte(DEVICE1,0);
	while(1)
	{
		// initial mode
		ULTRASONICMODE();
	}
}




