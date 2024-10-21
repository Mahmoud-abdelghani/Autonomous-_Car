/*****************************************************/
/********** SWC : TIMER1 *****************************/
/********** Date : 30 August 2024 ********************/
/********** Author : MAHMOUD ABDELGHANI **************/
/********** Version :1.0          ********************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "TIMER1_interface.h"
#include "TIMER1_config.h"
#include "TIMER1_private.h"

void TIMER1_voidInit(void)
{
  // WGM ->14
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
  // MAX VALUE OF TICKS = 20000
	ICR1=20000;
  // PRESCALLER/8
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
}
void TIMER1_voidSeTCMPValue(u16 Copy_u16Ticks)
{
  OCRA=Copy_u16Ticks;
}

