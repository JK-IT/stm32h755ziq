/*
 * spi.h
 *
 *  Created on: Apr 10, 2021
 *      Author: kdg
 */


#ifndef SPI_H_
#define SPI_H_
#include "stm32h755xx.h"
#include "rcc.h"


#define 	NULL	((void*)0)

/*
 * REUSABLE MACROs
 */
#define SPI_DEVICE_MODE_MASTER		1
#define SPI_DEVICE_MODE_SLAVE		0

#define SPI_BUS_CONFIG_FD				0
#define SPI_BUS_CONFIG_HD				3
#define SPI_BUS_CONFIG_S_TXONLY		1
#define SPI_BUS_CONFIG_S_RXONLY	2

#define SPI_SCLK_SPEED_DIV2				0
#define SPI_SCLK_SPEED_DIV4				1
#define SPI_SCLK_SPEED_DIV8				2
#define SPI_SCLK_SPEED_DIV16			3
#define SPI_SCLK_SPEED_DIV32			4
#define SPI_SCLK_SPEED_DIV64			5
#define SPI_SCLK_SPEED_DIV128			6
#define SPI_SCLK_SPEED_DIV256		7

#define SPI_DSIZE_XBITS(x)	((x < 5) ? 3 : (x -1))
#define SPI_DFF_MSB	0	// most significant bit goes first
#define SPI_DFF_LSB		1	// lsb bit goes first

#define SPI_CPOL_HIGH		1
#define SPI_CPOL_LOW		0


#define SPI_CPHA_HIGH		1	// send on 1st edge then sample on 2nd edge
#define SPI_CPHA_LOW		0	//sample on 1st edge then send on 2nd edge

#define SPI_SSM_DI		0	//hw management
#define SPI_SSM_EN		1

	//flag of status register
	// shift by the bit position in register
#define SPI_STAT_TXP			(1 << 1)	//txfifo space available
#define SPI_STAT_RXP			(1 << 0) //rxfifo space available
#define SPI_STAT_DPXP			(1 << 2) // dxp full duplex flag
#define SPI_STAT_RXWNE	(1 << 15) //rx word not empty space available
#define SPI_STAT_RXPLVL	(3 << 13) //rx packed frames available space available
#define SPI_EOT_FLAG	0x03
#define SPI_TXFT_FLAG	0x04
#define SPI_STAT_EOT 		(1 << 3) // end of transfer
#define SPI_STAT_TXC 		(1 << 12) // TRANSMISSION COMPLETE
#define SPI_STAT_MODF 		(1 << 9) // MODE FAULT


	//SSI SIGNAL
#define SSI_HIGH		1
#define SSI_LOW		0

	//SPI NUMBER
#define Spi_No_1		1
#define Spi_No_2		2
#define Spi_No_3 	3
#define Spi_No_4		4
#define Spi_No_5		5
#define Spi_No_6		6

	// SPI SS POLARITY
#define SPI_SSPOL_LOW		0
#define SPI_SSPOL_HIGH		1

	//SPI COMMAND


/*
 * SPI CONFIGURATION STRUCT
 */

typedef struct {
	uint8_t Spi_DeviceMode;	//master or slave
	uint8_t Spi_BusConfig;		//full, half or simplex
	uint8_t Spi_SclkSpeed;
	uint8_t Spi_Dff;
	uint8_t Spi_DSize; // max size is 32 bits
	uint8_t Spi_Cpol;	// 0: low lev idle active, 1: high lev idle active
	uint8_t Spi_CPha;	// 0: capture 1st, 1: transmit 1st
	uint8_t Spi_Ssm;
	uint8_t Spi_SsPol;
	uint8_t Spi_Ssoe; 	//enable ouput on nss pin
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


//===== INIT AND DEINIT
void Spi_Cfig(Spi_Handle_t * pSpiHandle, uint8_t masOnly);
void Spi_Reset(Spi_RegDef_t* pSpix);


//===== DATA SENT AND RECEIVE
/*
	SEt up data in spi config, these setting need to configured before
	enable spi comm
*/
void Spi_initData(Spi_RegDef_t * pSpix, uint8_t datlen);

void Spi_start(Spi_RegDef_t* pSpix);
//this will start and end the spi when done transmitting by itself
void Spi_sent_only(Spi_RegDef_t* pSpix, uint8_t *inBuffer, uint32_t len);
//this will just send the data without controlling the spi mechanism
void Spi_sent(Spi_RegDef_t* pSpix, uint8_t *inBuffer, uint32_t len);

void Spi_receive(Spi_RegDef_t* pSpix, uint8_t *outBuffer, uint32_t len);
void Spi_end(Spi_RegDef_t* pSpix);

//===== 	SPI INTERRUPT CONFIG
void Spi_IrqConfig(uint8_t IrqNum, uint8_t EnorDi);

void Spi_SetIpr(uint8_t IrqNum, uint32_t IprNum);

void Spi_IrqHandling(Spi_Handle_t * pSpiHandle);

//===== SPI OTHER CONFIG
void Spi_Toggle(Spi_RegDef_t * pSpix, uint8_t EnorDi);
void Spi_SsoeConfig(Spi_RegDef_t* pSpix, uint8_t EnorDi);
void Spi_SetSsi( Spi_RegDef_t* inSpi , uint8_t EnoDi);
void Spi_SetCstart(Spi_RegDef_t* inspi, uint8_t dioren);
uint8_t Spi_GetFlagStatus(Spi_RegDef_t* pSpix, uint32_t flagname);

#endif /* SPI_H_ */
