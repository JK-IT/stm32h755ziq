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
	for(uint32_t i = 0; i < 250000; i++);
}

void Led13_init()
{
	Gpio_Handle_t pb13Led;
	pb13Led.pGpiox = GPIOB;
	pb13Led.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_13;
	pb13Led.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_OUT;
	pb13Led.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
	pb13Led.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PU;
	pb13Led.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_FAST;
	Gpio_Init(&pb13Led);
}

void Led15_init()
{
	Gpio_Handle_t pb15Led;
	pb15Led.pGpiox = GPIOB;
	pb15Led.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_15;
	pb15Led.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_OUT;
	pb15Led.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
	pb15Led.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PD;
	pb15Led.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_FAST;
	Gpio_Init(&pb15Led);
}

void Led14_init()
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

void Butt11_init()
{
	Gpio_Handle_t pd11;
	pd11.pGpiox = GPIOD;
	pd11.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_11;
	pd11.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_IN;
	pd11.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
	pd11.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PD;
	pd11.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_FAST;
	Gpio_Init(&pd11);
}

void Spi1_init()
{
	//enable gpio pin
	Gpio_Handle_t pa;
	pa.pGpiox = GPIOA;
	pa.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_ALTFN;
	pa.Gpio_PinConfig.Gpio_PinAltFunMode = 5;
	pa.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
	pa.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PU;
	pa.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_FAST;

	pa.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_4;
	Gpio_Init(&pa);

	pa.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_5;
	Gpio_Init(&pa);

	pa.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_6;
	Gpio_Init(&pa);

	pa.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_7;
	Gpio_Init(&pa);

	//config spi
	Spi_Handle_t spi1;
	spi1.pSpix = SPI1;
	spi1.SpiConfig.Spi_BusConfig = SPI_BUS_CONFIG_FD;
	spi1.SpiConfig.Spi_CPha = SPI_CPHA_LOW;
	spi1.SpiConfig.Spi_Cpol = SPI_CPOL_LOW;
	spi1.SpiConfig.Spi_DSize = SPI_DSIZE_XBITS(8);
	spi1.SpiConfig.Spi_DeviceMode = SPI_DEVICE_MODE_MASTER;
	spi1.SpiConfig.Spi_SclkSpeed = SPI_SCLK_SPEED_DIV16;
	spi1.SpiConfig.Spi_SsPol = SPI_SSPOL_LOW;
	spi1.SpiConfig.Spi_Ssm = SPI_SSM_DI;

	Spi_Cfig(&spi1, ENABLE);

}

int main(void)
{
	Rcc_Init();
	Led14_init();
	Butt11_init();
	Spi1_init();
	RccSpi1_ClkSw(spi1per_clk);
	//RccSpi1_ClkSw(spi1pll2p_clk);
	char buff[] = "so u are working now?";
	char m1[] = "lets talk";

    /* Loop forever */
	for(;;)
	{
		while( ! Gpio_ReadFromInputPin(GPIOD, GPIO_PIN_NO_11))
		{

			Gpio_TogglePin(GPIOB, GPIO_PIN_NO_14);
			Delay();
		}
		Delay();
		uint8_t datlen = strlen(buff);
		Spi_SendData(SPI1, & datlen , 1);
		Spi_SendData(SPI1, (uint8_t*)buff , strlen(buff));
		//Spi_SendData(SPI1, m1, strlen(m1));

	};

	return 0;
}
