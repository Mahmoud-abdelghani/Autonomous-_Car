#ifndef STD_TYPES_
#define STD_TYPES_

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned short int u16;
typedef signed short int s16;

typedef unsigned long int u32;
typedef signed long int s32;

typedef unsigned long long int u64;
typedef signed long long int s64;

typedef float f32;
typedef double f64;

typedef long double f128;

#define NULL    (void*)0

typedef enum
{
	OK,
	NOK,
	TIME_OUT_ERR,
}Std_err_e;
#endif
