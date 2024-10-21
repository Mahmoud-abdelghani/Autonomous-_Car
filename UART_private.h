/*****************************************************/
/********** SWC : UART *******************************/
/********** Date : 4 SEPTEMPER 2024 ******************/
/********** Author : AHMED MOHAMED *******************/
/********** Version :1.0          ********************/
#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define UDR      *((volatile u8*)0X2C)

#define UCSRA    *((volatile u8*)0X2B)

#define UCSRA_UDRE    5
#define UCSRA_RXC     7
#define UCSRB    *((volatile u8*)0X2A)

#define  UCSRB_RXCIE     7
#define  UCSRB_TXCIE     6
#define  UCSRB_UDRIE     5
#define  UCSRB_RXEN      4
#define  UCSRB_TXEN      3
#define  UCSRB_UCSZ2     2
#define  UCSRB_RXB8      1
#define  UCSRB_TXB8      0

#define UCSRC     *((volatile u8*)0X40)

#define UCSRC_URSEL   7
#define UCSRC_UMSEL   6
#define UCSRC_UPM1    5
#define UCSRC_UPM0    4
#define UCSRC_USBS    3
#define UCSRC_UCSZ1   2
#define UCSRC_UCSZ0   1

#define UPRRL     *((volatile u8*)0x29)

#define BIT_5  1
#define BIT_6  2
#define BIT_7  3
#define BIT_8  4
#define BIT_9  5

#define BAUD_2400    1
#define BAUD_4800    2
#define BAUD_9600    3
#define BAUD_14400   4
#define BAUD_19200   5
#define BAUD_28800   6
#define BAUD_38400   7
#define BAUD_57600   8
#define BAUD_76800   9
#define BAUD_115200  10
#define BAUD_230400  11
#define BAUD_250000  12
#define BAUD_500000  13

#define  NO_PARITY    1
#define  EVEN_PARITY  2
#define  ODD_PARITY   3

#define  SYNCHRONOUS   1
#define  ASYNCHRONOUS  2

#define BIT_1      1
#define BIT_2      2

#define IDLE       1
#define BUSY       2
#endif
