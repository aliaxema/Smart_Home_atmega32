#ifndef BIT_MATH_H
#define BIT_MATH_H

#define F_CPU 16000000UL
#include <util/delay.h>		
#include <avr/interrupt.h> 


#define SET_BIT(Reg, bit)                 (Reg) |=  (1 << (bit))
#define CLEAR_BIT(Reg, bit)               (Reg) &= (~(1 << (bit)))
#define TOG_BIT(Reg, bit)                 (Reg) ^=  (1 << (bit))
#define GET_BIT(Reg, bit)                 (((Reg) >> (bit)) & (1))


#define SETBIT(REG,BIT)  ((REG) |= (1<<(BIT)))
#define CLRBIT(REG,BIT)  ((REG) &= ~(1<<(BIT)))
#define TOGBIT(REG,BIT)  ((REG) ^= (1<<(BIT)))
#define READBIT(REG,BIT) (((REG) >> (BIT)) & 1)

#define CLR_BIT(reg,bit)         ((reg)&=(~((1)<<(bit))))
#define READ_BIT(reg,bit)        (((reg)>>(bit))&1)
#define WRITE_BIT(reg,bit,val)   reg=(reg&((~(1<<bit))|(val<<bit))|(val<<bit))

#define TOGGLE_BIT(VAR,BIT_NUM)    (VAR)^=(1<<(BIT_NUM))
#define BIT_IS_CLEAR(REG,BIT)      ( !(REG & (1<<BIT)) )

#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )


#endif

