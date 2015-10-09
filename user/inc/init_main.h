#ifndef INIT_MAIN_H
#define INIT_MAIN_H
#include <stm32f10x.h>


	
	
	
	
void SysTick_Handler(void);
void delay_ms(uint32_t delay_temp);
void delay(volatile uint32_t nCount);
void init(void);

	#endif