/*
 * arduino_spi.c
 *
 *  Created on: Oct 22, 2020
 *      Author: jkgra
 */


#include "stm32h755xx.h"
#include "string.h"

void Delay()
{
	for(uint32_t i = 0; i < 500000/2; i ++);
}


/*
 * stm32 board - using spi2 - alternative function 5
 * 	pb12 nss
 * pb13 sck
 * pb14 miso
 * pb15 mosi\
 */


// SPI 1 PORT A ALTFUN 5
// PA4	NSS
//PA5		SCK
// PA6	MISO
// PA7	MOSI
void Spi1_PA_Init()
{
	//enable clock source
	// default clock source: pll but pll is disabled by default
	//for easy set up use peripheral kernal clk
	*(RCC_CR) |= (1 << 1); // enable hsi kernel clock
	Spi123_SrcClkSel(SPI123_CLK_PER);
	// enable gpio a
	Gpio_Handle_t gpioa;
	gpioa.pGpiox = GPIOA;
	gpioa.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_ALTFN;
	gpioa.Gpio_PinConfig.Gpio_PinAltFunMode = 5;
	gpioa.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
	gpioa.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_NO_PUPD;
	gpioa.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_LOW;

		// nss pa4
	gpioa.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_4;
	Gpio_Init(&gpioa);
	// sck pa5
	gpioa.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_5;
	Gpio_Init(&gpioa);
	//mosi pa7
	gpioa.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_7;
	Gpio_Init(&gpioa);

	Spi_Handle_t spi1;
	spi1.pSpix = SPI1;
	spi1.SpiConfig.Spi_BusConfig = SPI_BUS_CONFIG_FD;
	spi1.SpiConfig.Spi_DeviceMode = SPI_DEVICE_MODE_MASTER;
	spi1.SpiConfig.Spi_Dff = SPI_DFF_MSB;
	spi1.SpiConfig.Spi_Cpol = SPI_CPOL_LOW;
	spi1.SpiConfig.Spi_CPha = SPI_CPHA_LOW;
	spi1.SpiConfig.Spi_DSize = SPI_DSIZE_XBITS(8);
	spi1.SpiConfig.Spi_SclkSpeed = SPI_SCLK_SPEED_DIV16;
	spi1.SpiConfig.Spi_Ssm = SPI_SSM_DI;
	spi1.SpiConfig.Spi_SsPol = SPI_SSPOL_LOW;
	Spi_Init(&spi1, ENABLE);

}

/*
 *SPI 6 PORT A - ALF 8
 * pa4 - nss ; pa5 - sck ; pa6 - miso ; pa7 - mosi
 */
void Spi6_PA_Init()
{
	// enable gpio a
	Gpio_Handle_t gpioa;
	gpioa.pGpiox = GPIOA;
	gpioa.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_ALTFN;
	gpioa.Gpio_PinConfig.Gpio_PinAltFunMode = 8;
	gpioa.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
	gpioa.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_NO_PUPD;
	gpioa.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_FAST;

	// nss pa4
	gpioa.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_4;
	Gpio_Init(&gpioa);
	// sck pa5
	gpioa.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_5;
	Gpio_Init(&gpioa);
	//mosi pa7
	gpioa.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_7;
	Gpio_Init(&gpioa);

	Spi_Handle_t spi6;
	spi6.pSpix = SPI6;
	spi6.SpiConfig.Spi_BusConfig = SPI_BUS_CONFIG_FD;
	spi6.SpiConfig.Spi_DeviceMode = SPI_DEVICE_MODE_MASTER;
	spi6.SpiConfig.Spi_SclkSpeed = SPI_SCLK_SPEED_DIV16;
	spi6.SpiConfig.Spi_CPha = SPI_CPHA_LOW;
	spi6.SpiConfig.Spi_Cpol = SPI_CPOL_LOW;
	spi6.SpiConfig.Spi_DSize = SPI_DSIZE_XBITS(8);
	spi6.SpiConfig.Spi_Dff = SPI_DFF_MSB;
	spi6.SpiConfig.Spi_SsPol = SPI_SSPOL_LOW;
	spi6.SpiConfig.Spi_Ssm = SPI_SSM_DI;

	Spi_Init(&spi6, ENABLE);
}

/*
 * using button to init the communication
 * pa2 user button
 */
void User_ButtonInit()
{
	Gpio_Handle_t butt;
	butt.pGpiox = GPIOA;
	butt.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_IN;
	//butt.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
	butt.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PD;
	butt.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_HIGH;
	butt.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_0;

	Gpio_Init(&butt);
}


int main(){

	char messbuff[] = "what the heck is going on";

	User_ButtonInit();
	//Spi6_PA_Init();
	Spi1_PA_Init();
	while(1)
	{
		while( ! (Gpio_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)));
		Delay();

		uint8_t datlen = strlen(messbuff);
		Spi_SendData(SPI1, &datlen , 1);
		Spi_SendData(SPI1, (uint8_t *)messbuff, strlen(messbuff));

	}
	return 0;
}
