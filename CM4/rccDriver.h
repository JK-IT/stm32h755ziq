/*
 * rccDriver.h
 *
 *  Created on: Nov 10, 2020
 *      Author: jkgra
 */

#ifndef RCCDRIVER_H_
#define RCCDRIVER_H_

#include <stm32h755xx.h>

#define HSI_STAT       ((RCC->RCC_CR >> 0) & 0X1)
#define HSE_STAT       ((RCC->RCC_CR >> 16) & 0X1)
#define CSI_STAT       ((RCC->RCC_CR >> 7) & 0X1)
#define PLL1_STAT       ((RCC->RCC_CR >> 24) & 0X1)
#define PLL2_STAT       ((RCC->RCC_CR >> 26) & 0X1)
#define PLL3_STAT       ((RCC->RCC_CR >> 28) & 0X1)
#define D1CLK_STAT       ((RCC->RCC_CR >> 14) & 0X1)
#define D2CLK_STAT       ((RCC->RCC_CR >> 15) & 0X1)
/*
    Enable R P Q output
    can only be written when pll is disabled
*/
#define PLL1Q_EN(onoff)     ( (onoff == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 17)) : (RCC->RCC_PLLCFGR &= ~(1 << 17)) )
#define PLL1P_EN(onoff)     ( (onoff == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 16)) : (RCC->RCC_PLLCFGR &= ~(1 << 16)) )
#define PLL1R_EN(onoff)     ( (onoff == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 18)) : (RCC->RCC_PLLCFGR &= ~(1 << 18)) )

#define PLL2Q_EN(onoff)     ( (onoff == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 20)) : (RCC->RCC_PLLCFGR &= ~(1 << 17)) )
#define PLL2P_EN(onoff)     ( (onoff == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 19)) : (RCC->RCC_PLLCFGR &= ~(1 << 16)) )
#define PLL2R_EN(onoff)     ( (onoff == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 21)) : (RCC->RCC_PLLCFGR &= ~(1 << 18)) )

#define PLL3Q_EN(onoff)     ( (onoff == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 23)) : (RCC->RCC_PLLCFGR &= ~(1 << 17)) )
#define PLL3P_EN(onoff)     ( (onoff == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 22)) : (RCC->RCC_PLLCFGR &= ~(1 << 16)) )
#define PLL3R_EN(onoff)     ( (onoff == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 24)) : (RCC->RCC_PLLCFGR &= ~(1 << 18)) )

typedef enum {
    RCC_HSI,
    RCC_CSI,
    RCC_HSE,
    RCC_LSI,
    RCC_LSE,
    RCC_PLL1,
    RCC_PLL2,
    RCC_PLL3
} Rcc_SrcClk;

typedef enum 
{
    spi1pll1q_clk,
    spi1pll2p_clk,
    spi1pll3p_clk,
    spi1per_clk = 4
} Spi123_SrcClk;

typedef enum 
{
    spi4def_clk,
    spi4pll2q_clk = 1,
    spi4pll3q_clk,
    spi4hsi_ker_clk,
    spi4csi_ker_clk,
    spi4hse_clk
} Spi45_SrcClk;

typedef enum
{
    spi6pclk4,
    spi6pll2q_clk,
    spi6pll3q_clk,
    spi6hsi_ker_clk,
    spi6csi_ker_clk,
    spi6hse_clk
} Spi6_SrcClk;

/*
 * GPIO - RCC SECTION
 */

/* ======================
 * * -----||||-----GPIO MACRO FUNCTION--------------------
 * */


void RccGpio_ClkCon(Gpio_RegDef_t * gpio, uint8_t endi);

void RccGpio_Rst(Gpio_RegDef_t * gpio);


/*
 * SPI -RCC SECTION
 */
// DEFAULT HSI CLK : 64 MHZ
/*
    CALCULATE CLK SRC FROM PLL
    pll = ((pllsrc / divm) * divn ) / div(qpr)
            | = frefclk  |
          |       = fvco clk      |

     fvco = divn * fref, when frac is not enabled
*/

/* ======================
 * * -----||||-----SPI MACRO FUNCTION--------------------
 * */

void RccSpi_Init(Spi_RegDef_t* spi);
void RccSpi_Rst(Spi_RegDef_t* spi);
void RccSpi1_ClkSw(Spi123_SrcClk inclk);
void RccSpi4_ClkSw(Spi45_SrcClk inclk);
void RccSpi6_ClkSw(Spi6_SrcClk inclk);


//-------- DEFAULT CLOCK SRC ENABLING FUNC FOR SPI
// pll clks are off by default
// spi 4 5 6 using per clk(rcc_pclk), which is on after reset
void Spi123def_clksrc_on();



/**
 * RCC - other function
 * 
 * */
void Rcc_HsiKerEn();
void Rcc_Toggle_SrcClk(Rcc_SrcClk inclk, uint8_t onoff);

void Rcc_Init();
#endif /* RCCDRIVER_H_ */
