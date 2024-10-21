/*********************************************************************/
/******************************* SWC : DIO ***************************/ 
/******************************* DATE : 13 AUGUST 2024 ***************/
/********** Author : MAHMOUD ABDELGHANI ******************************/
/******************************* Version : 1.0 ***********************/
#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

#define PORTA   *((volatile u8*)0X3B)
#define DDRA    *((volatile u8*)0X3A)
#define PINA    *((volatile u8*)0X39)

#define PORTB   *((volatile u8*)0X38)
#define DDRB    *((volatile u8*)0X37)
#define PINB    *((volatile u8*)0X36)

#define PORTC   *((volatile u8*)0X35)
#define DDRC    *((volatile u8*)0X34)
#define PINC    *((volatile u8*)0X33)

#define PORTD   *((volatile u8*)0X32)
#define DDRD    *((volatile u8*)0X31)
#define PIND    *((volatile u8*)0X30)


#endif