/*****************************************************/
/********** SWC : TIMER0 *****************************/
/********** Date : 30 August 2024 ********************/
/********** Author : MAHMOUD ABDELGHANI **************/
/********** Version :1.0          ********************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER0_interface.h"
#include "TIMER0_private.h"
#include "TIMER0_config.h" 

static void(*GlobalPtrFuncCMP)(void)=NULL;
static void(*GlobalPtrFuncOVF)(void)=NULL;

void TIMER0_voidInit(void)
{
	//  CTC OR OVF
#if TIMER0_MODE == OVF_MODE
	CLR_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);
#elif TIMER0_MODE == CTC_MODE
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

#else
#error("Wrong Mode")
#endif
	// ENABLE INT -> MODE
#if INT_SRC == OVF_MODE
	SET_BIT(TIMSK,TIMSK_TOIE0);
#elif INT_SRC == CTC_MODE
	SET_BIT(TIMSK,TIMSK_OCIE0);
#else
#error("Wrong Int Mode")
#endif
	// PRESCALLER
#if PRE_SCALLER == NO_DIV
	TCCR0 &= 0b11111000;
	TCCR0 |= NO_DIV;
#elif PRE_SCALLER == DIV_8
	TCCR0 &= 0b11111000;
	TCCR0 |= DIV_8;
#elif PRE_SCALLER == DIV_64
	TCCR0 &= 0b11111000;
	TCCR0 |= DIV_64;
#elif PRE_SCALLER == DIV_256
	TCCR0 &= 0b11111000;
	TCCR0 |= DIV_256;
#elif PRE_SCALLER == DIV_1024
	TCCR0 &= 0b11111000;
	TCCR0 |= DIV_1024;
#else
#error("Wrong PreScaler")
#endif
}
void TIMER0_voidSetPreLoadValue(u8 Copy_u8Ticks)
{
	TCNT0=Copy_u8Ticks;
}
void TIMER0_voidSetCmpValue(u8 Copy_u8Ticks)
{
	OCR0=Copy_u8Ticks;
}
Std_err_e TIMER0_e_SetCallBackOVF(void(*PtrFunc)(void))
{
	Std_err_e Local_e_ErrorStatus=OK;
	if(PtrFunc != NULL)
	{
		GlobalPtrFuncOVF=PtrFunc;
	}
	else
	{
		Local_e_ErrorStatus=NOK;
	}
	return Local_e_ErrorStatus;
}

Std_err_e TIMER0_e_SetCallBackCMP(void(*PtrFunc)(void))
{
	Std_err_e Local_e_ErrorStatus=OK;
	if(PtrFunc != NULL)
	{
		GlobalPtrFuncCMP=PtrFunc;
	}
	else
	{
		Local_e_ErrorStatus=NOK;
	}
	return Local_e_ErrorStatus;
}
void TIMER0_voidCTCEnable(void)
{
  SET_BIT(TIMSK,TIMSK_OCIE0);
}
void TIMER0_voidCTCDisable(void)
{
	CLR_BIT(TIMSK,TIMSK_OCIE0);
}
// ISR OVF
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	// INVOKE FUNCTION
	GlobalPtrFuncOVF();
}
//ISR CTC
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	GlobalPtrFuncCMP();
}

