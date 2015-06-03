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
 * @file   discovery_f4.cpp
 * @author ala42
 * @brief  discovery_f4 board file.
 */

/*
 	STM32F401 monkey port June 2016 by sheepdoll (Julie S. Porter)
 	
 */

#ifdef BOARD_nucleo_f401

#include "board/board.h"

// sheepdoll -- prepare for later merging
//#include <libmaple/gpio.h>
#include "gpio.h"

#include "rcc.h"

//#include <libmaple/timer.h>
#include "timer.h"

/* Roger Clark. Added next to includes for changes to Serial 
#include <libmaple/usart.h>
#include <HardwareSerial.h>


#include <wirish_debug.h>
#include <wirish_types.h>
*/

#include "wirish_types.h"

/* 
	Sheepdoll --
	
	stm32F1 macros that set AFIO_MAPR do not work for F2 or F4 devices
	
	This code extensively modified for Nucleo
	
*/
void boardInit(void) {
	// remap TIMER8 to PC6-9
	gpio_set_af_mode(GPIOC, 6, 3);
	gpio_set_af_mode(GPIOC, 7, 3);
	gpio_set_af_mode(GPIOC, 8, 3);
	gpio_set_af_mode(GPIOC, 9, 3);

	// remap TIMER1 to PE9,11,13,14
	gpio_set_af_mode(GPIOE,  9, 1);
	gpio_set_af_mode(GPIOE, 11, 1);
	gpio_set_af_mode(GPIOE, 13, 1);
	gpio_set_af_mode(GPIOE, 14, 1);

	// remap TIMER3 to PB4,5,0,1
	gpio_set_af_mode(GPIOB,  4, 2);
	gpio_set_af_mode(GPIOB,  5, 2);
	gpio_set_af_mode(GPIOB,  0, 2);
	gpio_set_af_mode(GPIOB,  1, 2);


	//gpio_set_af_mode(GPIOA, 2, 7);
	//gpio_set_af_mode(GPIOA, 3, 7);
	return;
}


// Pin map: this lets the basic I/O functions (digitalWrite(),
// analogRead(), pwmWrite()) translate from pin numbers to STM32
// peripherals.
//
// PMAP_ROW() lets us specify a row (really a struct stm32_pin_info)
// in the pin map. Its arguments are:
//
// - GPIO device for the pin (GPIOA, etc.)
// - GPIO bit for the pin (0 through 15)
// - Timer device, or NULL if none
// - Timer channel (1 to 4, for PWM), or 0 if none
// - ADC device, or NULL if none
// - ADC channel, or ADCx if none
// gpioX, PINbit, TIMER/NULL, timerch/0, ADC1/NULL, adcsub/0
// gpioX, TIMER/NULL, ADC1/NULL, PINbit, timerch/0, adcsub/0
//       0    1    2      3    4     5
//       0    3    1      4    2     5

//       0    1    3      4    2     5
//       0    1    2      4    2     5

extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {

    /* Arduino-like header, right connectors */
    {GPIOA, NULL,   ADC1,   3,  0,    3}, /*  D0/PA3	USART_RX	*/
    {GPIOA, NULL,   ADC1,   2,  0,    2}, /*  D1/PA2	USART_TX	*/
    {GPIOA, TIMER1, NULL,  10,  3, ADCx}, /*  D2/PA10	USART1_RX	*/
    {GPIOB, TIMER2, NULL,   3,  2, ADCx}, /*  D3/PB3	SWO			*/
    {GPIOB, TIMER3, NULL,   5,  2, ADCx}, /*  D4/PB5	GPIO T3		*/
    {GPIOB, TIMER3, NULL,   4,  1, ADCx}, /*  D5/PB4  	GPIO T3		*/
    {GPIOB, TIMER2, NULL,  10,  3, ADCx}, /*  D6/PB10	I2C2_SCL	*/
    {GPIOA, TIMER1, NULL,   8,  1, ADCx}, /*  D7/PA8	GPIO T1		*/
                   
    {GPIOA, TIMER1, NULL,   9,  2, ADCx}, /*  D8/PA9	USART1_TX	*/
    {GPIOC, NULL,   NULL,   7,  0, ADCx}, /*  D9/PC7	GPIO		*/
    {GPIOB, TIMER4, NULL,   6,  1, ADCx}, /*  D10/PB6	I2C1_SCL	*/
    {GPIOA, NULL,   ADC1,   7,  0,    7}, /*  D11/PA7	SPI_MOSI_NC	*/
    {GPIOA, NULL,   ADC1,   6,  0, 	  6}, /*  D12/PA6	SPI_MISO_NC */
    {GPIOA, NULL,   NULL,   5,  0, ADCx}, /*  D13/PA5 	LED - no ADC12_IN5 SPI_SCK !*/
    {GPIOB, TIMER4, NULL,   9,  4, ADCx}, /*  D14/PB9 	I2C1_SDA	*/
    {GPIOB, TIMER4, NULL,   8,  3, ADCx}, /*  D15/PB8 	I2C1_SCL	*/
                   
    {GPIOA, NULL,   ADC1,   0,  0,    0}, /*  D16/A0/PA0 GPIO		*/
    {GPIOA, NULL,   ADC1,   1,  0,    1}, /*  D17/A1/PA1 GPIO		*/
    {GPIOA, NULL,   ADC1,   4,  0,    4}, /*  D18/A2/PA4 SPI_NSS	*/
    {GPIOB, TIMER3, ADC1,   0,  3,    8}, /*  D19/A3/PB0 GPIO		*/
    {GPIOC, NULL,   ADC1,   1,  0,   11}, /*  D20/A4/PC1 GPIO		*/
    {GPIOC, NULL,   ADC1,   0,  0,   10}, /*  D21/A5/PC0 GPIO		*/
                   
    /*
    	 these signals are only on the Morpho headers
    	 Odd pins are on the left header
    	 Even pins are on the right header                 
    */
    
    {GPIOC, NULL,   NULL,  10,  0, ADCx}, /*  D22/PC10 	SPI_SCK			ML1 */
	{GPIOC, NULL,   NULL,  12,  0, ADCx}, /*  D23/PC12	SPI_MOSI		ML3 */
    {GPIOB, TIMER4, NULL,   7,  2, ADCx}, /*  D24/PB7	I2C1_SDA		M21 */
    {GPIOC, NULL,   NULL,  13,  0, ADCx}, /*  D25/PC13 USER BLUE BUTTON M23 */
    {GPIOC, NULL,   NULL,  14,  0, ADCx}, /*  D26/PC14 RCC_OSC32_IN 	M25 */
    {GPIOC, NULL,   NULL,  15,  0, ADCx}, /*  D27/PC15 RCC_OSC32_OUT	M26 */
    {GPIOC, NULL,   ADC1,   2,  0,   12}, /*  D28/PC2	SPI2_MISO		M35 */
    {GPIOC, NULL,   ADC1,   3,  0,   13}, /*  D29/PC3	GPIO			M37 */
    {GPIOC, NULL,   NULL,  11,  0, ADCx}, /*  D30/PC11	SPI3_MISO		ML2 */
    {GPIOD, NULL,   NULL,   2,  0, ADCx}, /*  D31/PD2 	GPIO			ML4 */
    {GPIOC, NULL,   NULL,   9,  0, ADCx}, /*  D32/PC9	GPIO			MR1 */
    {GPIOC, NULL,   NULL,   8,  0, ADCx}, /*  D33/PC8	GPIO			MR2 */
    {GPIOC, NULL,   NULL,   6,  0, ADCx}, /*  D34/PC6	GPIO			MR4 */
    {GPIOC, NULL,   ADC1,   5,  0,   15}, /*  D35/PC5	GPIO			MR6 */
    {GPIOA, NULL,   NULL,  12,  0, ADCx}, /*  D36/PA12 USART6_RX USB_DP M12*/
    {GPIOA, TIMER1, NULL,  11,  4, ADCx}, /*  D37/PA11 USART6_TX USB_DM M14 */
    {GPIOB, NULL,   NULL,  12,  0, ADCx}, /*  D38/PB12	SPI2_NSS		M16 */
    {GPIOB, TIMER2, NULL,  11,  4, ADCx}, /*  D39/PB11	I2C2_SDA		M18 PWM-not working?*/
    {GPIOB, NULL,   NULL,  2,   0, ADCx}, /*  D40/PB2	BOOT1 !!		ML7 */
    {GPIOB, TIMER3, ADC1,   1,  4,    9}, /*  D41/PB1	GPIO 			M24 */
    {GPIOB, NULL,   NULL,  15,  0, ADCx}, /*  D42/PB15	SPI2_MOSI		M26 */
    {GPIOB, NULL,   NULL,  14,  0, ADCx}, /*  D43/PB14	SPI2_MISO		M28 */
    {GPIOB, NULL,   NULL,  13,  0, ADCx}, /*  D44/PB13	SPI2_SCK		M30 */
    {GPIOC, NULL,   ADC1,   4,  0,   14}  /*  D45/PC4	GPIO			M34 */
  
  	// JTAG Single wire pins
	// {GPIOA, NULL,   NULL, 13, 0, ADCx},/* D41/PA13 	TMS	do not use	M13 */
	// {GPIOA, NULL,   NULL, 14, 0, ADCx},/* D42/PA14	TCK do not use	M15 */

// sheepdoll -- not sure why this one is locked out?
	// {GPIOA, TIMER2, NULL, 15, 1, ADCx},/* D43/PA15 	TDI do not use	M17 */
};

// sheepdoll -- from F103 Nucleo
// Array of pins you can use for pwmWrite(). Keep it in Flash because
// it doesn't change, and so we don't waste RAM.
extern const uint8 boardPWMPins[] __FLASH__ = {
    2,3,5,6,7,8,10,14,15,19,24,37,39,41
};

// Array of pins you can use for analogRead().
extern const uint8 boardADCPins[] __FLASH__ = {
    0,1,11,12,16,17,18,19,20,21,28,29,35,41,45
};

// sheepdoll this is left over from the F107

extern const uint8 boardUsedPins[BOARD_NR_USED_PINS] __FLASH__ = {
    BOARD_LED_PIN, BOARD_BUTTON_PIN, BOARD_JTMS_SWDIO_PIN,
    BOARD_JTCK_SWCLK_PIN, BOARD_JTDI_PIN, BOARD_JTDO_PIN, BOARD_NJTRST_PIN
};

/*
static void initSRAMChip(void) {
    fsmc_nor_psram_reg_map *regs = FSMC_NOR_PSRAM1_BASE;

    fsmc_sram_init_gpios();
    rcc_clk_enable(RCC_FSMC);

    regs->BCR = (FSMC_BCR_WREN | FSMC_BCR_MWID_16BITS | FSMC_BCR_MTYP_SRAM |
                 FSMC_BCR_MBKEN);
    fsmc_nor_psram_set_addset(regs, 0);
    fsmc_nor_psram_set_datast(regs, 3);
}
*/

/* 
 * Roger Clark
 * 
 * 2015/05/28
 *
 * Moved definitions for Hardware Serial devices from HardwareSerial.cpp so that each board can define which Arduino "Serial" instance
 * Maps to which hardware serial port on the microprocessor
 */
						
#ifdef SERIAL_USB
   DEFINE_HWSERIAL(Serial1, 1);
   DEFINE_HWSERIAL(Serial2, 2);
   DEFINE_HWSERIAL(Serial3, 3);
#else
   DEFINE_HWSERIAL(Serial, 6);// Use HW Serial 6 as "Serial"
   DEFINE_HWSERIAL(Serial1, 2);
   DEFINE_HWSERIAL(Serial2, 1);
#endif

#endif
