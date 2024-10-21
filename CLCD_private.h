/*****************************************************/
/********** SWC : CLCD *******************************/
/********** Date : 19 August 2024 ********************/
/********** Author : MAHMOUD ABDELGHANI **************/
/********** Version :1.0          ********************/


#ifndef CLCD_PRIVATE_H_
#define CLCD_PRIVATE_H_

#define LINE1_BASE    0X40
#define MSB           128
#define CGRAM_CONS    64


static void CLCD_voidSendData(u8 Copy_u8Data);
static void CLCD_voidSendCommand(u8 Copy_u8Command);







#endif
