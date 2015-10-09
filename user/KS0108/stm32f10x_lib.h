

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_LIB_H
#define __STM32F10x_LIB_H

/* Includes ------------------------------------------------------------------*/


#ifdef _ADC
  #include "stm32f10x_adc.h"
#endif /*_ADC */

#ifdef _BKP
  #include "stm32f10x_bkp.h"
#endif /*_BKP */

#ifdef _CAN
  #include "stm32f10x_can.h"
#endif /*_CAN */

#ifdef _DMA
  #include "stm32f10x_dma.h"
#endif /*_DMA */

#ifdef _EXTI
  #include "stm32f10x_exti.h"
#endif /*_EXTI */

#ifdef _FLASH
  #include "stm32f10x_flash.h"
#endif /*_FLASH */

#ifdef _GPIO
  #include "stm32f10x_gpio.h"
#endif /*_GPIO */

#ifdef _I2C
  #include "stm32f10x_i2c.h"
#endif /*_I2C */

#ifdef _IWDG
  #include "stm32f10x_iwdg.h"
#endif /*_IWDG */

#ifdef _NVIC
  #include "stm32f10x_nvic.h"
#endif /*_NVIC */

#ifdef _PWR
  #include "stm32f10x_pwr.h"
#endif /*_PWR */

#ifdef _RCC
  #include "stm32f10x_rcc.h"
#endif /*_RCC */

#ifdef _RTC
  #include "stm32f10x_rtc.h"
#endif /*_RTC */

#ifdef _SPI
  #include "stm32f10x_spi.h"
#endif /*_SPI */

#ifdef _SysTick
  #include "stm32f10x_systick.h"
#endif /*_SysTick */

#ifdef _TIM1
  #include "stm32f10x_tim1.h"
#endif /*_TIM1 */

#ifdef _TIM
  #include "stm32f10x_tim.h"
#endif /*_TIM */

#ifdef _USART
  #include "stm32f10x_usart.h"
#endif /*_USART */

#ifdef _WWDG
  #include "stm32f10x_wwdg.h"
#endif /*_WWDG */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void debug(void);

#endif /* __STM32F10x_LIB_H */

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/