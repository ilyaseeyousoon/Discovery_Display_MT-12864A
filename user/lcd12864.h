
// Пауза

void Delay(volatile uint32_t nCount) {
    for (; nCount != 0; nCount--);
}

// Запись байта в ЖК

void LcdByte(uint32_t byte)
{
	GPIOC->ODR = byte;	   	// Вывод в порт
	Delay(0x000F);		   	// Пауза 1 мкс
	GPIOC->BSRR = GPIO_BSRR_BS9;    // Выставляем Е
	Delay(0x000F);		   	// Пауза 1 мкс
	GPIOC->BSRR = GPIO_BSRR_BR9;	// Сбрасываем Е
	Delay(0x000F);		   	// Пауза 1 мкс
}

void CodeL(uint32_t code)
{
	code |= 0x0900;    // Побитное ИЛИ кода с командой в левый кристалл
	LcdByte(code);
}

void CodeR(uint32_t code)
{
	code |= 0x1100;    // Побитное ИЛИ кода с командой в правый кристалл
	LcdByte(code);
}

void DataL(uint32_t code)
{
	code |= 0x2900;    // Побитное ИЛИ данных с командой в левый кристалл
 	LcdByte(code);
}

void DataR(uint32_t code)
{
	code |= 0x3100;    // Побитное ИЛИ данных с командой в правый кристалл
	LcdByte(code);
}


