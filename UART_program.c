/*****************************************************/
/********** SWC : UART *******************************/
/********** Date : 4 SEPTEMPER 2024 ******************/
/********** Author : AHMED MOHAMED *******************/
/********** Version :1.0          ********************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"

static u8 UART_u8Status=IDLE;
static void(*Global_voidPtrFuncSend)(void)=NULL;
static void(*Global_voidPtrFuncRecieve)(void)=NULL;
static u8 Global_u8PtrSend=0;
static u8*Global_u8PtrRecive=NULL;
void UART_voidInit(void)
{
	// CHOOSE CHAR SIZE
	u8 Local_u8CTRLCValue=0;
#if  CHAR_SIZE == BIT_5
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	CLR_BIT(Local_u8CTRLCValue,UCSRC_UCSZ1);
	CLR_BIT(Local_u8CTRLCValue,UCSRC_UCSZ0);
#elif CHAR_SIZE == BIT_6
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	CLR_BIT(Local_u8CTRLCValue,UCSRC_UCSZ1);
	SET_BIT(Local_u8CTRLCValue,UCSRC_UCSZ0);
#elif CHAR_SIZE == BIT_7
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	SET_BIT(Local_u8CTRLCValue,UCSRC_UCSZ1);
	CLR_BIT(Local_u8CTRLCValue,UCSRC_UCSZ0);
#elif  CHAR_SIZE == BIT_8
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	SET_BIT(Local_u8CTRLCValue,UCSRC_UCSZ1);
	SET_BIT(Local_u8CTRLCValue,UCSRC_UCSZ0);
#elif  CHAR_SIZE == BIT_9
	SET_BIT(UCSRB,UCSRB_UCSZ2);
	SET_BIT(Local_u8CTRLCValue,UCSRC_UCSZ1);
	SET_BIT(Local_u8CTRLCValue,UCSRC_UCSZ0);
#else
#error("WRONG SIZE")
#endif
	// CHOOSE BAUD RATE
#if BAUD_RATE == BAUD_2400
	UPRRL=207;
#elif  BAUD_RATE == BAUD_4800
	UPRRL=103;
#elif BAUD_RATE == BAUD_9600
	UPRRL=51;
#elif BAUD_RATE == BAUD_14400
	UPRRL=34;
#elif BAUD_RATE == BAUD_19200
	UPRRL=25;
#elif BAUD_RATE == BAUD_28800
	UPRRL=16;
#elif BAUD_RATE == BAUD_38400
	UPRRL=12;
#elif BAUD_RATE == BAUD_57600
	UPRRL=8;
#elif BAUD_RATE == BAUD_76800
	UPRRL=6;
#elif BAUD_RATE == BAUD_115200
	UPRRL=3;
#elif BAUD_RATE == BAUD_230400
	UPRRL=1;
#elif BAUD_RATE == BAUD_250000
	UPRRL=1;
#elif BAUD_RATE == BAUD_500000
	UPRRL=0;
#else
#error("WRONG BAUD RATE")
#endif
	// NO INT
	CLR_BIT(UCSRB,UCSRB_RXCIE);
	CLR_BIT(UCSRB,UCSRB_TXCIE);
	CLR_BIT(UCSRB,UCSRB_UDRIE);
	// ENABLE RECIEVER TRANSIMETTER
	SET_BIT(UCSRB,UCSRB_RXEN);
	SET_BIT(UCSRB,UCSRB_TXEN);
	// select ucsrc
	SET_BIT(Local_u8CTRLCValue,UCSRC_URSEL);
	// set asunchronus mode
#if MODE_OPERATION == ASYNCHRONOUS
	CLR_BIT(Local_u8CTRLCValue,UCSRC_UMSEL);
#elif MODE_OPERATION == SYNCHRONOUS
	SET_BIT(Local_u8CTRLCValue,UCSRC_UMSEL);
#else
#error ("WRONG MODE")
#endif

#if PARITY_MODE == NO_PARITY
	CLR_BIT(Local_u8CTRLCValue,UCSRC_UPM1);
	CLR_BIT(Local_u8CTRLCValue,UCSRC_UPM0);
#elif PARITY_MODE == ODD_PARITY
	SET_BIT(Local_u8CTRLCValue,UCSRC_UPM1);
	SET_BIT(Local_u8CTRLCValue,UCSRC_UPM0);
#elif PARITY_MODE == EVEN_PARITY
	SET_BIT(Local_u8CTRLCValue,UCSRC_UPM1);
	CLR_BIT(Local_u8CTRLCValue,UCSRC_UPM0);
#else
#error("WRONG PARITY MODE")
#endif

#if STOP_BITS == BIT_1
	CLR_BIT(Local_u8CTRLCValue,UCSRC_USBS);
#elif STOP_BITS == BIT_2
	SET_BIT(UCSRC,UCSRC_USBS);
#else
#error("WRONG NUMBER OF STOP BITS")
#endif
UCSRC=Local_u8CTRLCValue;
}

Std_err_e UART_voidSendDataSynch(u8 Copy_u8Data)
{
	Std_err_e Local_e_ErrStatus = OK;
	u32 Local_u32Counter=0;

		while((!GET_BIT(UCSRA,UCSRA_UDRE)) && (Local_u32Counter < TIME_OUT_CYCLE))
		{
			Local_u32Counter++;
		}
		if(Local_u32Counter == TIME_OUT_CYCLE)
		{
			Local_e_ErrStatus=TIME_OUT_ERR;
		}
		else
		{
			UDR = Copy_u8Data;
		}

	return Local_e_ErrStatus;
}
Std_err_e UART_u8RecieveDataSynch(u8 *Copy_u8Reading)
{
	Std_err_e Local_e_ErrStatus = OK;
	u32 Local_u32Counter=0;
	if(Copy_u8Reading != NULL)
	{
		while((!GET_BIT(UCSRA,UCSRA_RXC)) && Local_u32Counter < TIME_OUT_CYCLE)
		{
			Local_u32Counter++;
		}
		if(Local_u32Counter == TIME_OUT_CYCLE)
		{
			Local_e_ErrStatus=TIME_OUT_ERR;
		}
		else
		{
			*Copy_u8Reading = UDR;
		}
	}
	else
	{
		Local_e_ErrStatus=NOK;
	}
	return Local_e_ErrStatus;
}
Std_err_e UART_voidSendDataAsynch(u8 Copy_u8Data,void(*PtrFuncNot)(void))
{
	Std_err_e Local_e_ErrStatus = OK;
	if(UART_u8Status == IDLE)
	{
		if(PtrFuncNot != NULL)
		{
			UART_u8Status = BUSY;
			Global_u8PtrSend=Copy_u8Data;
			Global_voidPtrFuncSend = PtrFuncNot;
			SET_BIT(UCSRB,UCSRB_UDRIE);
		}
	}
	else
	{
		Local_e_ErrStatus = NOK;
	}
	return Local_e_ErrStatus;
}

void __vector_14(void)  __attribute__((signal));
void __vector_14(void)
{
	UART_u8Status = IDLE;
	UDR = Global_u8PtrSend;
	Global_voidPtrFuncSend();
	CLR_BIT(UCSRB,UCSRB_UDRIE);
}



Std_err_e UART_u8RecieveDataAsynch(u8 *Copy_u8Reading,void(*PtrFuncNot)(void))
{
	Std_err_e Local_e_ErrStatus = OK;
	if(UART_u8Status == IDLE)
	{
		if((Copy_u8Reading != NULL) && (PtrFuncNot != NULL))
		{
			UART_u8Status = BUSY;
			Global_voidPtrFuncRecieve = PtrFuncNot;
			Global_u8PtrRecive = Copy_u8Reading;
			SET_BIT(UCSRB,UCSRB_RXCIE);
		}
	}
	else
	{
		Local_e_ErrStatus=NOK;
	}
	return Local_e_ErrStatus;
}
void __vector_13(void)  __attribute__((signal));
void __vector_13(void)
{
	UART_u8Status = IDLE;
	*Global_u8PtrRecive=UDR;
	Global_voidPtrFuncRecieve();
	CLR_BIT(UCSRB,UCSRB_RXCIE);
}
