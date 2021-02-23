/*
 * rccDriver.c
 *
 *  Created on: Nov 10, 2020
 *      Author: jkgra
 */

#include <rccDriver.h>

/*============================
	GPIO RCC SECTION ======================
*/

/*-----------------------------------

 * ENABLE GPIO PERIPHERAL CLOCKS
 * BY DEFAULT ALL DISABLE
 * BY DEFAULT ALL CLOCK IS ENABLE IN CSLEEP MODE
 * ALL GPIO IS ON AHB4 == D3;
 * 
 -----------------------------------------*/

void RccGpio_ClkCon(Gpio_RegDef_t * gpio, uint8_t endi)
{
	if(endi == ENABLE)
	{
		if(gpio == GPIOA)
		{
			RCC->RCC_AHB4ENR |= (1 << 0);
			// read back the reg to make sure it is not waiting in buffer
			while ( ! (RCC->RCC_AHB4ENR >> 0 ) & 0x1);
			//perform dummy read to make sure clock is enabled properly
			uint32_t temp = GPIOA->Moder;
		} else if(gpio == GPIOB)
		{
			RCC->RCC_AHB4ENR |= (1 << 1);
			// read back the reg to make sure it is not waiting in buffer
			while ( ! (RCC->RCC_AHB4ENR >> 1 ) & 0x1);
			//perform dummy read to make sure clock is enabled properly
			uint32_t temp = GPIOB->Moder;
		} else if(gpio == GPIOC)
		{
			RCC->RCC_AHB4ENR |= (1 << 2);
			// read back the reg to make sure it is not waiting in buffer
			while ( ! (RCC->RCC_AHB4ENR >> 2 ) & 0x1);
			//perform dummy read to make sure clock is enabled properly
			uint32_t temp = GPIOC->Moder;
		} else if(gpio == GPIOD)
		{
			RCC->RCC_AHB4ENR |= (1 << 3);
			// read back the reg to make sure it is not waiting in buffer
			while ( ! (RCC->RCC_AHB4ENR >> 3 ) & 0x1);
			//perform dummy read to make sure clock is enabled properly
			uint32_t temp = GPIOD->Moder;
		} else if(gpio == GPIOE)
		{
			RCC->RCC_AHB4ENR |= (1 << 4);
			// read back the reg to make sure it is not waiting in buffer
			while ( ! (RCC->RCC_AHB4ENR >> 4 ) & 0x1);
			//perform dummy read to make sure clock is enabled properly
			uint32_t temp = GPIOE->Moder;
		} else if(gpio == GPIOF)
		{
			RCC->RCC_AHB4ENR |= (1 << 5);
			// read back the reg to make sure it is not waiting in buffer
			while ( ! (RCC->RCC_AHB4ENR >> 5 ) & 0x1);
			//perform dummy read to make sure clock is enabled properly
			uint32_t temp = GPIOF->Moder;
		} else if(gpio == GPIOG)
		{
			RCC->RCC_AHB4ENR |= (1 << 6);
			// read back the reg to make sure it is not waiting in buffer
			while ( ! (RCC->RCC_AHB4ENR >> 6 ) & 0x1);
			//perform dummy read to make sure clock is enabled properly
			uint32_t temp = GPIOG->Moder;
		} else if(gpio == GPIOH)
		{
			RCC->RCC_AHB4ENR |= (1 << 7);
			// read back the reg to make sure it is not waiting in buffer
			while ( ! (RCC->RCC_AHB4ENR >> 7 ) & 0x1);
			//perform dummy read to make sure clock is enabled properly
			uint32_t temp = GPIOH->Moder;
		} else if(gpio == GPIOI)
		{
			RCC->RCC_AHB4ENR |= (1 << 8);
			// read back the reg to make sure it is not waiting in buffer
			while ( ! (RCC->RCC_AHB4ENR >> 8 ) & 0x1);
			//perform dummy read to make sure clock is enabled properly
			uint32_t temp = GPIOI->Moder;
		} else if(gpio == GPIOJ)
		{
			RCC->RCC_AHB4ENR |= (1 << 9);
			// read back the reg to make sure it is not waiting in buffer
			while ( ! (RCC->RCC_AHB4ENR >> 9 ) & 0x1);
			//perform dummy read to make sure clock is enabled properly
			uint32_t temp = GPIOJ->Moder;
		} else if(gpio == GPIOK)
		{
			RCC->RCC_AHB4ENR |= (1 << 10);
			// read back the reg to make sure it is not waiting in buffer
			while ( ! (RCC->RCC_AHB4ENR >> 10 ) & 0x1);
			//perform dummy read to make sure clock is enabled properly
			uint32_t temp = GPIOK->Moder;
		}
	} else
	{
		if(gpio == GPIOA)
		{
			RCC->RCC_AHB4ENR &= ~(1 << 0);
		} else if(gpio == GPIOB)
		{
			RCC->RCC_AHB4ENR &= ~(1 << 1);
		} else if(gpio == GPIOC)
		{
			RCC->RCC_AHB4ENR &= ~(1 << 2);
		} else if(gpio == GPIOD)
		{
			RCC->RCC_AHB4ENR &= ~(1 << 3);
		} else if(gpio == GPIOE)
		{
			RCC->RCC_AHB4ENR &= ~(1 << 4);
		} else if(gpio == GPIOF)
		{
			RCC->RCC_AHB4ENR &= ~(1 << 5);
		} else if(gpio == GPIOG)
		{
			RCC->RCC_AHB4ENR &= ~(1 << 6);
		} else if(gpio == GPIOH)
		{
			RCC->RCC_AHB4ENR &= ~(1 << 7);
		} else if(gpio == GPIOI)
		{
			RCC->RCC_AHB4ENR &= ~(1 << 8);
		} else if(gpio == GPIOJ)
		{
			RCC->RCC_AHB4ENR &= ~(1 << 9);
		} else if(gpio == GPIOK)
		{
			RCC->RCC_AHB4ENR &= ~(1 << 10);
		}
	}
}

/*---------------------

 ********** GPIO BLOCK RESET************
 * 
 * -------------------------------*/
void RccGpio_Rst(Gpio_RegDef_t * gpio)
{
	if(gpio == GPIOA)
	{
		RCC->RCC_AHB4RSTR &= ~(1<< 0);
		RCC->RCC_AHB4RSTR |= (1<< 0);
	} else if(gpio == GPIOB)
	{
		RCC->RCC_AHB4RSTR &= ~(1<< 1);
		RCC->RCC_AHB4RSTR |= (1<< 1);
	} else if(gpio == GPIOC)
	{
		RCC->RCC_AHB4RSTR &= ~(1<< 2);
		RCC->RCC_AHB4RSTR |= (1<< 2);
	} else if(gpio == GPIOD)
	{
		RCC->RCC_AHB4RSTR &= ~(1<< 3);
		RCC->RCC_AHB4RSTR |= (1<< 3);
	} else if(gpio == GPIOE)
	{
		RCC->RCC_AHB4RSTR &= ~(1<< 4);
		RCC->RCC_AHB4RSTR |= (1<< 4);
	} else if(gpio == GPIOF)
	{
		RCC->RCC_AHB4RSTR &= ~(1<< 5);
		RCC->RCC_AHB4RSTR |= (1<< 5);
	} else if(gpio == GPIOG)
	{
		RCC->RCC_AHB4RSTR &= ~(1<< 6);
		RCC->RCC_AHB4RSTR |= (1<< 6);
	} else if(gpio == GPIOH)
	{
		RCC->RCC_AHB4RSTR &= ~(1<< 7);
		RCC->RCC_AHB4RSTR |= (1<< 7);
	} else if(gpio == GPIOI)
	{
		RCC->RCC_AHB4RSTR &= ~(1<< 8);
		RCC->RCC_AHB4RSTR |= (1<< 8);
	} else if(gpio == GPIOJ)
	{
		RCC->RCC_AHB4RSTR &= ~(1<< 9);
		RCC->RCC_AHB4RSTR |= (1<< 9);
	} else if(gpio == GPIOK)
	{
		RCC->RCC_AHB4RSTR &= ~(1<< 10);
		RCC->RCC_AHB4RSTR |= (1<< 10);
	}
}


/*===========================
 * SPI -RCC SECTION ======================
 */


/*---------------------------------------

	Enable SPi Peripheral and its default source clk
	@pa1: spi specific
	Note: spi12345 -> D2, spi6 -> D3

-----------------------------------------*/

void RccSpi_Init(Spi_RegDef_t* spi)
{
	if(spi == SPI1) 	// domain 2 cpu2
	{
		//bit 12 apb2enr & apb2lenr
		RCC->RCC_APB2ENR |= (1 << 12);
		RCC->RCC_APB2LPENR |= (1 << 12);
		while( ! ((RCC->RCC_APB2ENR >> 12) & 0x1) );
		// read d2clkrdy bit stat, if peri is on diff domain then reading
		// this bit to see if domain is power on
		while( ! (RCC->RCC_CR >> 15) & 0x1);
		// check stand by flag sbf_d2
		do {
			// clear the stand by flag
			PWR->PWR_CPU2CR |= (1 << 9);
		} while ( (PWR->PWR_CPU2CR >> 8) & 0X1);
		uint32_t temp = SPI1->SPI2S_SR; // dummy read

	//--' setting source clk : pll1 Q 
		if( ! PLL1_STAT) // CLK IS NOT ON	
		{
			// enable p or q or r output before turn on pll
			PLL1Q_EN(ENABLE);
			//enable clock
			Rcc_Toggle_SrcClk(RCC_PLL1, ENABLE);
			while ( ! PLL1_STAT);
		}	

	}  
	else if(spi == SPI2)
	{	
		//D2
		RCC->RCC_APB1LENR |= ( 1 << 14);
		RCC->RCC_APB1LLPENR |= ( 1 << 14);
		while( ! (RCC->RCC_APB1LENR >> 14) & 0x1);
		// check d2 domain clk
		while ( ! (RCC->RCC_CR >> 15) & 0x1 );
		//check stb flag
		do {
			// try to clear the flag
			PWR->PWR_CPU2CR |= ( 1 << 9);
		} while ( (PWR->PWR_CPU2CR >> 8) & 0x1 );
		uint32_t temp = SPI2->SPI2S_SR;
		//-- setting default src clock
		if ( ! PLL1_STAT)
		{
			PLL1Q_EN(ENABLE);
			Rcc_Toggle_SrcClk(RCC_PLL1, ENABLE);
			while ( ! PLL1_STAT);
		}
	}
	else if(spi == SPI3)
	{
		//d2
		RCC->RCC_APB1LENR |= ( 1 << 15);
		RCC->RCC_APB1LLPENR |= ( 1 << 15);
		while ( ! (RCC->RCC_APB1LENR >> 15) & 0x1);
		//check d2 clk
		while ( ! (RCC->RCC_CR >> 15) & 0x1);
		//check stb flag
		do {
			PWR->PWR_CPU2CR |= ( 1 << 9);
		} while ( (PWR->PWR_CPU2CR >> 8) & 0x1 );
		uint32_t temp = SPI3->SPI2S_SR;
		//-- setting default src clock
		//Spi123def_clksrc_on();
		if ( ! PLL1_STAT)
		{
			PLL1Q_EN(ENABLE);
			Rcc_Toggle_SrcClk(RCC_PLL1, ENABLE);
			while ( ! PLL1_STAT);
		}
	}
	else if(spi == SPI4)
	{
		//D2
		RCC->RCC_APB2ENR |= ( 1 <<  13);
		RCC->RCC_APB2LPENR |= (1 << 13);
		while ( ! (RCC->RCC_APB2ENR >> 13) & 0x1);

		while ( ! (RCC->RCC_CR >> 15) & 0x1);
		do {
			PWR->PWR_CPU2CR |= ( 1 << 9);
		} while ( (PWR->PWR_CPU2CR >> 8) & 0x1);
		uint32_t temp = SPI4->SPI2S_SR;
		// default src clk : apb aka d2 clk

	}
	else if(spi == SPI5)
	{
		//d2
		RCC->RCC_APB2ENR |= (1 << 20);
		RCC->RCC_APB2LPENR |= ( 1 << 20);
		while( ! (RCC->RCC_APB2ENR >> 20) & 0x1);

		while( ! (RCC->RCC_CR >> 15) & 0x1);
		do {
			PWR->PWR_CPU2CR |= ( 1<< 9);
		} while ( (PWR->PWR_CPU2CR >> 8) & 0x1);
		uint32_t temp = SPI5->SPI2S_SR;
		//default clk is apb clk aka d2 clk
	}
	else if(spi == SPI6)
	{
		//hang on apb4 --> d3, also enable spi6 automation mode
		// make sure run_d3 bit in pwr_cpuxcr is set 
		RCC->RCC_D3AMR |= ( 1<< 5);
		//D3  and system will be running if cpu in run mode or low power bit is enabled
		RCC->RCC_APB4ENR |= ( 1 << 5);
		RCC->RCC_APB4LPENR |= ( 1 << 5);
		//default clk is d3 pclk so no need to activate
	}
}
/*--------------------------------------

	SPI123 CLOCK SWITCHING ============

---------------------------------------*/

void RccSpi1_ClkSw(Spi123_SrcClk inclk)
{
	if(inclk == spi1pll1q_clk) //cfig and enable clk
	{
		if ( ! PLL1_STAT)
		{
			PLL1Q_EN(ENABLE);
			Rcc_Toggle_SrcClk(RCC_PLL1, ENABLE);
			while ( ! PLL1_STAT);
		}
		RCC->RCC_D2CCIP1R |= (spi1pll1q_clk << 12); //set target clock
	} 
	else if(inclk == spi1pll2p_clk)
	{
		if( ! PLL2_STAT)
		{
			PLL2P_EN(ENABLE);
			Rcc_Toggle_SrcClk(RCC_PLL2, ENABLE);
			while( ! PLL2_STAT);
		}
		RCC->RCC_D2CCIP1R |= (spi1pll2p_clk << 12);
	}
	else if(inclk == spi1pll3p_clk)
	{
		if( ! PLL3_STAT)
		{
			PLL3P_EN(ENABLE);
			Rcc_Toggle_SrcClk(RCC_PLL3, ENABLE);
			while( ! PLL3_STAT);
		}
		RCC->RCC_D2CCIP1R |= (spi1pll3p_clk << 12);
	}
	else if(inclk == spi1per_clk)
	{
		//this clock require hsi_ker, by dfeault will not be on
		RCC->RCC_D2CCIP1R |= (spi1per_clk << 12);
	}
}

/*-------------------------------------

	**********SPI 45 CLOCK SWITCHING ============

---------------------------------------*/

void RccSpi4_ClkSw(Spi45_SrcClk inclk)
{
	if(inclk == spi4def_clk)
	{	// APB CLK == d2 clk so check if d2 clk rdy flag
		//domain only enter dstop, dstandby if there is no active peri and cpu is in cstop
		//aka, this d2clk should always be on, besides spi should be on when u run init fnc
		//unless u put it back to sleep mode
		// if d2 is on --> swich , if not keep current
		RCC->RCC_D2CCIP1R |= (spi4def_clk << 16);
	}
	else if(inclk == spi4pll2q_clk)
	{
		if( ! PLL2_STAT)
		{
			PLL2Q_EN(ENABLE);
			Rcc_Toggle_SrcClk(RCC_PLL2, ENABLE);
			while( ! PLL2_STAT);
		}
		RCC->RCC_D2CCIP1R |= (spi4pll2q_clk << 16);
	}
	else if(inclk == spi4pll3q_clk)
		{
		if( ! PLL3_STAT)
		{
			PLL3Q_EN(ENABLE);
			Rcc_Toggle_SrcClk(RCC_PLL3, ENABLE);
			while( ! PLL3_STAT);
		}
		RCC->RCC_D2CCIP1R |= (spi4pll3q_clk << 16);
	}
	else if(inclk == spi4hsi_ker_clk)
	{	//hsi ker clk = hsi clk
		//hsi ker ENABLE bit is set when running Rcc_Init() 
		if( ! HSI_STAT)
		{
			Rcc_Toggle_SrcClk(RCC_HSI, ENABLE);
			while( ! HSI_STAT);
		}
		RCC->RCC_D2CCIP1R |= (spi4hsi_ker_clk << 16);
	}
	else if(inclk == spi4csi_ker_clk)
	{	//csi ker == csi
		if( ! CSI_STAT)
		{
			Rcc_Toggle_SrcClk(RCC_CSI, ENABLE);
			while( ! CSI_STAT);
		}
		RCC->RCC_D2CCIP1R |= (spi4csi_ker_clk << 16);
	}
	else if(inclk == spi4hse_clk)
	{
		if( ! HSE_STAT)
		{
			Rcc_Toggle_SrcClk(RCC_HSE, ENABLE);
			while( ! HSE_STAT);
		}
		RCC->RCC_D2CCIP1R |= (spi4hse_clk << 16);
	}
}

/*--------------------------

	*** SPI 6 CLK SWITCH========================

----------------------------
*/
void RccSpi6_ClkSw(Spi6_SrcClk inclk)
{
	if(inclk == spi6pclk4)
	{
		RCC->RCC_D3CCIPR |= ( spi6pclk4 << 28);
	} 
	else if (inclk == spi6pll2q_clk)
	{
		if( ! PLL2_STAT)
		{
			PLL2Q_EN(ENABLE);
			Rcc_Toggle_SrcClk(RCC_PLL2, ENABLE);
			while( ! PLL2_STAT);
		}
		RCC->RCC_D3CCIPR |= (spi6pll2q_clk << 28) ;
	}
	else if (inclk == spi6pll3q_clk)
	{
		if( ! PLL3_STAT)
		{
			PLL3Q_EN(ENABLE);
			Rcc_Toggle_SrcClk(RCC_PLL3, ENABLE);
			while( ! PLL3_STAT);
		}
		RCC->RCC_D3CCIPR |= (spi6pll3q_clk << 28) ;
	}
	else if (inclk == spi6hsi_ker_clk)
	{
		Rcc_HsiKerEn();
		RCC->RCC_D3CCIPR |= (spi6hsi_ker_clk << 28) ;
	}
	else if (inclk == spi6csi_ker_clk)
	{
		//enable csi kernel
		RCC->RCC_CR |= ( 1 << 9);
		if( ! CSI_STAT)
		{
			Rcc_Toggle_SrcClk(RCC_CSI, ENABLE);
			while( ! CSI_STAT);
		}
		RCC->RCC_D3CCIPR |= (spi6csi_ker_clk << 28) ;
	}
	else if (inclk == spi6hse_clk)
	{
		if( ! HSE_STAT)
		{
			Rcc_Toggle_SrcClk(RCC_HSE, ENABLE);
			while( ! HSE_STAT);
		}
		RCC->RCC_D3CCIPR |= (spi6hse_clk << 28) ;
	}
	
}

/*------------------------------

*******|||||***** 	RCC SPI REST FUNC *******

------------------------------------
*/
void RccSpi_Rst(Spi_RegDef_t* spi)
{
	if(spi == SPI1)
	{
		RCC->RCC_APB2RSTR &= ~(1 << 12);
		RCC->RCC_APB2RSTR |= (1 << 12);
	}
	else if(spi == SPI2)
	{
		RCC->RCC_APB1LRSTR &= ~(1 << 14);
		RCC->RCC_APB1LRSTR |= (1 << 14);
	}
	else if(spi == SPI3)
	{
		RCC->RCC_APB1LRSTR &= ~(1 << 15);
		RCC->RCC_APB1LRSTR |= (1 << 15);
	}
	else if(spi == SPI4)
	{
		RCC->RCC_APB2RSTR &= ~(1 << 13);
		RCC->RCC_APB2RSTR |= (1 << 13);
	}
	else if(spi == SPI5)
	{
		RCC->RCC_APB2RSTR &= ~(1 << 20);
		RCC->RCC_APB2RSTR |= (1 << 20);
	}
	else if(spi == SPI6)
	{
		RCC->RCC_APB4RSTR &= ~(1 << 5);
		RCC->RCC_APB4RSTR |= (1 << 5);
	}
}

/* ======================
 * * -----||||-----SYSCONFG FUNCTION--------------------
 * */
void Rcc_sysconfClk_init()
{
	RCC->RCC_APB4ENR |= ( 1 << 1);
	RCC->RCC_APB4LPENR |= (1<< 1);
}


/**==================================
 * Other Functions ==================
 * */

/*---------------------------

	************HSI KERNEL ON********** 
	will keep running during Stop mode
	Bit 1 of Rcc_Cr**************

----------------------------*/
void Rcc_HsiKerEn()
{
	RCC->RCC_CR |= (1 << 1);
	while( ! (RCC->RCC_CR >> 1) & 0X1);
}

/*--------------------------------

	*******Toggle Src Clock in RCC_CR **********

----------------------------------*/
void Rcc_Toggle_SrcClk(Rcc_SrcClk inclk, uint8_t onoff)
{
	if( inclk == RCC_HSI)
	{
		if(onoff == ENABLE)
		{
			RCC->RCC_CR |= (1 << 0);
		} else 
		{
			RCC->RCC_CR &= ~(1 << 0);
		}
	}
	else if(inclk == RCC_HSE)
	{
		if(onoff == ENABLE)
		{
			RCC->RCC_CR |= (1 << 16);
		}else 
		{
			RCC->RCC_CR &= ~(1 << 16);
		}
	}
	else if (inclk == RCC_CSI)
	{
		if(onoff == ENABLE)
		{
			RCC->RCC_CR |= (1<< 7);
		} else 
		{
			RCC->RCC_CR &= ~(1 << 7);
		}
	}
	else if (inclk == RCC_PLL1)
	{
		if(onoff == ENABLE)
		{
			RCC->RCC_CR |= (1 << 24);
		} else  
		{
			RCC->RCC_CR &= ~(1<<24);
		}
	}
	else if (inclk == RCC_PLL2)
	{
		if(onoff == ENABLE)
		{
			RCC->RCC_CR |= (1 << 26);
		} else  
		{
			RCC->RCC_CR &= ~(1<<26);
		}
	}
	else if (inclk == RCC_PLL3)
	{
		if(onoff == ENABLE)
		{
			RCC->RCC_CR |= (1 << 28);
		} else  
		{
			RCC->RCC_CR &= ~(1<<28);
		}
	}
}

/*-------------------------------------

	*********RCC INIT FUNC************

	----------------------------------*/
void Rcc_Init()
{
	// enable pwr block to access its reg
	//CANNOT FIND IT IN RCC REG so it on automatically
	//enable syscfg
	RCC->RCC_APB4ENR |= (1 << 1);
	RCC->RCC_APB4LPENR |= (1 << 1);
	//enable kernel hsi running in lowpower mode
	Rcc_HsiKerEn();
	//enable d3 run independent to cpu state or d1, d2 state
	PWR->PWR_CPU1CR |= ( 1 << 11);
	PWR->PWR_CPU2CR |= (1 << 11);
}

/*
	-- ENABLE CLK SRC FOR SPI
	-- DEFAULT PLL CLK IS DISABLED
*/

void Spi123def_clksrc_on(){ //PLL1Q
	if ( ! PLL1_STAT)
	{
		// adding more tweak here - divM, divN, divPQR factor
		PLL1Q_EN(ENABLE);
		Rcc_Toggle_SrcClk(RCC_PLL1, ENABLE);
		while ( ! PLL1_STAT);
	}
}
