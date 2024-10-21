/*****************************************************/
/********** SWC : TIMER2 *****************************/
/********** Date : 24 Septemper 2024 ********************/
/********** Author : MAHMOUD ABDELGHANI **************/
/********** Version :1.0          ********************/
#ifndef TIMER2_CONFIG_H_
#define TIMER2_CONFIG_H_

/*
 * OPTIONS:
 * CTC_MODE
 * OVF_MODE
 */

#define TIMER2_MODE    CTC_MODE

/*
 * OPTIONS:
 * NO_DIV
 * DIV_8
 * DIV_32
 * DIV_64
 * DIV_128
 * DIV_256
 * DIV_1024
 */

#define PRESCALER  DIV_64

/*
 * OPTIONS:
 * OVF
 * CTC
 */
#define INT_SOURCE   CTC

#endif
