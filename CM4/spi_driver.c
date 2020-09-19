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

//===== INIT AND DEINIT
void Spi_Init(Spi_Handle_t * pSpiHandle)
{

}
void Spi_DeInit(Spi_RegDef_t* pSpix);

//===== DATA SENT AND RECEIVE
void Spi_SendData(Spi_RegDef_t* pSpix, uint8_t *ptxBuffer, uint32_t len);
void Spi_ReceiveData(Spi_RegDef_t* pSpix, uint8_t *prxBuffer, uint32_t len);

//===== 	SPI INTERRUPT CONFIG
void Spi_IrqConfig(uint8_t IrqNum, uint8_t EnorDi);

void Spi_SetIpr(uint8_t IrqNum, uint32_t IprNum);

void Spi_IrqHandling(Spi_Handle_t * pSpiHandle);
