/*****************************************************/
/********** SWC : TIMER2 *****************************/
/********** Date : 24 Septemper 2024 ********************/
/********** Author : MAHMOUD ABDELGHANI **************/
/********** Version :1.0          ********************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER2_interface.h"
#include "TIMER2_private.h"
#include "TIMER2_config.h" 

static void(*GlobalPtrFuncCMP)(void)=NULL;
static void(*GlobalPtrFuncOVF)(void)=NULL;

void TIMER2_voidInit(void)
{
#if TIMER2_MODE == CTC_MODE
	CLR_BIT(TCCR2,TCCR2_WGM20);
	SET_BIT(TCCR2,TCCR2_WGM21);
#elif TIMER2_MODE == OVF_MODE
	CLR_BIT(TCCR2,TCCR2_WGM20);
	CLR_BIT(TCCR2,TCCR2_WGM21);
#else
#error("WRONG MODE")
#endif

#if PRESCALER == NO_DIV
	CLR_BIT(TCCR2,TCCR2_CS22);
	CLR_BIT(TCCR2,TCCR2_CS21);
	SET_BIT(TCCR2,TCCR2_CS20);
#elif PRESCALER == DIV_8
	CLR_BIT(TCCR2,TCCR2_CS22);
	SET_BIT(TCCR2,TCCR2_CS21);
	CLR_BIT(TCCR2,TCCR2_CS20);
#elif PRESCALER == DIV_32
	CLR_BIT(TCCR2,TCCR2_CS22);
	SET_BIT(TCCR2,TCCR2_CS21);
	SET_BIT(TCCR2,TCCR2_CS20);
#elif PRESCALER == DIV_64
	SET_BIT(TCCR2,TCCR2_CS22);
	CLR_BIT(TCCR2,TCCR2_CS21);
	CLR_BIT(TCCR2,TCCR2_CS20);
#elif PRESCALER == DIV_128
	SET_BIT(TCCR2,TCCR2_CS22);
	CLR_BIT(TCCR2,TCCR2_CS21);
	SET_BIT(TCCR2,TCCR2_CS20);
#elif PRESCALER == DIV_256
	SET_BIT(TCCR2,TCCR2_CS22);
	SET_BIT(TCCR2,TCCR2_CS21);
	CLR_BIT(TCCR2,TCCR2_CS20);
#elif PRESCALER == DIV_1024
	SET_BIT(TCCR2,TCCR2_CS22);
	SET_BIT(TCCR2,TCCR2_CS21);
	SET_BIT(TCCR2,TCCR2_CS20);
#else
#error("WRONG PRE SCALER")
#endif

#if INT_SOURCE == CTC
	SET_BIT(TIMSK,TIMSK_OCIE2);
#elif INT_SOURCE == OVF
	SET_BIT(TIMSK,TIMSK_TOIE2);
#else
#error("WRONG INT SOURCE")
#endif
}
void TIMER2_voidSetPreLoadValue(u8 Copy_u8Ticks)
{
	TCNT2=Copy_u8Ticks;
}
void TIMER2_voidSetCmpValue(u8 Copy_u8Ticks)
{
	OCR2 = Copy_u8Ticks;
}
Std_err_e TIMER2_e_SetCallBackOVF(void(*PtrFunc)(void))
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
Std_err_e TIMER2_e_SetCallBackCMP(void(*PtrFunc)(void))
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

void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
	GlobalPtrFuncCMP();
}
void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
	GlobalPtrFuncOVF();
}
