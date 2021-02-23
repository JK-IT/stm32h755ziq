/*
 * spiDriver.c
 *
 *  Created on: Nov 20, 2020
 *      Author: jkgra
 */
#include "spiDriver.h"
#include "stdint.h"
#include "stdio.h"

void Spi_delay()
{
	for(uint32_t i =0; i < 290000; i++);
}


/*--------------------------

	**** SPI CONFIGURATION ***********

-----------------------------
*/

void Spi_Cfig(Spi_Handle_t * pSpiHandle, uint8_t masOnly)
{
	//enable spi clock and kernel clk
	RccSpi_Init(pSpiHandle->pSpix);

	//----2. bus config
	// bit 18:17 comm of spi_cfg2
	// if half- duplex mode, use bit 11 HDDIR of spi2s_cr1 to control direction
	pSpiHandle->pSpix->SPI_CFG2 |= ((uint32_t)pSpiHandle->SpiConfig.Spi_BusConfig << 17);

	//----3. serial clock - master baud rate
	// bit 30:28	of spi_cfg1
	pSpiHandle->pSpix->SPI_CFG1 |= ((uint32_t)pSpiHandle->SpiConfig.Spi_SclkSpeed << 28);

	//----4. data frame format - data size
	// data size bit 4:0		of spi_cfg1
	pSpiHandle->pSpix->SPI_CFG1 |= ((uint32_t)pSpiHandle->SpiConfig.Spi_DSize) ;
	//---- SERIAL DATA FORMAT
	// bit 23 lsbfrst of spi_cfg2	----	0: msb transmitted 1st,  1: lsb transmitted 1st
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



/*--------------------------

	**** SPI RESET ***********

-----------------------------
*/
void Spi_Reset(Spi_RegDef_t* pSpix)
{	//using rcc to reset spi block
	RccSpi_Rst(pSpix);
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
/*--------------------------

	**** SPI ENABLE STARTING THE COMM ***********

-----------------------------
*/
void Spi_start(Spi_RegDef_t* pSpix)
{
	//enable spi by enable SPE
	Spi_Toggle(pSpix, ENABLE);
	//---START COMMUNICATION BY ENABLE CSTART BIT
	//CAN ONLY SET IF MASTER = 1 AND SPE = 1
	Spi_SetCstart(pSpix, ENABLE);
}

/*--------------------------

	**** SPI DISABLE ***********

-----------------------------
*/
void Spi_end(Spi_RegDef_t* pSpix)
{
	/*
		check TXC FLAG IF TRANSACTION IS GOING OR TXFIFO IS EMPTY
		IF TSIZE = 0 , AKA ENDLESS TRANSACTION, TXC RAISING WHEN TXFIFO IS EMPTY
		IF TSIZE <> 0, TXC IS SET AT THE END OF TRANSFER
		TXC IS GOOD FOR TRANSMISSION , BUT NOT RELIABLE TO RECEPTION
	*/
	while( !Spi_GetFlagStatus(pSpix, SPI_STAT_TXC));
	// check status of RXWNE & RXPLVL BASED ON DATA FRAME
	uint8_t datsize = pSpix->SPI_CFG1 & 0x1f;
	uint8_t dump;
	if(datsize < 8)
	{
		while(Spi_GetFlagStatus(pSpix, SPI_STAT_RXPLVL)){
			dump = *((uint8_t* )&pSpix->SPI2S_RXDR);
			printf("END SPI DRIVER :data left in receive data regis %d\n", dump);
		}
	}
	
	// without clearing the eot flag, it won't work properly
	//while( ! Spi_GetFlagStatus(pSpix, SPI_STAT_EOT) );
			//clear eot or txf bit
	pSpix->SPI2S_IFCR |= (1 << 10); // clear tserf
	pSpix->SPI2S_IFCR |= (1 << 4); //clear txtf
	pSpix->SPI2S_IFCR |= (1 << 3); //clear eot, clear this as last
	Spi_SetCstart(pSpix, OFF);
	Spi_Toggle(pSpix, OFF);
	printf("END SPI DRIVER : turn off spi\n");
}

/*--------------------------

	**** SPI COMM DATA ***********

-----------------------------
*/
/*
	SEt up data in spi config, these setting need to configured before
	enable spi comm
*/
void Spi_initData(Spi_RegDef_t * pSpix, uint8_t datlen)
{
	//configure the data size in tsize of cr2, first 16bits
	//CAN ONLY SET IF SPE = 0 OR SPI IS DISABLED
	// if not config, the transaction will be endless , aka EOT flag will never  be set
	//uint8_t prepmess [2] = {cmd, (uint8_t)len};
	//pSpix->SPI_CR2 |= (sizeof prepmess / sizeof prepmess[0]); // len = 1 to send cmd
	pSpix->SPI_CR2 &= ~(0xff);
	pSpix->SPI_CR2 |= (datlen + 1);
}


//===== DATA SENT ONLY FUNCTION
// it will start and end the spi comm inside the function block
void Spi_sent_only(Spi_RegDef_t* pSpix ,uint8_t *inBuffer,uint32_t len)
{
	//getting data size from spi register
		//data size is at cfr1 , at 5:0 bit
	uint8_t datsize = pSpix->SPI_CFG1 & 0x1f;
	Spi_start(pSpix);
	
	while( ! (Spi_GetFlagStatus(pSpix, SPI_STAT_TXP)) == FLAG_SET);
	*( (uint8_t*) &(pSpix->SPI2S_TXDR)) = (len);
	//writing to txdr reg will acccess tx buffer or txfifo
	while ( len > 0 )
	{	
		// check bit 1 in status reg: 0-no space 1-space available
		//wait till there are spaces
		while (!(Spi_GetFlagStatus(pSpix, SPI_STAT_TXP) == FLAG_SET));
		//check the data size
			//load data to data register
		//data register is accessed byte-wise: 8bits, 16bits, 32bits
		if( datsize < 8 )
		{
			// load data as 8 bits
			*( (uint8_t*) &(pSpix->SPI2S_TXDR)) = *( inBuffer);
			len--;
			inBuffer++;
		}
	}

	Spi_end(pSpix);
}

//this will just send the data without controlling the spi mechanism
// FUNCTION WILL NOT SEND DAT LEN, DATLEN NEED TO BE SENT SEPERATLY
void Spi_sent(Spi_RegDef_t* pSpix, uint8_t *inBuffer, uint32_t len){
	//getting data size from spi register
		//data size is at cfr1 , at 5:0 bit
	uint8_t datsize = pSpix->SPI_CFG1 & 0x1f;
	//writing to txdr reg will acccess tx buffer or txfifo
	while ( len > 0 )
	{	
		// check bit 1 in status reg: 0-no space 1-space available
		//wait till there are spaces
		while (!(Spi_GetFlagStatus(pSpix, SPI_STAT_TXP) == FLAG_SET));
		//check the data size
			//load data to data register
		//data register is accessed byte-wise: 8bits, 16bits, 32bits
		if( datsize < 8 )
		{
			// load data as 8 bits
			*( (uint8_t*) &(pSpix->SPI2S_TXDR)) = *( inBuffer);
			len--;
			inBuffer++;
		}
	}

}

/*--------------------------

	**** SPI RECEIVE DATA ***********

-----------------------------
*/

void Spi_receive(Spi_RegDef_t* pSpix, uint8_t *outBuffer, uint32_t len)
{
	//check dat size
	uint8_t datsize = pSpix->SPI_CFG1 & 0x1f;
	while( Spi_GetFlagStatus(pSpix, SPI_STAT_RXP) == FLAG_SET)
	{
		if( len == 0)	break;
		if(datsize < 8){
			//0x40003830
			uint8_t red = *( (uint8_t*)&pSpix->SPI2S_RXDR);
			//uint32_t red = *( (uint32_t*)0x40003830);
			printf("SPI RECEI : from ardu %d\n", red);
			len--;
			outBuffer++;
		}
	}
}



//===== 	SPI INTERRUPT CONFIG
void Spi_IrqConfig(uint8_t IrqNum, uint8_t EnorDi){}

void Spi_SetIpr(uint8_t IrqNum, uint32_t IprNum){}

void Spi_IrqHandling(Spi_Handle_t * pSpiHandle){}

//===== Other Config

/*--------------------------

	**** SPI ENABLE ***********

-----------------------------
*/
	/*
	 * Enable SPI in Spi Control Register
	 * bit SPE = 0 of CR1
	 */
void Spi_Toggle(Spi_RegDef_t * pSpix, uint8_t EnorDi)
{
	if(EnorDi == ENABLE){
		pSpix->SPI2S_CR1 |= 1;
	} else {
		pSpix->SPI2S_CR1 &= ~(1);
	}
}

/*--------------------------

	**** SPI SET SSOE PIN ***********

-----------------------------
*/

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

/*--------------------------

	**** SPI SET SSI PIN ***********

-----------------------------
*/

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

/*--------------------------

	**** SPI SET CSTART PIN ***********

-----------------------------
*/

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
