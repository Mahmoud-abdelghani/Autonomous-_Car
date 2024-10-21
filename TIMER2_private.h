/*****************************************************/
/********** SWC : TIMER2 *****************************/
/********** Date : 24 Septemper 2024 ********************/
/********** Author : MAHMOUD ABDELGHANI **************/
/********** Version :1.0          ********************/
#ifndef TIMER2_PRIVATE_H_
#define TIMER2_PRIVATE_H_

#define TCCR2        *((volatile u8*)0X45)

#define TCCR2_WGM20       6
#define TCCR2_WGM21       3
#define TCCR2_COM21       5
#define TCCR2_COM20       4
#define TCCR2_CS22        2
#define TCCR2_CS21        1
#define TCCR2_CS20        0

#define TCNT2       *((volatile u8*)0X44)

#define OCR2        *((volatile u8*)0X43)

#define TIMSK       *((volatile u8*)0X59)

#define TIMSK_OCIE2     7
#define TIMSK_TOIE2     6

#define CTC_MODE        1
#define OVF_MODE        2

#define NO_DIV          1
#define DIV_8           2
#define DIV_32          3
#define DIV_64          4
#define DIV_128         5
#define DIV_256         6
#define DIV_1024        7

#define OVF             1
#define CTC             2

#endif
