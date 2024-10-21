/*****************************************************/
/********** SWC : EXTI *******************************/
/********** Date : 25 August 2024 ********************/
/********** Author : MAHMOUD ABDELGHANI **************/
/********** Version :1.0          ********************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

static void (*GlobalPtrTofunc[3])(void)={NULL};

void EXTI_voidEnableDisable(Int_num_e Copy_e_IntNum,Int_Mode_e Copy_e_Mode)
{
	switch(Copy_e_IntNum)
	{
	case INT_0:
	{
		switch(Copy_e_Mode)
		{
		case Enabled :
		{
			SET_BIT(GICR,GICR_INT0);
			break;
		}
		case Disabled :
		{
			CLR_BIT(GICR,GICR_INT0);
			break;
		}
		}
		break;
	}
	case INT_1 :
	{
		switch(Copy_e_Mode)
		{
		case Enabled :
		{
			SET_BIT(GICR,GICR_INT1);
			break;
		}
		case Disabled :
		{
			CLR_BIT(GICR,GICR_INT1);
			break;
		}
		}

		break;
	}
	case INT_2 :
	{
		switch(Copy_e_Mode)
		{
		case Enabled :
		{
			SET_BIT(GICR,GICR_INT2);
			break;
		}
		case Disabled :
		{
			CLR_BIT(GICR,GICR_INT2);
			break;
		}
		}

		break;
	}

	}
}
void EXTI_voidSetSenseCtrl(Int_num_e Copy_e_IntNum ,Int_SenseCtrl_e Copy_e_SenseCtrl)
{
	switch(Copy_e_IntNum)
	{
	case INT_0:
	{
		switch(Copy_e_SenseCtrl)
		{
		case low_level :
		{
			CLR_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
			break;
		}
		case logical_change:
		{
			SET_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
			break;
		}
		case falling_edge:
		{
			CLR_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			break;
		}
		case rising_edge:
		{
			SET_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			break;
		}
		}
		break;
	}
	case INT_1:
	{
		switch(Copy_e_SenseCtrl)
		{
		case low_level :
		{
			CLR_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);
			break;
		}
		case logical_change:
		{
			SET_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);
			break;
		}
		case falling_edge:
		{
			CLR_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
			break;
		}
		case rising_edge:
		{
			SET_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
			break;
		}
		}
		break;
	}
	case INT_2:
	{
		switch(Copy_e_SenseCtrl)
		{
		case falling_edge:
		{
			CLR_BIT(MCUCSR,MCUCSR_ISC2);
			break;
		}
		case rising_edge:
		{
			SET_BIT(MCUCSR,MCUCSR_ISC2);
			break;
		}
		}
		break;
	}

	}
}
Std_err_e EXTI_voidSetCallBack(Int_num_e Copy_e_IntNum,void(*PvoidFunc)(void))
{
	Std_err_e Local_estate = OK;
	switch(Copy_e_IntNum)
	{
	case INT_0 :
	{
		if(PvoidFunc != NULL)
		{
			GlobalPtrTofunc[0]=PvoidFunc;
		}
		else
		{
			Local_estate=NOK;
		}
		break;
	}
	case INT_1 :
	{
		if(PvoidFunc != NULL)
		{
			GlobalPtrTofunc[1]=PvoidFunc;
		}
		else
		{
			Local_estate=NOK;
		}
		break;
	}
	case INT_2 :
	{
		if(PvoidFunc != NULL)
		{
			GlobalPtrTofunc[2]=PvoidFunc;
		}
		else
		{
			Local_estate=NOK;
		}
		break;
	}
	}
	return Local_estate;
}
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	GlobalPtrTofunc[0]();
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	GlobalPtrTofunc[1]();
}
void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	GlobalPtrTofunc[2]();
}
