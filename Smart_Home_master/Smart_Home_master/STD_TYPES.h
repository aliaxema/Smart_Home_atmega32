
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int  u16;
typedef signed short int  s16;

typedef unsigned long int  u32;
typedef signed long int  s32;
typedef unsigned long long int  u64;
typedef signed long long int  s64;

typedef float f32;
typedef double f64;
typedef long double f96;

#define NULL    0
#define Enable	1
#define Disable	0

/*********************************************************************************************/

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef unsigned long long uint64;

typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;
typedef signed long long sint64;

typedef float float32;
typedef double float64;
typedef long double float80;


/*********************************************************************************************/

#define NULLPTR ((void*)0)
#define NULL_POINTER   ((void*)0)

typedef unsigned short us16;
typedef   signed short ss16;


typedef enum{
	
	FALSE,
	TRUE
	
} bool_t;


#endif
