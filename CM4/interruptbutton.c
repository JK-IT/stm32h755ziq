/*
 * interruptbutton.c
 *
 *  Created on: Sep 9, 2020
 *      Author: jkgra
 */

#include "string.h"
#include "stm32h755xx.h"

void Delay(void)
{
	for(uint32_t i = 0;  i < 500000/2; i++);
}


void main(void)
{
	//enable led on board
	//led3		PB14
	Gpio_Handle_t led3;
	memset(&led3, 0, sizeof(led3));
	led3.pGpiox = GPIOB;
	led3.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_14;
	led3.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_OUT;
	led3.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
	led3.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_NO_PUPD;
	led3.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_LOW;

	//configure the button to generate interrupt
	//using button1  PC13
	Gpio_Handle_t butt1;
	memset(&butt1, 0, sizeof(butt1));
	butt1.pGpiox = GPIOD;
	butt1.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_15;
	butt1.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_IT_FT;
	butt1.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PU;
	butt1.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_MED;

	//enable peri clock and init
	Gpio_PeriClkControl(GPIOB, ENABLE);
	Gpio_PeriClkControl(GPIOD, ENABLE);

	Gpio_Init(&led3);
	Gpio_Init(&butt1);

	// Interrupt configuration
	Gpio_SetIpr(IRQ_NO_EXTI15_10, 15);
	Gpio_IrqConfig(IRQ_NO_EXTI15_10, ENABLE);

	while(1);
}

void EXTI15_10_IRQHandler(void)
{
	Delay();
	Gpio_IrqHandling(GPIO_PIN_NO_15);
	Gpio_TogglePin(GPIOB, GPIO_PIN_NO_14);
}

