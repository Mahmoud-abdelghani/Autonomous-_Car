/*****************************************************/
/********** SWC : EXTI *******************************/
/********** Date : 25 August 2024 ********************/
/********** Author : MAHMOUD ABDELGHANI **************/
/********** Version :1.0          ********************/
#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


typedef enum
{
	INT_0=0,
	INT_1,
	INT_2,
}Int_num_e;

typedef enum
{
	low_level=0,
	logical_change,
	falling_edge,
	rising_edge,
}Int_SenseCtrl_e;

typedef enum
{
	Enabled=0,
	Disabled,
}Int_Mode_e;

void EXTI_voidEnableDisable(Int_num_e Copy_e_IntNum,Int_Mode_e Copy_e_Mode);
void EXTI_voidSetSenseCtrl(Int_num_e Copy_e_IntNum ,Int_SenseCtrl_e Copy_e_SenseCtrl);
Std_err_e EXTI_voidSetCallBack(Int_num_e Copy_e_IntNum,void(*PvoidFunc)(void));







#endif
