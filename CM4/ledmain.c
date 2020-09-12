/*
 * ledmain.c
 *
 *  Created on: Aug 31, 2020
 *      Author: jkgra
 */
#include "stm32h755xx.h"

#define RCC_BASE	0x58024400UL
#define	AHB4_EN	0x0e0UL
#define AHB4_REG	(RCC_BASE + AHB4_EN)

void Delay(void){
	for(uint32_t i = 0; i < 500000; i ++);
}

int main(void){

	//uint32_t * ahb4bus = (uint32_t*)AHB4_REG;
	//* ((uint32_t*)AHB4_REG) |= (1<< 3);
	//*RCC_AHB4ENR |= (1 << 1);
	Gpio_PeriClkControl(GPIOA, ENABLE);
	Gpio_Handle_t gpioled3;
	Gpio_Handle_t gpioled2;

	gpioled3.pGpiox = GPIOA;
	gpioled3.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_5;
	gpioled3.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_OUT;
	gpioled3.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
	gpioled3.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_MED;
	gpioled3.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_NO_PUPD;


	Gpio_PeriClkControl(GPIOE, ENABLE);
	gpioled2.pGpiox = GPIOE;
	gpioled2.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_1;
	gpioled2.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_OUT;
	gpioled2.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_OP;
	gpioled2.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_MED;
	gpioled2.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PU;

	Gpio_Init(&gpioled3);
	Gpio_Init(&gpioled2);
	//GPIOB_REG_RST();
	while(1){
		Gpio_TogglePin(GPIOA, GPIO_PIN_NO_5);
		Gpio_TogglePin(GPIOE, GPIO_PIN_NO_1);
		Delay();
	}

	return 0;
}
