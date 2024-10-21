/*****************************************************/
/********** SWC : CLCD *******************************/
/********** Date : 19 August 2024 ********************/
/********** Author : MAHMOUD ABDELGHANI **************/
/********** Version :1.0          ********************/

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_




void CLCD_voidInit(void);
void CLCD_voidSendString(const char *pcString);

void CLCD_voidSetPosition(u8 Copy_u8x,u8 Copy_u8y);
void CLCD_voidSendSpecialChar(u8 *pu8_arr,
		u8 Copy_u8BlockNum,
		u8 Copy_u8x,
		u8 Copy_u8y);

void CLCD_voidClearDisplay();
void CLCD_voidSendNum(u16 Copy_u16Num);





#endif
