/*****************************************************/
/********** SWC : TIMER0 *****************************/
/********** Date : 30 August 2024 ********************/
/********** Author : MAHMOUD ABDELGHANI **************/
/********** Version :1.0          ********************/
#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

/*
 * Options:
 * OVF_MODE
 * CTC_MODE
 */

#define TIMER0_MODE  CTC_MODE
#define INT_SRC      CTC_MODE

/*
 * Options:
 * NO_DIV
 * DIV_8
 * DIV_64
 * DIV_256
 * DIV_1024
 */

#define PRE_SCALLER  DIV_64






#endif
