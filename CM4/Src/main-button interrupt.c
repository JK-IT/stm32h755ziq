/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stm32h755xx.h>
#include <stdio.h>
#include <string.h>


void Delay()
{
	for(uint32_t i = 0; i < 300000; i++);
}

void DelayTime(uint32_t intime)
{
	for(uint32_t i = 0; i < intime; i++);
}

void Led1_init()
{
	Gpio_Handle_t pb0Led;
	pb0Led.pGpiox = GPIOB;
	pb0Led.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_0;
	pb0Led.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_OUT;
	pb0Led.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
	pb0Led.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PU;
	pb0Led.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_HIGH;
	Gpio_Init(&pb0Led);
}

void Led2_init()
{
	Gpio_Handle_t pe1;
	pe1.pGpiox = GPIOE;
	pe1.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_1;
	pe1.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_OUT;
	pe1.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
	pe1.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PU;
	pe1.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_HIGH;
	Gpio_Init(&pe1);
}

void Led3_init()
{
	Gpio_Handle_t pb14;
	pb14.pGpiox = GPIOB;
	pb14.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_OUT;
	pb14.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_14;
	pb14.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PU;
	pb14.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
	pb14.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_HIGH;
	Gpio_Init(&pb14);
}

void Led4_init() // pe12
{
	Gpio_Handle_t pe12;
	pe12.pGpiox = GPIOE;
	pe12.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_OUT;
	pe12.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_12;
	pe12.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
	pe12.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_HIGH;
	pe12.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PD;
	Gpio_Init(&pe12);
}

void mbutt1_init() //e14
{
	Gpio_Handle_t butt;
	butt.pGpiox = GPIOE;
	butt.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_14;
	butt.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_IN;
	butt.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PD;
	Gpio_Init(&butt);
}

void mbutt1_risingedge()
{
	Gpio_Handle_t butt;
	butt.pGpiox = GPIOE;
	butt.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_IN;
	butt.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_14;
	butt.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PD;
	Gpio_Init(&butt);

	//enable sysconf
	Syscfg_init();
	// set pin as iterrupt source
	Syscfg_port_t pe = PE;
	Syscfg_exti_source(pe, 0xe);
	//enable exti interrupt mask
	Exti_trigger_edge_t edge = RisingEdge;
	Set_C2IM_ioexti(0xe, edge);

}


uint8_t butpressed = 0;
uint8_t dummy = 0x6b; //K
uint8_t led_state = OFF;

int main(void)
{
	Rcc_Init();

	Led1_init();//b0
	Led2_init();//e1
	Led3_init();//b14 with spi2 this is miso
	Led4_init();
	mbutt1_risingedge();// <== interruption

	for(;;)
	{
		while(!butpressed){
			Gpio_WriteToOutputPin(GPIOE, 12, OFF);
		}
		Gpio_WriteToOutputPin(GPIOE, 12, ON);
		butpressed = 0;
	}
	return 0;
}


void Gpio_irq_handling(uint8_t pin)
{

	//clear pending in exti, so interrupt will be reset
	EXTI->C2PR1 |= (1 << pin);
	/*
	if(led_state == OFF)
	{
		Gpio_TogglePin(GPIOE, GPIO_PIN_NO_12);
		led_state = ON;
	} else {
		Gpio_TogglePin(GPIOE, GPIO_PIN_NO_12);
		led_state = OFF;
	}*/

}

void EXTI15_10_IRQHandler()
{
	Delay();
	// TO AVOID BOUNDING BUTTON CUZ OF CHEAP HARDWARD
	// USE A FLAG INSTEAD
	if(butpressed){ // bouncing button , the program will jump here even it not finish sending spi
			//set this will ignore the until the butpressed is reset to 0
		Gpio_irq_handling(0xe);
		return;
	}
	butpressed = 1;// <=== the flag
	Gpio_irq_handling(0xe);
}