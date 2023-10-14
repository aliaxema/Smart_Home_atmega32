/*
 * GI_Prog.c
 *
 * Created: 11-Sep-23 11:53:08 AM
 *  Author: lenovo
 */ 
#include "GI_Inter.h"

void GI_Enable(void)
{
	SETBIT(SREG,I);
}
void GI_Disable(void)
{
	CLRBIT(SREG,I);
}