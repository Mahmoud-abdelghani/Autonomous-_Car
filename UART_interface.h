/*****************************************************/
/********** SWC : UART *******************************/
/********** Date : 4 SEPTEMPER 2024 ******************/
/********** Author : AHMED MOHAMED *******************/
/********** Version :1.0          ********************/
#ifndef UART_INERFACE_H_
#define UART_INTERFACE_H_




void UART_voidInit(void);

Std_err_e UART_voidSendDataSynch(u8 Copy_u8Data);

Std_err_e UART_voidSendDataAsynch(u8 Copy_u8Data,void(*PtrFuncNot)(void));

Std_err_e UART_u8RecieveDataSynch(u8 *Copy_u8Reading);

Std_err_e UART_u8RecieveDataAsynch(u8 *Copy_u8Reading,void(*PtrFuncNot)(void));

#endif
