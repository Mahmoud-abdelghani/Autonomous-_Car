/*****************************************************/
/********** SWC : UART *******************************/
/********** Date : 4 SEPTEMPER 2024 ******************/
/********** Author : AHMED MOHAMED *******************/
/********** Version :1.0          ********************/
#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_


/*
 * OPTIONS:
 * BIT_5
 * BIT_6
 * BIT_7
 * BIT_8
 * BIT_9
 */

#define CHAR_SIZE    BIT_8

/*
 * OPTIONS:
 * BAUD_2400
 * BAUD_4800
 * BAUD_9600
 * BAUD_14400
 * BAUD_19200
 * BAUD_28800
 * BAUD_38400
 * BAUD_57600
 * BAUD_76800
 * BAUD_115200
 * BAUD_230400
 * BAUD_250000
 * BAUD_500000
 */

#define BAUD_RATE   BAUD_9600

/*
 * OPTIONS:
 * NO_PARITY
 * EVEN_PARITY
 * ODD_PARITY
 */

#define PARITY_MODE NO_PARITY

/*
 * OPTIONS :
 * SYNCHRONOUS
 * ASYNCHRONOUS
 */

#define MODE_OPERATION   ASYNCHRONOUS

/*
 * OPTIONS:
 * BIT_1
 * BIT_2
 */

#define STOP_BITS  BIT_1

#define TIME_OUT_CYCLE   150000
#endif
