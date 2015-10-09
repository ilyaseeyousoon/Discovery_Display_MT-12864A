#include <stm32f10x_conf.h>
#include <stm32f10x_usart.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "stm32f10x_adc.h"
#include "stm32f10x_spi.h"
#include "font5x8.h"




	uint32_t delay_count=0;	
	uint32_t b,c,d,e,f,g,h, i, j, k,p=0;
	uint16_t pos_x,pos_x=0;
	uint8_t Receive_buf[256];
 unsigned char Buffer[50];	
 unsigned char SPIBuffer[50];
 uint8_t Receive_W=0,Receive_R=0,Receive_C=0;
uint16_t  dm;
	#define KS0108_SCREEN_WIDTH		128
#define KS0108_SCREEN_HEIGHT	64
#define DISPLAY_SET_Y       0x40
#define DISPLAY_SET_X       0xB8
#define DISPLAY_START_LINE  0xC0
#define DISPLAY_ON_CMD		0x3E
uint16_t SPI1_Buffer_Tx[5] = {0xFF,0x89,0x88,0x78,0x55 };

															 
void delay(volatile uint32_t nCount)
{

	for(;nCount!=0;nCount--);
}


void init_spi()
{
	
	//????? SPI1 (Master)
	GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); 
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE);
		
 GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 );
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	 GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_6);
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	SPI_InitTypeDef SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //?????? ???????
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; // ???????? ?? 8 ???
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; // ?????????? ?
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; // ???? ????????? ???????
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	
SPI_Init(SPI1, &SPI_InitStructure);
 SPI_Cmd(SPI1, ENABLE);
	
SPI_Init(SPI1, &SPI_InitStructure);
 SPI_Cmd(SPI1, ENABLE);
	
SPI_Init(SPI1, &SPI_InitStructure);
 SPI_Cmd(SPI1, ENABLE);
	
	
	
}


void otpravka(uint32_t kill) // ОТПРАВКА ДАННЫХ НА LCD
{
 GPIO_Write(GPIOC,kill);
	delay(0x000F);
GPIO_SetBits( GPIOC,  GPIO_Pin_9);
	delay(0x000F);
	GPIO_ResetBits( GPIOC,  GPIO_Pin_9);
	delay(0x000F);
}
unsigned char GLCD_ReadByteFromROMMemory(uint8_t * ptr) // ПРИХОДИТ АДРЕС ,РАЗЫМЕНОВВЫВАЮ И ПОЛУЧАЮ ДАННЫЕ
{
  return *(ptr);
}
void komandaL(uint32_t lol) 
{
	lol|=0x0900;
otpravka(lol);
	
}

void komandaR(uint32_t mol)
{
	mol|=0x1100;
otpravka(mol);
	
}
void dataL(uint32_t ass)
{
	ass|=0x2900;
otpravka(ass);
	
}

void dataR(uint32_t byte)
{
	byte|=0x3100;
otpravka(byte);
	
}
void GLCD_WriteCharL(uint8_t charToWriteL) // ЗАПИСЬ СИМВОЛА В ЛЕВЫЙ 
{
int i;
	charToWriteL -= 32; 
for(i = 0; i < 5; i++) 
	
  dataL(GLCD_ReadByteFromROMMemory((uint8_t *)((int)font5x8 + (5 * charToWriteL) + i))); 
dataL(0x00);
}

void GLCD_WriteCharR(uint8_t charToWriteR) // ЗАПИСЬ СИМВОЛА В ПРАВЫЙ
{
int i;
charToWriteR -= 32; 
for(i = 0; i < 5; i++) 
	
  dataR(GLCD_ReadByteFromROMMemory((uint8_t *)((int)font5x8 + (5 * charToWriteR) + i))); 
dataR(0x00);
}
void kristalli(uint32_t chislo)//1 OR 2(ИСПРАВИТЬ ВКЛЮЧЕНИЕ КРИСТАЛЛОВ)
{
//	komandaL(0x3E);
//	komandaR(0x3E);
if(chislo==1)
{
komandaL(0x3F);
}

	if(chislo==2)
{
komandaR(0x3F);
}
	if(chislo==12)
{
komandaR(0x3F);
	komandaL(0x3F);
}
}
void set_xL(uint32_t pos_xL) //ПО ВЫСОТЕ ПОЛОЖЕНИЕ В ЛЕВОМ И ТД
 {
	 
	 pos_xL|=0xB8;
	 komandaL(pos_xL);
 } 
 void set_xR(uint32_t pos_xR)
 {
	 
	 pos_xR|=0xB8;
	 komandaR(pos_xR);
 } 
 void set_yL(uint32_t pos_yL)
 {
	 
	 pos_yL|=0x40;
	 komandaL(pos_yL);
 } 
 void set_yR(uint32_t pos_yR)
 {
	 
	 pos_yR|=0x40;
	 komandaR(pos_yR);
 } 
 
void GLCD_WriteStringL(char  *stringToWrite)// ЗАПИСЬ СТРОКИ В ЛЕВУЮ ЧАСТЬ ЭКРАНА(ПЕРЕДЕЛЕЛАТЬ,ЧТОБЫ 
//В ЗАВИСИМОСТИ ОТ ТОГО КАКОЙ БАЙТ,ЗАПИСЫВАИСЬ ДДАНЫЕ В СВОЕ МЕСТО НА ЭКРАНЕ)СДЕЛАТЬ СЧЕТЧИК БАЙТ 
{
	
	uint8_t g=0;
	 int length = 0;
while(*stringToWrite)// ПОКА НЕ КОНЧИТСЯ СТРОКА
{	
if(length<=9)//РАЗМЕР ЧАСТИ ДИСПЛЕЯ В СИМВОЛАХ
	{
//???????

	 length++; 
     
	GLCD_WriteCharL(*stringToWrite);
	 *stringToWrite++;  
}
	
	else
	
		if(g<1)
		{
		set_xL(1);
set_yL(0);
			g++;
		}
	
else

		if(length<=19)//ВТОРАЯ СТРОКА
		{
	
	 length++; 
      
	GLCD_WriteCharL(*stringToWrite);
	 *stringToWrite++; 
		}
			else
	
		if(g<2)
		{
		set_xL(2);
set_yL(0);
			g++;
		}
	
//else

//		if(length<=29)//3 СТРОКА
//		{
//	
//	 length++; 
//      
//	GLCD_WriteCharL(*stringToWrite);
//	 *stringToWrite++; 
//				set_xL(3);
//set_yL(0);
//		}
		else 
		{break;}
}
}
void GLCD_WriteStringR(char * stringToWrite)// СТРОКА В ПРАВУЮ ЧАСТЬ(БЕЗ ОГРАНИЧЕНИЯ И ВЫРЕЗАНИЯ,ЕСЛИ ПРЕВЫСИТ ДЛИНУ ЭКРАНА)
{ 
uint8_t g=0;
	 int length = 0;
while(*stringToWrite)// ПОКА НЕ КОНЧИТСЯ СТРОКА
{	
if(length<=9)//РАЗМЕР ЧАСТИ ДИСПЛЕЯ В СИМВОЛАХ
	{
//???????

	 length++; 
     
	GLCD_WriteCharR(*stringToWrite);
	 *stringToWrite++;  
}
	else 
		{break;}
}	
}
void lcd_fillL()//ЗАПОЛНЕНИЕ ЕДИНИЦАМИ ЛЕВОЙ ЧАСТИ ЭКРАНА
 {
komandaR(0x3F);
	komandaL(0x3F);
  for(unsigned char i=0; i<8; i++)//X
  {
  set_xL(i);
   for(unsigned char j=0; j<64; j++)//Y
    {
     set_yL(j);
     dataL(0xFF);
    }

 
	}
 }
 
 
void lcd_clearL()//НУЛИ В ЛЕВУЮ ЧАСТЬ ЭКРАНА (НЕКОРРЕКТНАЯ РАБОТА ПРИ ПРЕРЫВАНИИ)
 {
komandaR(0x3F);
	komandaL(0x3F);
  for(unsigned char i=0; i<8; i++)//X
  {
  set_xL(i);
   for(unsigned char j=0; j<64; j++)//Y
    {
     set_yL(j);
     dataL(0x00);
    }

 
	}
 }
 void lcd_fillR()
 {
komandaR(0x3F);
	komandaL(0x3F);
  for(unsigned char i=0; i<8; i++)//X
  {
  set_xR(i);
   for(unsigned char j=0; j<64; j++)//Y
    {
     set_yR(j);
     dataR(0xFF);
    }

 
	}
 }
void lcd_clearR()
 {
komandaR(0x3F);
	komandaL(0x3F);
  for(unsigned char i=0; i<8; i++)//X
  {
  set_xR(i);
   for(unsigned char j=0; j<64; j++)//Y
    {
     set_yR(j);
     dataR(0x00);
    }

 
	}
 }
 
unsigned char getch_Uart(USART_TypeDef* USARTx)
{
	while(USART_GetFlagStatus(USARTx,USART_FLAG_RXNE) == RESET){}
	return USART_ReceiveData(USARTx);
}
unsigned char geth_spi(SPI_TypeDef* SPIx)
{
	while (SPI_I2S_GetFlagStatus( SPIx, SPI_I2S_FLAG_RXNE) == RESET){}
	return SPI_I2S_ReceiveData(SPIx);
}
void send_Uart(USART_TypeDef* USARTx, unsigned char c)
{
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)== RESET){}
		USART_SendData(USARTx, c);
}
void read_str_uart(USART_TypeDef* USARTx,unsigned char* s)
{		
	
	unsigned char tempa=0;
	unsigned int indexb=0;
	unsigned char indexa=0;
	
	
	for(indexa=0;indexa<5;indexa++)
{
	
		tempa=getch_Uart(USARTx);// на этом этапе символ
	
//		if(tempa!=1)//НЕ ПОНЯТНО,ЗАЧЕМ ВООБЩЕ НУЖНО
//		{
			*s++=tempa;//увеличивает адрес и берет след байт

//		}
//	else
//	{
//		 send_Uart(USART1, indexa);
//	
//	}
			
	}

	
	}

 void send_Uart_str(USART_TypeDef* USARTx, unsigned char *s)
{
  while (*s != 0) 
    send_Uart(USARTx, *s++);
}
  void USART1_IRQHandler(void)
{
		
	if (USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{

			set_xL(0);
   set_yL(0);
//		USART_SendData(USART1,0xFF);
		delay(0xFF);delay(0xFF);
	read_str_uart(USART1, Buffer);
		delay(0xFF);delay(0xFF);
//			USART_SendData(USART1,0xFF);
		delay(0xFF);delay(0xFF);
	 dm=USART_ReceiveData(USART1);
		delay(0xFF);delay(0xFF);
//			USART_SendData(USART1,0xFF);
		delay(0xFF);delay(0xFF);
		Receive_buf[Receive_W]= USART_ReceiveData(USART1);
		delay(0xFF);delay(0xFF);
		Receive_W++;
		Receive_C++;
		send_Uart_str(USART1, Buffer);
				delay(0xFF);delay(0xFF);
			
		delay(0xFF);delay(0xFF);
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		
	}
	
}

 		
	void SysTick_Handler(void)   //ВООБЩЕ НЕ ПОНЯТНО,ЗАЧЕМ ТЫ НУЖЕН
{
if (delay_count>0)
	{
delay_count--;	
}
}

 void delay_ms(uint32_t delay_temp)
{
delay_count = delay_temp;
	while(delay_count){}
}
void init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
GPIO_InitTypeDef GPIO_dindin;
	GPIO_dindin.GPIO_Pin  = GPIO_Pin_All;
  GPIO_dindin.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_dindin.GPIO_Mode =  GPIO_Mode_Out_PP ;
GPIO_Init(GPIOC,&GPIO_dindin);
	NVIC_EnableIRQ(USART1_IRQn);
	GPIO_SetBits( GPIOC,  GPIO_Pin_9);
	delay(0x1E);
	GPIO_ResetBits( GPIOC,  GPIO_Pin_9);
	delay(0xFF);
	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);//MASKA PO PRIEMU
NVIC_EnableIRQ(SPI1_IRQn);
	 
 kristalli(12);
	
	
}
	void adc_init() 
{
GPIO_InitTypeDef    GPIO_InitStruct;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 | RCC_APB2ENR_AFIOEN, ENABLE);
  //????????????? ?????? PA9 - USART1_Tx
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9; //????????? ?????? PA9
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; //???????? ????? ????????????
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; //????? ?????????????? ???????, ????? Push-Pull
  GPIO_Init(GPIOA, &GPIO_InitStruct); //???????? ????????? ????????? ? ????????? GPIO?

  //????????????? ?????? PA10 - USART1_Rx
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10; //????????? ?????? PA10
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING; //Input floating
  GPIO_Init(GPIOA, &GPIO_InitStruct); //???????? ????????? ????????? ? ????????? GPIO?
USART_InitTypeDef    USART_InitStruct;
  //????????????? USART1
  USART_InitStruct.USART_BaudRate = 9600; //???????? ?????? 9600 ???
  USART_InitStruct.USART_WordLength = USART_WordLength_8b; //????? ????? 8 ???
  USART_InitStruct.USART_StopBits = USART_StopBits_1; //1 ????-???
  USART_InitStruct.USART_Parity = USART_Parity_No ; //??? ???????? ????????
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //??? ??????????? ????????
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //??????? ?????????? ? ???????? USART1
  USART_Init(USART1, &USART_InitStruct); //???????? ????????? ????????? ? ????????? USART1
	USART1->CR1 |= USART_CR1_TE; 
	USART1->CR1 |= USART_CR1_RE; 
	USART1->CR1 |= USART_CR1_RXNEIE;
NVIC_EnableIRQ(USART1_IRQn);
USART_Cmd(USART1,ENABLE);
}



void vivod(unsigned char sector,unsigned char  pos_x,unsigned char  pos_y, unsigned char *abc)
 {
 
	 
	 
  switch(sector)
  {
   case 1: 
	 {
		set_xL(pos_x);
   set_yL(pos_y);
		GLCD_WriteStringL(abc);
   break;
  }		
   case 2:  // В РАЗРАБОТКЕ
		{
		set_xR(pos_x);
   set_yR(pos_y);
			GLCD_WriteStringR(abc);
   break;
  }
 }
}
 void read_spi(SPI_TypeDef* SPIx,unsigned char* m)
{		
	
	unsigned char tempa=0;
	unsigned int indexb=0;
	unsigned char indexa=0;
	
	
	for(indexa=0;indexa<5;indexa++)
{
	while(*m++!=0)
	{
		tempa=geth_spi(SPIx);// на этом этапе символ
	
		if(tempa!=1)//типа сколько данных обработает прежде чем отправить обратно
		{
			*m++=tempa;//увеличивает адрес и берет след байт

		}
	
			
	}

	}
	}
void SPI1_IRQHandler()//ПРЕРЫВАНИЕ ПО SPI(НАДО ЕЩЕ ДОБАВИТЬ ОПРОСНЫЙ СИГНАЛ И СТРОКУ ОШИБКИ.ТАК ЖЕ НУЖНА ОБРАБОТКА КАЖДОГО БАЙТА)
{
	 if(SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE)==SET)
	
	
	read_spi(SPI1,SPIBuffer);
		

	
	
	
	
	
    //ЗДЕСЬ БУДЕТ НЕВЕДОМАЯ ФИГНЯ
	 SPI_I2S_ClearITPendingBit(SPI1, SPI_I2S_IT_RXNE);
}
int main(void)
{
	init_spi();

init();
	SysTick_Config(SystemCoreClock/2);
	adc_init();
	lcd_fillL();
delay(0xFF);
		lcd_clearL();
	delay(0xFF);
	lcd_fillR();
	delay(0xFF);
		lcd_clearR();
	delay(0xFF);
	set_xL(0);
   set_yL(0);
				 delay(0xFF);
	while(1)
		 {	 
		set_xL(0);
			 set_yL(0);
			 		set_xR(0);
			 set_yR(0);
			 for(int l=0;l<4;l++)
			 {
				switch(l)
				{
					case 1:
				{

			 vivod(1,0,0, "1");
			 vivod(1,1,0, "2");
			 vivod(1,2,0, "3");
			 vivod(1,3,0, "4");
			 vivod(1,4,0, "5");
			 vivod(1,5,0, "6");
			 vivod(1,6,0, "7");
			 vivod(1,7,0, "8");
						vivod(2,0,0, "-1");
						vivod(2,1,0, "-2");
						vivod(2,2,0, "-3");
						vivod(2,3,0, "-4");
						vivod(2,4,0, "-5");
						vivod(2,5,0, "-6");
						vivod(2,6,0, "-7");
						vivod(2,7,0, "-8");
					break;
			 }			
				case 2:
				{
 	delay_ms(5);
					vivod(1,0,0,"9");
			 vivod(1,1,0, "10");
			 vivod(1,2,0, "11");
			 vivod(1,3,0, "12");
			 vivod(1,4,0, "13");
			 vivod(1,5,0, "14");
			 vivod(1,6,0, "15");
			 vivod(1,7,0, "16");
						vivod(2,0,0, "-9");
						vivod(2,1,0, "-10");
						vivod(2,2,0, "-11");
						vivod(2,3,0, "-12");
						vivod(2,4,0, "-13");
						vivod(2,5,0, "-14");
						vivod(2,6,0, "-15");
						vivod(2,7,0, "-16");
				break;
				}
					case 3:
				{
 	delay_ms(5);
					vivod(1,0,0,"17");
			 vivod(1,1,0, "18");
			 vivod(1,2,0, "19");
			 vivod(1,3,0, "20");
			 vivod(1,4,0, "21");
			 vivod(1,5,0, "22");
			 vivod(1,6,0, "23");
			 vivod(1,7,0, "24");
						vivod(2,0,0, "-17");
						vivod(2,1,0, "-18");
						vivod(2,2,0, "-19");
						vivod(2,3,0, "-20");
						vivod(2,4,0, "-21");
						vivod(2,5,0, "-22");
						vivod(2,6,0, "-23");
						vivod(2,7,0, "-24");
				break;
				}
				
		 }
	 }
			 delay_ms(5);
			 
//  GPIO_SetBits( GPIOC,  GPIO_Pin_9);
//	delay(10000000);
//	GPIO_ResetBits( GPIOC,  GPIO_Pin_9);
			 
			 
			 
			 
			 		set_xL(0);
			 set_yL(0);
	 set_xR(0);
			 set_yR(0);
//	 GLCD_WriteStringL( "+--------+");
//			 delay_ms(5);
//	GLCD_WriteStringR("+--------+");
//			  delay_ms(5); 
	lcd_clearL();
	 	lcd_clearR();

//			 unsigned char m=Buffer[0];
//			 send_Uart(USART1, m);

}

}








