/*********************************************************************/
/******************************* SWC : DIO ***************************/ 
/******************************* DATE : 13 AUGUST 2024 ***************/
/********** Author : MAHMOUD ABDELGHANI ******************************/
/******************************* Version : 1.0 ***********************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_config.h"
#include "DIO_private.h"

#define MAX_PIN_NUM  7



void DIO_voidSetPortDirection(u8 Copy_u8PortNum ,u8 Copy_u8PortDir)
{
	switch(Copy_u8PortNum)
	{
		case PORT_u8A:
		{
			DDRA=Copy_u8PortDir;
			break;
		}
		case PORT_u8B:
		{
			DDRB=Copy_u8PortDir;
			break;
		}
		case PORT_u8C:
		{
			DDRC=Copy_u8PortDir;
			break;
		}
		case PORT_u8D:
		{
			DDRD=Copy_u8PortDir;
			break;
		}
		
	}
}
void DIO_voidSetPortValue(u8 Copy_u8PortNum ,u8 Copy_u8PortValue)
{
   switch(Copy_u8PortNum)
	{
		case PORT_u8A:
		{
			PORTA=Copy_u8PortValue;
			break;
		}
		case PORT_u8B:
		{
			PORTB=Copy_u8PortValue;
			break;
		}
		case PORT_u8C:
		{
			PORTC=Copy_u8PortValue;
			break;
		}
		case PORT_u8D:
		{
			PORTD=Copy_u8PortValue;
			break;
		}
		
	}	
}
void DIO_voidSetPinDirection(u8 Copy_u8PortNum,u8 Copy_u8PinNum, u8 Copy_u8PinDir)
{
	if(Copy_u8PinNum <= MAX_PIN_NUM)
	{
		if(Copy_u8PinDir == PIN_OUT)
		{
			switch(Copy_u8PortNum)
			{
				case PORT_u8A :
				{
					SET_BIT(DDRA,Copy_u8PinNum);
					break;
				}
				case PORT_u8B :
				{
					SET_BIT(DDRB,Copy_u8PinNum);
					break;
				}
				case PORT_u8C :
				{
					SET_BIT(DDRC,Copy_u8PinNum);
					break;
				}
				case PORT_u8D :
				{
					SET_BIT(DDRD,Copy_u8PinNum);
					break;
				}
			}
		}
		else if(Copy_u8PinDir == PIN_IN)
		{
			switch(Copy_u8PortNum)
			{
				case PORT_u8A :
				{
					CLR_BIT(DDRA,Copy_u8PinNum);
					break;
				}
				case PORT_u8B :
				{
					CLR_BIT(DDRB,Copy_u8PinNum);
					break;
				}
				case PORT_u8C :
				{
					CLR_BIT(DDRC,Copy_u8PinNum);
					break;
				}
				case PORT_u8D :
				{
					CLR_BIT(DDRD,Copy_u8PinNum);
					break;
				}
			}
		}
	}
}
void DIO_voidSetPinValue(u8 Copy_u8PortNum ,u8 Copy_u8PinNum , u8 Copy_u8PinValue)
{
	if(Copy_u8PinNum <= MAX_PIN_NUM)
	{
		if(Copy_u8PinValue == PIN_HIGH)
		{
			switch(Copy_u8PortNum)
			{
				case PORT_u8A :
				{
					SET_BIT(PORTA,Copy_u8PinNum);
					break;
				}
				case PORT_u8B :
				{
					SET_BIT(PORTB,Copy_u8PinNum);
					break;
				}
				case PORT_u8C :
				{
					SET_BIT(PORTC,Copy_u8PinNum);
					break;
				}
				case PORT_u8D :
				{
					SET_BIT(PORTD,Copy_u8PinNum);
					break;
				}
			}
		}
		else if(Copy_u8PinValue == PIN_LOW)
		{
			switch(Copy_u8PortNum)
			{
				case PORT_u8A :
				{
					CLR_BIT(PORTA,Copy_u8PinNum);
					break;
				}
				case PORT_u8B :
				{
					CLR_BIT(PORTB,Copy_u8PinNum);
					break;
				}
				case PORT_u8C :
				{
					CLR_BIT(PORTC,Copy_u8PinNum);
					break;
				}
				case PORT_u8D :
				{
					CLR_BIT(PORTD,Copy_u8PinNum);
					break;
				}
			}
		}
	}
}

u8 DIO_u8GetPinValue(u8 Copy_u8PortNum ,u8 Copy_u8PinNum)
{
	u8 Local_u8PinState=0;
	
	switch(Copy_u8PortNum)
	{
		case PORT_u8A:
		{
			Local_u8PinState = GET_BIT(PINA,Copy_u8PinNum);
			break;
		}
		case PORT_u8B:
		{
			Local_u8PinState = GET_BIT(PINB,Copy_u8PinNum);
			break;
		}
		case PORT_u8C:
		{
			Local_u8PinState = GET_BIT(PINC,Copy_u8PinNum);
			break;
		}
		case PORT_u8D:
		{
			Local_u8PinState = GET_BIT(PIND,Copy_u8PinNum);
			break;
		}
		
	}
	return Local_u8PinState;
}

void DIO_voidTooglePin(u8 Copy_u8PortNum , u8 Copy_u8PinNum)
{
    	switch(Copy_u8PortNum)
			{
				case PORT_u8A :
				{
					TOG_BIT(PORTA,Copy_u8PinNum);
					break;
				}
				case PORT_u8B :
				{
					TOG_BIT(PORTB,Copy_u8PinNum);
					break;
				}
				case PORT_u8C :
				{
					TOG_BIT(PORTC,Copy_u8PinNum);
					break;
				}
				case PORT_u8D :
				{
					TOG_BIT(PORTD,Copy_u8PinNum);
					break;
				}
			}
}
