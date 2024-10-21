/*****************************************************/
/********** SWC : TIMER2 *****************************/
/********** Date : 24 Septemper 2024 ********************/
/********** Author : MAHMOUD ABDELGHANI **************/
/********** Version :1.0          ********************/
#ifndef TIMER2_INTERFACE_H_
#define TIMER2_INTERFACE_H_

void TIMER2_voidInit(void);

void TIMER2_voidSetPreLoadValue(u8 Copy_u8Ticks);

void TIMER2_voidSetCmpValue(u8 Copy_u8Ticks);

Std_err_e TIMER2_e_SetCallBackOVF(void(*PtrFunc)(void));

Std_err_e TIMER2_e_SetCallBackCMP(void(*PtrFunc)(void));

#endif
