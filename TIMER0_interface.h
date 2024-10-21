/*****************************************************/
/********** SWC : TIMER0 *****************************/
/********** Date : 30 August 2024 ********************/
/********** Author : MAHMOUD ABDELGHANI **************/
/********** Version :1.0          ********************/
#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

void TIMER0_voidInit(void);

void TIMER0_voidSetPreLoadValue(u8 Copy_u8Ticks);

void TIMER0_voidSetCmpValue(u8 Copy_u8Ticks);

Std_err_e TIMER0_e_SetCallBackOVF(void(*PtrFunc)(void));

Std_err_e TIMER0_e_SetCallBackCMP(void(*PtrFunc)(void));

void TIMER0_voidCTCEnable(void);

void RIMER0_voidCTCDisable(void);

#endif
