/*
 * spi_driver.c
 *
 *  Created on: Sep 17, 2020
 *      Author: jkgra
 */
#include "spi_driver.h"

//===== PERI CLOCK CONTROL
/*
 * @param1[in]		Spi Peripheral
 * @param2[in]		Enable or Disable
 */
void Spi_PeriClkControl(Spi_RegDef_t * pSpix, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSpix == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if(pSpix == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if(pSpix == SPI3)
		{
			SPI3_PCLK_EN();
		}
		else if (pSpix == SPI4)
		{
			SPI4_PCLK_EN();
		}
		else if (pSpix == SPI5)
		{
			SPI5_PCLK_EN();
		} else
		{
			SPI6_PCLK_EN();
		}
	} else
	{
		if(pSpix == SPI1)
		{
			SPI1_PCLK_DI();
		}
		else if(pSpix == SPI2)
		{
			SPI2_PCLK_DI();
		}
		else if(pSpix == SPI3)
		{
			SPI3_PCLK_DI();
		}
		else if (pSpix == SPI4)
		{
			SPI4_PCLK_DI();
		}
		else if (pSpix == SPI5)
		{
			SPI5_PCLK_DI();
		} else
		{
			SPI6_PCLK_DI();
		}
	}
}

void Spi123_SrcClkSel( uint8_t clkNum)
{
	*(RCC_D2CCIP1R) |= (clkNum << 12);
}

//===== INIT AND DEINIT
void Spi_Init(Spi_Handle_t * pSpiHandle, uint8_t masOnly)
{

	//enable spi clock to access register
	Spi_PeriClkControl(pSpiHandle->pSpix, ENABLE);

	//----2. bus config
	// bit 18:17 comm of spi_cfg2
	// if half- duplex mode, use bit 11 HDDIR of spi2s_cr1 to control direction
	pSpiHandle->pSpix->SPI_CFG2 |= ((uint32_t)pSpiHandle->SpiConfig.Spi_BusConfig << 17);

	//----3. serial clock - master baud rate
	// bit 30:28	of spi_cfg1
	pSpiHandle->pSpix->SPI_CFG1 |= ((uint32_t)pSpiHandle->SpiConfig.Spi_SclkSpeed << 28);

	//----4. data frame format - data size
	// data size bit 4:0		of spi_cfg1
	// bit 23 lsbfrst of spi_cfg2	----	0: msb transmitted 1st,  1: lsb transmitted 1st
	pSpiHandle->pSpix->SPI_CFG1 |= ((uint32_t)pSpiHandle->SpiConfig.Spi_DSize) ;
	/*if(pSpiHandle->SpiConfig.Spi_DSize < 8)
	{
		pSpiHandle->pSpix->SPI_CFG1 |= (1 << 5);
	}*/
	pSpiHandle->pSpix->SPI_CFG2 |= ((uint32_t)pSpiHandle->SpiConfig.Spi_Dff << 23);

	//----5. Clock Polarity
	//bit 25 of spi_cfg2		0: idle when clk at low lev		1: idle when clk at high lev
	pSpiHandle->pSpix->SPI_CFG2 |= ((uint32_t)pSpiHandle->SpiConfig.Spi_Cpol << 25);

	//-----6. Clock phase
	// bit 24 of spi_cfg2		0: captured 1st edge, transmitted ; 2nd edge	1: transmit 1st then capture
	pSpiHandle->pSpix->SPI_CFG2 |= ((uint32_t)pSpiHandle->SpiConfig.Spi_CPha << 24);

	//------7. SS software management
	//bit 26 of spi_cfg2	0: hardware		1: software control with SSI bit 12 in spi2s_cr1
	pSpiHandle->pSpix->SPI_CFG2 |= ( (uint32_t)pSpiHandle->SpiConfig.Spi_Ssm << 26);

	// SSIOP SS signal active polarity  -- SS active when  0: low lev  or 1: high lev
	pSpiHandle->pSpix->SPI_CFG2 |= ( (uint8_t)pSpiHandle->SpiConfig.Spi_SsPol << 28);

	// single master
		//need to configure SS Output Enable, pin 29 of cfgr2
		//SSOE = 0 means SS is input, SSOE = 1 means output
	if(masOnly)
	{
		//Spi_SsoeConfig(SPI2, ENABLE);
		pSpiHandle->pSpix->SPI_CFG2 |= (1 << 29);
	}
	//modfault will be enable if device is master and has SSOE disabled and ss pin is at active lev
	//if ssm = 1 and ssiop = 0 or low --> switch ssi =1 to prevent modefault
	//if ssm = 1 and ssiop = 1 or low --> switch ssi =0 to prevent modefault
	if(pSpiHandle->SpiConfig.Spi_Ssm == ENABLE)
	{
		//set ssi bit based on ssio polarity
		if(pSpiHandle->SpiConfig.Spi_SsPol == SPI_SSPOL_LOW)
		{
			Spi_SetSsi(pSpiHandle->pSpix, ENABLE);
		} else
		{
			Spi_SetSsi(pSpiHandle->pSpix, DISABLE);
		}

	}

	//----1. device mode
	// bit 22 master of spi_cfg2 for stm32h755xx
	pSpiHandle->pSpix->SPI_CFG2 |= ((uint32_t)pSpiHandle->SpiConfig.Spi_DeviceMode << 22);

}
void Spi_DeInit(Spi_RegDef_t* pSpix)
{	//using rcc to reset spi block
	if ( pSpix == SPI1)
	{	// bit 12 rcc_apb2rstr
		SPI1_REG_RST();
	}
	else if ( pSpix == SPI2)
	{	//bit 14 rcc_apb1lrstr
		SPI2_REG_RST();
	}
	else if ( pSpix == SPI3)
	{	//bit 15 rcc_apb1lrstr
		SPI3_REG_RST();
	}
	else if ( pSpix == SPI4)
	{	//bit 13 rcc_apb2rstr
		SPI4_REG_RST();
	}
	else if ( pSpix == SPI5)
	{	//bit 20 rcc_apb2rstr
		SPI5_REG_RST();
	}
	else if ( pSpix == SPI6)
	{	//bit 5 rcc_apb4rstr
		SPI6_REG_RST();
	}
}

/*
 * Purpose: enable port pin that will be used as spi
 * Different spiNum will have different number of pin to use on each port
 * Enable all port pin as spi if the spiNum is scattering around
 * The pin that will be used is from reference book
 */

void Spi_GpioInit(Gpio_RegDef_t* inPort, uint8_t spiNum)
{
	if(spiNum == Spi_No_1)
	{

		// configure PORT A PIN 4 -NSS, 5-SCK, 6-MISO, 7-MOSI
		//ALTF = 5
		if(inPort == GPIOA)
		{
			Gpio_Handle_t pa;
			pa.pGpiox = GPIOA;
			pa.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_ALTFN;
			pa.Gpio_PinConfig.Gpio_PinAltFunMode = 5;
			pa.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
			pa.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PU;
			pa.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_MED;
			//nss pa4
			//pa.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_4;
			//Gpio_Init(&pa);
			//sck pa5
			pa.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_5;
			Gpio_Init(&pa);
			//miso pa6
			//pa.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_6;
			//Gpio_Init(&pa);
			//mosi pa7
			pa.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_7;
			Gpio_Init(&pa);
		}
	} else if(spiNum == Spi_No_2)
	{
		// will need to look up the reference manual to find out the altfn number
		//this setup : port B, pin 12-15, altfn =5
		if(inPort == GPIOB)
		{
			Gpio_Handle_t port;
			port.pGpiox = GPIOB;
			port.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_ALTFN;
			port.Gpio_PinConfig.Gpio_PinAltFunMode = 5;
			port.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
			port.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PU;
			port.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_MED;

			// nss pin 12 port b
			port.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_12;
			Gpio_Init(&port);

			//sck pin 13 port b
			port.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_13;
			Gpio_Init(&port);

			//miso pin 14 port b
			//port.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_14;
			//Gpio_Init(&port);

			//mosi pin 15 port b
			port.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_15;
			Gpio_Init(&port);
		}

	} else if(spiNum == Spi_No_3)
	{

	} else if(spiNum == Spi_No_4)
	{

	} else if(spiNum == Spi_No_5)
	{

	} else if(spiNum == Spi_No_6)
	{

	}
}


uint8_t Spi_GetFlagStatus(Spi_RegDef_t* pSpix, uint32_t flagname)
{
	if( pSpix->SPI2S_SR &  flagname)
	{
		return FLAG_SET;
	} else {
		return FLAG_RESET;
	}
}

//===== DATA SENT FUNCTION
void Spi_SendData(Spi_RegDef_t* pSpix ,uint8_t *ptxBuffer, uint32_t len)
{
	//getting data size from spi register
		//data size is at cfr1 , at 5:0 bit
	uint8_t datsize = pSpix->SPI_CFG1 & 0x1f;

	//configure the data size in tsize of cr2, first 16bits
	//CAN ONLY SET IF SPE = 0 OR SPI IS DISABLED
	// if not config, the transaction will be endless , aka EOT flag will never  be set
	pSpix->SPI_CR2 &= ~(0xff);
	pSpix->SPI_CR2 |= (uint16_t)(len * 4);

	//enable spi by enable SPE
	Spi_PerControl(pSpix, ENABLE);
	//---START COMMUNICATION BY ENABLE CSTART BIT
	//CAN ONLY SET IF MASTER = 1 AND SPE = 1
	Spi_SetCstart(pSpix, ENABLE);

	//writing to txdr reg will acccess tx buffer or txfifo
	while ( len > 0 )
	{	// check bit 1 in status reg: 0-no space 1-space available
		//wait till there are spaces
		while (!(Spi_GetFlagStatus(pSpix, SPI_STAT_TXP) == FLAG_SET));
		//check the data size
			//load data to data register
		//data register is accessed byte-wise: 8bits, 16bits, 32bits
		if( datsize < 8 )
		{
			// load data as 8 bits
			pSpix->SPI2S_TXDR = *( ptxBuffer);
			len--;
			ptxBuffer++;
		}
		else if ( (datsize) >=8 && (datsize) < 16 )
		{
			if(len < 2)
			{
				// load data as  bits
			    pSpix->SPI2S_TXDR = *(ptxBuffer);
				len -= 1;
				ptxBuffer += 1;
			} else
			{
				// load data as 16 bits
				pSpix->SPI2S_TXDR = *((uint16_t*) ptxBuffer);
				len -= 2;
				ptxBuffer +=2;
			}
		} else if ( (datsize) >=16 && (datsize) < 32 )
		{
			//load data as 32 bits
			pSpix->SPI2S_TXDR = *((uint32_t*) ptxBuffer);
			if( len < 4)
			{
				ptxBuffer += len;
				len = 0;
			} else
			{
				len -= 4;
				ptxBuffer += 4;
			}
		}
	}
	while( ! Spi_GetFlagStatus(pSpix, SPI_STAT_TXC));
	while(  Spi_GetFlagStatus(pSpix, SPI_STAT_RXWNE) &  Spi_GetFlagStatus(pSpix, SPI_STAT_RXPLVL)  )
	{
		uint32_t dispose = pSpix->SPI2S_RXDR;
	}
	// without clearing the eot flag, it won't work properly
	while( ! Spi_GetFlagStatus(pSpix, SPI_STAT_EOT) );
			//clear eot or txf bit
		pSpix->SPI2S_IFCR |= (1 << 3);
		pSpix->SPI2S_IFCR |= (1 << 4);

	Spi_PerControl(pSpix, DISABLE);
}

void Spi_ReceiveData(Spi_RegDef_t* pSpix, uint8_t *prxBuffer, uint32_t len);

//===== 	SPI INTERRUPT CONFIG
void Spi_IrqConfig(uint8_t IrqNum, uint8_t EnorDi);

void Spi_SetIpr(uint8_t IrqNum, uint32_t IprNum);

void Spi_IrqHandling(Spi_Handle_t * pSpiHandle);

//===== Other Config
	/*
	 * Enable SPI in Spi Control Register
	 * bit SPE = 0 of CR1
	 */
void Spi_PerControl(Spi_RegDef_t * pSpix, uint8_t EnorDi)
{
	if(EnorDi == ENABLE){
		pSpix->SPI2S_CR1 |= 1;
	} else {
		pSpix->SPI2S_CR1 &= ~(1);
	}
}

	/*
	 * Enable SSOE in Spi Control Register
	 * bit SSOE = 29 of CFGR2
	 * 0: output is disabled -> spi works in multi-master mode
	 * 1: output is enabled -> spi cannot work in multi-master mode
	 */
void Spi_SsoeConfig(Spi_RegDef_t* pSpix, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSpix->SPI_CFG2 |= (1 << 29);
	} else {
		pSpix->SPI_CFG2 &= ~(1 << 29);
	}
}

void Spi_SetSsi( Spi_RegDef_t* inSpi , uint8_t EnoDi)
{
	if(EnoDi == ENABLE)
	{
		//bit 12 in CR1 of Spi
		inSpi->SPI2S_CR1 |= (1 << 12);
	} else
	{
		inSpi->SPI2S_CR1 &= ~(1 << 12);
	}
}

void Spi_SetCstart(Spi_RegDef_t* inspi, uint8_t dioren)
{
	if(dioren == ENABLE)
	{
		inspi->SPI2S_CR1 |= (1<< 9);
	} else
	{
		inspi->SPI2S_CR1 &= ~(1<< 9);
	}
}

