/*****************************************************/
/********** SWC : EXTI *******************************/
/********** Date : 25 August 2024 ********************/
/********** Author : MAHMOUD ABDELGHANI **************/
/********** Version :1.0          ********************/
#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define MCUCR        *((volatile u8*)0x55)

#define MCUCR_ISC00  0
#define MCUCR_ISC01  1
#define MCUCR_ISC10  2
#define MCUCR_ISC11  3

#define MCUCSR       *((volatile u8*)0x54)

#define MCUCSR_ISC2  6

#define GICR         *((volatile u8*)0x5B)

#define GICR_INT0    6
#define GICR_INT1    7
#define GICR_INT2    5


#endif