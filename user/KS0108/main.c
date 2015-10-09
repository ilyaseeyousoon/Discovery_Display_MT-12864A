//-------------------------------------------------------------------------------------------------
// (c) Rados³aw Kwiecieñ, radek@dxp.pl
// http://en.radzio.dxp.pl
//-------------------------------------------------------------------------------------------------
#include "KS0108.h"


int main(void)
{
GLCD_Initialize();
GLCD_ClearScreen();
GLCD_Circle(5, 5 ,5);
GLCD_GoTo(0,0);
GLCD_WriteString("+-------------------+");
GLCD_GoTo(0,1);
GLCD_WriteString("|     Universal     |");
GLCD_GoTo(0,2);
GLCD_WriteString("|   KS0108 library  |");
GLCD_GoTo(0,3);
GLCD_WriteString("|                   |");
GLCD_GoTo(0,4);
GLCD_WriteString("|  en.radzio.dxp.pl |");
GLCD_GoTo(0,5);
GLCD_WriteString("|  STM32 Cortex-M3  |");
GLCD_GoTo(0,6);
GLCD_WriteString("|  microcontrollers |");
GLCD_GoTo(0,7);
GLCD_WriteString("+-------------------+");

for( ; ; );
return 0;
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
