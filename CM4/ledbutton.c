/*
 * ledbutton.c
 *
 *  Created on: Sep 5, 2020
 *      Author: jkgra
 */
#include "stm32h755xx.h"

void Delay()
{
	for(uint32_t i = 0; i < 5000; i ++);
}

void main()
{
	//RESET PORT
	GPIOB_REG_RST();
	GPIOC_REG_RST();

	// ENABLE PERIPHERAL
	GPIOB_PCLK_EN();
	GPIOC_PCLK_EN();

	//INIT LED -B0
	Gpio_Handle_t led1;
	led1.pGpiox = GPIOB;
	led1.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_0;
	led1.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_OUT;
	led1.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
	led1.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_FAST;
	led1.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_NO_PUPD;
	Gpio_Init(&led1);

	//INIT BUTTON -C13
		//BUTTON CLOSE - READ 1
	Gpio_Handle_t btn;
	btn.pGpiox = GPIOC;
	btn.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_13;
	btn.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_IN;
	btn.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_FAST;
	btn.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_NO_PUPD;
	Gpio_Init(&btn);

	while(1)
	{
		if( Gpio_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) == 1)
		{
			Delay();
			Gpio_TogglePin(GPIOB, GPIO_PIN_NO_0);

		}
	}

}
// Interrupt Handling
void EXTI15_10_IRQHandler(void)
{
	Gpio_IrqHandling(13);
}



