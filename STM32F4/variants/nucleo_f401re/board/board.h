/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file   aeroquad32.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Private include file for Maple Native in boards.h
 *
 * See maple.h for more information on these definitions.
 */
 
 /*
 	STM32F401 monkey port June 2016 by sheepdoll (Julie S. Porter)
 	
 */

#ifndef _BOARD_NUCLEO_F401_H_
#define _BOARD_NUCLEO_F401_H_

// sheepdoll -- the following macros look to map the same thing
#define Port2Pin(port, bit) ((port-'A')*16+bit)

enum {
PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
PD1,PD2
};


// setup some clock timer macros

#define CYCLES_PER_MICROSECOND  168


#undef  STM32_PCLK1
#undef  STM32_PCLK2
#define STM32_PCLK1   (CYCLES_PER_MICROSECOND*1000000/4)
#define STM32_PCLK2   (CYCLES_PER_MICROSECOND*1000000/2)

#define SYSTICK_RELOAD_VAL      (CYCLES_PER_MICROSECOND*1000-1)

// setup Hardware User indicators

#define BOARD_LED_PIN           Port2Pin('A', 5)
#define BOARD_BUTTON_PIN        Port2Pin('C', 13)

// define some shortcuts to the Serial devices

#define BOARD_NR_USARTS         3
#define BOARD_USART1_TX_PIN     Port2Pin('A', 9)
#define BOARD_USART1_RX_PIN     Port2Pin('A',10)
#define BOARD_USART2_TX_PIN     Port2Pin('A', 2)
#define BOARD_USART2_RX_PIN     Port2Pin('A', 3) 

// sheepdoll -- USART 6 mapped to same pins as USB
// on morpho header
// alternates are PC7,PC6 [D9,D34]
// this will need a switch to use USB-OTG
#define BOARD_USART6_TX_PIN     Port2Pin('A', 11)
#define BOARD_USART6_RX_PIN     Port2Pin('A', 12)

// sheepdoll -- SPI1 is not available for general use when the
// [D13] Led is on A5  
// this is the best fit Arduino 
#define BOARD_NR_SPI            3
#define BOARD_SPI1_NSS_PIN      Port2Pin('A', 4)
#define BOARD_SPI1_MOSI_PIN     Port2Pin('A', 7)
#define BOARD_SPI1_MISO_PIN     Port2Pin('A', 6)
#define BOARD_SPI1_SCK_PIN      Port2Pin('A', 5)

// SPI2 has two mappings
// Best fit Nucleo
#define BOARD_SPI2_NSS_PIN      Port2Pin('B',12)
#define BOARD_SPI2_MOSI_PIN     Port2Pin('B',15)
#define BOARD_SPI2_MISO_PIN     Port2Pin('B',14)
#define BOARD_SPI2_SCK_PIN      Port2Pin('B',13)

#define BOARD_SPI2B_NSS_PIN      Port2Pin('B',9)
#define BOARD_SPI2B_MOSI_PIN     Port2Pin('C',3)
#define BOARD_SPI2B_MISO_PIN     Port2Pin('C',2)
#define BOARD_SPI2B_SCK_PIN      Port2Pin('B',10)


// SPI3 has two mappings 
// note the conflict with NSS on SPI1
// this also conflicts with SWO
#define BOARD_SPI3_NSS_PIN      Port2Pin('A',4)
#define BOARD_SPI3_MOSI_PIN     Port2Pin('B', 5)
#define BOARD_SPI3_MISO_PIN     Port2Pin('B', 4)
#define BOARD_SPI3_SCK_PIN      Port2Pin('B', 3)

// Best fit Morpho header
#define BOARD_SPI3B_NSS_PIN      Port2Pin('A', 15)
#define BOARD_SPI3B_MOSI_PIN     Port2Pin('C',12)
#define BOARD_SPI3B_MISO_PIN     Port2Pin('C',11)
#define BOARD_SPI3B_SCK_PIN      Port2Pin('C',10)

// these values are approximations
#define BOARD_NR_GPIO_PINS      51
#define BOARD_NR_PWM_PINS       14
#define BOARD_NR_ADC_PINS       15
#define BOARD_NR_USED_PINS      43 


// JTAG serial wire defines

#define BOARD_JTMS_SWDIO_PIN    Port2Pin('A',13)
#define BOARD_JTCK_SWCLK_PIN    Port2Pin('A',14)
#define BOARD_JTDI_PIN          Port2Pin('A',15)
#define BOARD_JTDO_PIN          Port2Pin('B', 3)
#define BOARD_NJTRST_PIN        Port2Pin('B', 4)



/* 
	sheepdoll -- define modes for Alternate functions

	these are based on STM HAL generated data with descriptive names to make
	the setup code easier to read
*/

#define MODE_AF0_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping                       */
#define MODE_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define MODE_AF0_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define MODE_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define MODE_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */

#define MODE_AF1_TIM1          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define MODE_AF1_TIM2          ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */

#define MODE_AF2_TIM3          ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define MODE_AF2_TIM4          ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define MODE_AF2_TIM5          ((uint8_t)0x02)  /* TIM5 Alternate Function mapping */

#define MODE_AF3_TIM9          ((uint8_t)0x03)  /* TIM9 Alternate Function mapping  */
#define MODE_AF3_TIM10         ((uint8_t)0x03)  /* TIM10 Alternate Function mapping */
#define MODE_AF3_TIM11         ((uint8_t)0x03)  /* TIM11 Alternate Function mapping */

#define MODE_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define MODE_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */
#define MODE_AF4_I2C3          ((uint8_t)0x04)  /* I2C3 Alternate Function mapping */

#define MODE_AF5_SPI1          ((uint8_t)0x05)  /* SPI1 Alternate Function mapping        */
#define MODE_AF5_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping   */
#define MODE_AF5_SPI4          ((uint8_t)0x05)  /* SPI4 Alternate Function mapping        */
#define MODE_AF5_I2S3ext      ((uint8_t)0x05)  /* I2S3ext_SD Alternate Function mapping  */

#define MODE_AF6_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping  */
#define MODE_AF6_I2S2ext      ((uint8_t)0x06)  /* I2S2ext_SD Alternate Function mapping */

#define MODE_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping     */
#define MODE_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping     */
#define MODE_AF7_I2S3ext       ((uint8_t)0x07)  /* I2S3ext_SD Alternate Function mapping */

#define MODE_AF8_USART6        ((uint8_t)0x08)  /* USART6 Alternate Function mapping */

#define MODE_AF9_TIM14         ((uint8_t)0x09)  /* TIM14 Alternate Function mapping */
#define MODE_AF9_I2C2          ((uint8_t)0x09)  /* I2C2 Alternate Function mapping  */
#define MODE_AF9_I2C3          ((uint8_t)0x09)  /* I2C3 Alternate Function mapping  */

#define MODE_AF10_OTG_FS        ((uint8_t)0xA)  /* OTG_FS Alternate Function mapping */

#define MODE_AF12_SDIO          ((uint8_t)0xC)  /* SDIO Alternate Function mapping  */

#define MODE_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */


#endif
