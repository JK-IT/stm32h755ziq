/*
 * rcc.h
 *
 *  Created on: Apr 10, 2021
 *      Author: kdg
 */



#ifndef RCC_H
#define RCC_H
#include <stm32h755xx.h>

#define HSI_STAT       ((RCC->RCC_CR >> 0) & 0X1)
#define HSE_STAT       ((RCC->RCC_CR >> 16) & 0X1)
#define CSI_STAT       ((RCC->RCC_CR >> 7) & 0X1)
#define PLL1_STAT      ((RCC->RCC_CR >> 24) & 0X1)
#define PLL2_STAT      ((RCC->RCC_CR >> 26) & 0X1)
#define PLL3_STAT      ((RCC->RCC_CR >> 28) & 0X1)
#define D1CLK_STAT     ((RCC->RCC_CR >> 14) & 0X1)
#define D2CLK_STAT     ((RCC->RCC_CR >> 15) & 0X1)

// ?    Clock Src Enum
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

/**
 * @brief 
 * *    PLL CLK OUTPUT CONFIG
 *      PLL need reference input clock frequency to generate the desired freq
 * if PLL VCOSEL is VCOL then input freq must be < 2 mhz
 * if PLL  VCOSEL is VCOH then input freq must be > 2mhz and < 16mhz
 * by default the VCOSEL IS VCOH , but the input freq is < 2mhz
 * TODO: to make it output properly we should change the input freq to appropriate range
 */
#define PLL1    1
#define PLL2    2
#define PLL3    3

#define PLLSRC_HSI  	0 // default
#define PLLSRC_CSI  	1
#define PLLSRC_HSE  	2
#define PLLSRC_NOCLK  	3

#define PLLSRC_PICKING(x)   ( RCC->RCC_PLLCKSELR |= ((x) << 0) )

//*    Define Input Clk Range
#define RefClk12     0       // 1-2 mhz
#define RefClk24     1       // 2 -4 mhz
#define RefClk48     2       //4-8 mhz
#define RefClk816    3       //8-16 mhz
//*
#define VCO_WIDE_RANGE   	0 // 192 -836 mhz default setting
#define VCO_MED_RANGE   	1 // 150-420 mhz

//*     F(vco) = refClkFre * DivN
// DivN default val is 129 -> Default output of pll = (2 * 129) = 258
void Rcc_PllFreqCfgOutput(uint8_t pllnum, uint8_t vcosel, uint8_t frqrange);

/*
   * Enable R P Q output
    can only be written when pll is disabled
*/
#define PLL1Q_EN(onoff)     ( ((onoff) == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 17)) : (RCC->RCC_PLLCFGR &= ~(1 << 17)) )
#define PLL1P_EN(onoff)     ( ((onoff) == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 16)) : (RCC->RCC_PLLCFGR &= ~(1 << 16)) )
#define PLL1R_EN(onoff)     ( ((onoff) == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 18)) : (RCC->RCC_PLLCFGR &= ~(1 << 18)) )

#define PLL2Q_EN(onoff)     ( ((onoff) == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 20)) : (RCC->RCC_PLLCFGR &= ~(1 << 17)) )
#define PLL2P_EN(onoff)     ( ((onoff) == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 19)) : (RCC->RCC_PLLCFGR &= ~(1 << 16)) )
#define PLL2R_EN(onoff)     ( ((onoff) == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 21)) : (RCC->RCC_PLLCFGR &= ~(1 << 18)) )

#define PLL3Q_EN(onoff)     ( ((onoff) == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 23)) : (RCC->RCC_PLLCFGR &= ~(1 << 17)) )
#define PLL3P_EN(onoff)     ( ((onoff) == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 22)) : (RCC->RCC_PLLCFGR &= ~(1 << 16)) )
#define PLL3R_EN(onoff)     ( ((onoff) == ENABLE)? (RCC->RCC_PLLCFGR |= (1 << 24)) : (RCC->RCC_PLLCFGR &= ~(1 << 18)) )


#pragma region  ======== GPIO SECTION
/*
 * GPIO - RCC SECTION
 * ENABLE GPIO BUS TO ACCESS REGISTER
 * RESET GPIO PERIPHERAL
 */

/* ======================
 * * -----||||-----GPIO FUNCTION--------------------
 * */

//  GPIO BUS CLK ENABLED
void Rcc_gpio_enable(gpio_reg_t* gpio);

// GPIO PERIPHERAL RESET
void Rcc_gpio_reset(gpio_reg_t* gpio);

#pragma endregion


#pragma region ========= SPI SECTION
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
//?     Spi123 Clk src Enum
typedef enum
{
    spi1pll1q_clk,
    spi1pll2p_clk,
    spi1pll3p_clk,
    spi1per_clk = 4
} Spi123_SrcClk;

//?     Spi4 Clk src Enum
typedef enum
{
    spi4def_clk,
    spi4pll2q_clk = 1,
    spi4pll3q_clk,
    spi4hsi_ker_clk,
    spi4csi_ker_clk,
    spi4hse_clk
} Spi45_SrcClk;

//?     Spi6 Clk src Enum
typedef enum
{
    spi6pclk4,
    spi6pll2q_clk,
    spi6pll3q_clk,
    spi6hsi_ker_clk,
    spi6csi_ker_clk,
    spi6hse_clk
} Spi6_SrcClk;



/* ======================
 * * -----||||-----SPI MACRO FUNCTION--------------------
 * */

void RccSpi1_ClkSw(Spi123_SrcClk inclk);
void RccSpi4_ClkSw(Spi45_SrcClk inclk);
void RccSpi6_ClkSw(Spi6_SrcClk inclk);


//-------- DEFAULT CLOCK SRC ENABLING FUNC FOR SPI
// pll clks are off by default
// spi 4 5 6 using per clk(rcc_pclk), which is on after reset
void Spi123def_clksrc_on();

#pragma endregion

#pragma region  =============== SYSCONFIG SECTION
/* ======================
 * * -----||||-----SYSCONFG FUNCTION--------------------
 * */
void Rcc_sysconfClk_init();

#pragma endregion

#pragma region ======== I2C SECTION

//*     Bus Clk Cfg
/**
 * @brief  ENABLE PERIPHERAL BUS IN RCC REGISTER
 *              TO ACCESS I2C REGISTER
 *              ENABLE KERNEL CLOCK  SOURCEAS I2C WILL NEED IT
 *              i2c base clock : apb1 , apb4 only i2c4
 */
void Rcc_I2cBusCfg(uint8_t i2cnum);

void Rcc_I2c4BusCfg();

		//*Kernel clock Enable
/**
 * @brief  RCC_D2CCIP2R -> domain 2 kernel clock src for i2c123
 * 				RCC_D3CCIPR -> domain 3 kernel clock src for i2c4	
*/

#define i2c_pclk1_kerclk   0 //==> default clk, peripheral clk 1 , aka apb1 clk
#define i2c_pll3_r__kerclk   1
#define i2c_hsi_kerclk 2
#define i2c_csi_kerclk 3

#define i2c4_pclk4  0 // ==> default clk, peripheral clk 4, aka apb4 clk

//* set up the speed of the i2c kernel clk src
#define I2C_KERCLK_8MHZ 0
#define I2C_KERCLK_16MHZ    1

// THE KERNEL CLK SRC WILL BE ENABLED WHEN SETTING THE SPEED HERE 
void Rcc_Cfg_i2c_kerclk_speed(uint8_t kerspeed);


//? SET UP I2C CLK SRC  
// Using Pll3 as clk src so we can leave other clk src as default speed
// THIS Is FOR I2C-123
void Rcc_Cfg_i2c_kerclk();

//this is for i2c- 4
void Rcc_Cfg_i2c4_kerclk();

#pragma endregion

#pragma region =============== RCC OTHER FUNCTION
/**
 * *=============== RCC - other function
 *
 * */
void Rcc_HsiKerEn();
void Rcc_Toggle_SrcClk(Rcc_SrcClk inclk, uint8_t onoff);

void Rcc_Init();

#pragma endregion

#endif //RCC_H


