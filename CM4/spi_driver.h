/*
 * spi_driver.h
 *
 *  Created on: Sep 17, 2020
 *      Author: jkgra
 */

#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include "stm32h755xx.h"


/*
 * REUSABLE MACROs
 */
#define SPI_DEVICE_MODE_MASTER		1
#define SPI_DEVICE_MODE_SLAVE		0

#define SPI_BUS_CONFIG_FD				1
#define SPI_BUS_CONFIG_HD				2
//#define SPI_BUS_CONFIG_S_TXONLY		3
#define SPI_BUS_CONFIG_S_RXONLY	3

#define SPI_SCLK_SPEED_DIV2				0
#define SPI_SCLK_SPEED_DIV4				1
#define SPI_SCLK_SPEED_DIV8				2
#define SPI_SCLK_SPEED_DIV16			3
#define SPI_SCLK_SPEED_DIV32			4
#define SPI_SCLK_SPEED_DIV64			5
#define SPI_SCLK_SPEED_DIV128			6
#define SPI_SCLK_SPEED_DIV2256		7

#define SPI_DFF_8BITS	0
#define SPI_DFF_16BITS	1

#define SPI_CPOL_HIGH		1
#define SPI_CPOL_LOW		0


#define SPI_CPHA_HIGH		1	// send on 1st edge then sample on 2nd edge
#define SPI_CPHA_LOW		0	//sample on 1st edge then send on 2nd edge

#define SPI_SSM_DI		0	//hw management
#define SPI_SSM_EN		1


/*
 * SPI CONFIGURATION STRUCT
 */

typedef struct {
	uint8_t Spi_DeviceMode;	//master or slave
	uint8_t Spi_BusConfig;		//full, half or simplex
	uint8_t Spi_SclkSpeed;
	uint8_t Spi_Dff;
	uint8_t Spi_Cpol;
	uint8_t Spi_CPha;
	uint8_t Spi_Ssm;
} Spi_Config_t;

/*
 * HANDLE STRUCT OF SPI
 */
typedef struct
{
	Spi_RegDef_t * pSpix;
	Spi_Config_t SpiConfig;
} Spi_Handle_t;

/*
 * Spi Api	Definition
 */

//===== PERI CLOCK CONTROL
void Spi_PeriClkControl(Spi_RegDef_t * pSpix, uint8_t EnorDi);

//===== INIT AND DEINIT
void Spi_Init(Spi_Handle_t * pSpiHandle);
void Spi_DeInit(Spi_RegDef_t* pSpix);

//===== DATA SENT AND RECEIVE
void Spi_SendData(Spi_RegDef_t* pSpix, uint8_t *ptxBuffer, uint32_t len);
void Spi_ReceiveData(Spi_RegDef_t* pSpix, uint8_t *prxBuffer, uint32_t len);

//===== 	SPI INTERRUPT CONFIG
void Spi_IrqConfig(uint8_t IrqNum, uint8_t EnorDi);

void Spi_SetIpr(uint8_t IrqNum, uint32_t IprNum);

void Spi_IrqHandling(Spi_Handle_t * pSpiHandle);



#endif /* SPI_DRIVER_H_ */
