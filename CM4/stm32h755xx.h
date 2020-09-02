/*
 * stm32h755xx.h
 *
 *  Created on: Aug 24, 2020
 *      Author: jkgra
 */

#ifndef INC_STM32H755XX_H_
#define INC_STM32H755XX_H_

#include "stdint.h"

#define	__vo	volatile


/*
 * Base address of flash and sram in memory
 */
#define	FLASH_BASEADDR 		(uint32_t) 0x08100000 //for cortex M4
#define	SRAM1_BASEADDR		0x30000000U
#define SRAM2_BASEADDR		0x30020000U
#define	SRAM3_BASEADDR		0x30040000U
	//no ROM access on cortex m4 for this board
#define SRAM 						SRAM1_BASEADDR


/*
 * Base address of AHP & APB bus peripheral
 */

#define	PERIH_BASE		0x40000000U

#define	APB1_BASEADDR 	PERIH_BASE
#define	APB2_BASEADDR	0x40010000U
#define	APB3_BASEADDR	0x50000000U
#define	APB4_BASEADDR	0x58000000U

#define AHB1_BASEADDR	0x40020000U
#define AHB2_BASEADDR	0x48020000U
#define AHB3_BASEADDR	0x51000000U
#define AHB4_BASEADDR	0x58020000U

/*
 * base address of gpio a-k

 */

#define GPIOA_BASEADDR	(AHB4_BASEADDR + 0x0000)
#define GPIOB_BASEADDR	(AHB4_BASEADDR + 0x0400)
#define GPIOC_BASEADDR	(AHB4_BASEADDR + 0x0800)
#define GPIOD_BASEADDR	(AHB4_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR	(AHB4_BASEADDR + 0x1000)
#define GPIOF_BASEADDR	(AHB4_BASEADDR + 0x1400)
#define GPIOG_BASEADDR	(AHB4_BASEADDR + 0x1800)
#define GPIOH_BASEADDR	(AHB4_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR	(AHB4_BASEADDR + 0x2000)
#define GPIOJ_BASEADDR	(AHB4_BASEADDR + 0x2400)
#define GPIOK_BASEADDR	(AHB4_BASEADDR + 0x2800)

#define RCC_BASEADDR	(AHB4_BASEADDR + 0x4400)

/*
 * base address of i2c and uart peri
 */

#define I2C1_BASEADDR	(APB1_BASEADDR + 0x5400)
#define I2C2_BASEADDR	(APB1_BASEADDR + 0x5800)
#define I2C3_BASEADDR	(APB1_BASEADDR + 0x5C00)
#define I2C4_BASEADDR	(APB4_BASEADDR + 0x1C00)

#define UART4_BASEADDR		(APB1_BASEADDR + 0x4C00)
#define UART5_BASEADDR		(APB1_BASEADDR + 0x5000)
#define UART7_BASEADDR		(APB1_BASEADDR + 0x7800)
#define UART8_BASEADDR		(APB1_BASEADDR + 0x7C00)

#define SPI6_BASEADDR	(APB4_BASEADDR + 0x1400)
#define SPI5_BASEADDR	(APB2_BASEADDR + 0x5000)
#define SPI4_BASEADDR	(APB2_BASEADDR + 0x3400)
#define SPI1_BASEADDR	(APB2_BASEADDR + 0x3000)
#define SPI2_BASEADDR	(APB1_BASEADDR + 0x3800)
#define SPI3_BASEADDR	(APB1_BASEADDR + 0x3C00)

#define USART1_BASEADDR	(APB2_BASEADDR + 0x1000)
#define USART6_BASEADDR	(APB2_BASEADDR + 0x1400)
#define USART2_BASEADDR	(APB1_BASEADDR + 0x4400)
#define USART3_BASEADDR	(APB1_BASEADDR + 0x4800)

/*
 * BASE ADDRESS OF EXTI & SYSCFG PERIH
 */
#define EXTI_BASEADDR	(APB4_BASEADDR +0x0000)
#define SYSCFG_BASEADDR	(APB4_BASEADDR +0x0400)

/*
 * CFG REG OF GPIO
 */
typedef struct { //with offset addr of each
	__vo uint32_t Moder;	//0x00
	__vo uint32_t Otyper;	//0x04
	__vo uint32_t Ospeedr;	//0x08
	__vo uint32_t Pupdr;	//0x0c
	__vo uint32_t Idr;	//0x10
	__vo uint32_t Odr;	//0x14
	__vo uint32_t Bsrr;	//0x18
	__vo uint32_t Lckr;	//0x1c
	__vo uint32_t Afr[2]; //0x20 afrl, 0x24 afrh

}	Gpio_RegDef_t;

/*
 * peripheral definition of gpio - typecast to gpio regdef
 */
#define GPIOA		((Gpio_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB		((Gpio_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC		((Gpio_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD		((Gpio_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE		((Gpio_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF		((Gpio_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG		((Gpio_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH		((Gpio_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI		((Gpio_RegDef_t*)GPIOI_BASEADDR)
#define GPIOJ		((Gpio_RegDef_t*)GPIOJ_BASEADDR)
#define GPIOK		((Gpio_RegDef_t*)GPIOK_BASEADDR)

/*
 * peripheral definition register map for RCC
 */

typedef struct {
	__vo uint32_t Cr; //0x000
	__vo uint32_t HsiCfgr; //0x004
	__vo uint32_t Crrcr; //0x008
	__vo uint32_t CsiCfgr; //0x00c
	__vo uint32_t Cfgr; //0x010
	uint32_t RESERVED0; //0x014
	__vo uint32_t D1Cfgr; //0x018
	__vo uint32_t D2Cfgr; //0x01c
	__vo uint32_t D3Cfgr; //0x020
	uint32_t RESERVED1; //0x024
	__vo uint32_t PllCkSelr; //0x028
	__vo uint32_t PllCfgr; //0x02c
	__vo uint32_t Pll1Divr; //0x030
	__vo uint32_t Pll1Fracr; //0x034
	__vo uint32_t Pll2Divr; //0x038
	__vo uint32_t Pll2Fracr; //0x03c
	__vo uint32_t Pll3Divr; //0x040
	__vo uint32_t Pll3Fracr; //0x044
	uint32_t RESERVED2; //0x048
	__vo uint32_t D1Ccipr; //0x04c
	__vo uint32_t D2Ccip1r; //0x050
	__vo uint32_t D2Ccip2r; //0x054
	__vo uint32_t D3Ccipr; //0x058
	uint32_t RESERVED3; //0x05c
	__vo uint32_t Cier; //0x060
	__vo uint32_t Cifr; //0x064
	__vo uint32_t Cicr; //0x068
	uint32_t RESERVED4; //0x06c
	__vo uint32_t Bdcr; //0x070
	__vo uint32_t Csr; //0x074
	uint32_t RESERVED5; //0x078
	__vo uint32_t Ahb3Rstr; //0x07c
	__vo uint32_t Ahb1Rstr; //0x080
	__vo uint32_t Ahb2Rstr; //0x084
	__vo uint32_t Ahb4Rstr; //0x088
	__vo uint32_t Apb3Rstr; //0x08c
	__vo uint32_t Apb1Lrstr; //0x090
	__vo uint32_t Apb1Hrstr; //0x094
	__vo uint32_t Apb2Rstr; //0x098
	__vo uint32_t Apb4Rstr; //0x09c
	__vo uint32_t Gcr; //0x0A0
	uint32_t RESERVED6; //0x0A4
	__vo uint32_t D3Amr; //0x0a8
	uint32_t RESERVED7; //0x0AC - CC
	__vo uint32_t Rsr; //0x0d0
	__vo uint32_t Ahb3Enr; //0x0d4
	__vo uint32_t Ahb1Enr; //0x0d8
	__vo uint32_t Ahb2Enr; //0x0dc
	__vo uint32_t Ahb4Enr; //0x0e0
	__vo uint32_t Apb3Enr; //0x0e4
	__vo uint32_t Apb1Lenr; //0x0e8
	__vo uint32_t Apb1Henr; //0x0ec
	__vo uint32_t Apb2Enr; //0x0f0
	__vo uint32_t Apb4Enr; //0x0f4
	uint32_t RESERVED8; //0x0f8
	__vo uint32_t Ahb3Lpenr; //0x0fc
	__vo uint32_t Ahb1Lpenr; //0x100
	__vo uint32_t Ahb2Lpenr; //0x104
	__vo uint32_t Ahb4Lpenr; //0x108
	__vo uint32_t Apb3Lpenr; //0x10c
	__vo uint32_t Apb1Llpenr; //0x110
	__vo uint32_t Apb1Hlpenr; //0x114
	__vo uint32_t Apb2Lpenr; //0x118
	__vo uint32_t Apb4Lpenr; //0x11c
	uint32_t RESERVED9; //0x120 - 12c
	__vo uint32_t C1_Rsr; //0x130
	__vo uint32_t C1_Ahb3Enr; //0x134
	__vo uint32_t C1_Ahb1Enr; //0x138
	__vo uint32_t C1_Ahb2Enr; //0x13c
	__vo uint32_t C1_Ahb4Enr; //0x140
	__vo uint32_t C1_Apb3Enr; //0x144
	__vo uint32_t C1_Apb1Lenr; //0x148
	__vo uint32_t C1_Apb1Henr; //0x14c
	__vo uint32_t C1_Apb2Enr; //0x150
	__vo uint32_t C1_Apb4Enr; //0x154
	uint32_t RESERVED10; //0x158
	__vo uint32_t C1_Ahb3Lpenr; //0x15c
	__vo uint32_t C1_Ahb1Lpenr; //0x160
	__vo uint32_t C1_Ahb2Lpenr; //0x164
	__vo uint32_t C1_Ahb4Lpenr; //0x168
	__vo uint32_t C1_Apb3Lpenr; //0x16c
	__vo uint32_t C1_Apb1Llpenr; //0x170
	__vo uint32_t C1_Apb1Hlpenr; //0x174
	__vo uint32_t C1_Apb2Lpenr; //0x178
	__vo uint32_t C1_Apb4Lpenr; //0x17c
	uint32_t RESERVED11; //0x180-18c
	__vo uint32_t C2_Rsr; //0x190
	__vo uint32_t C2_Ahb3Enr; //0x194
	__vo uint32_t C2_Ahb1Enr; //0x198
	__vo uint32_t C2_Ahb2Enr; //0x19c
	__vo uint32_t C2_Ahb4Enr; //0x1a0
	__vo uint32_t C2_Apb3Enr; //0x1a4
	__vo uint32_t C2_Apb1Lenr; //0x1a8
	__vo uint32_t C2_Apb1Henr; //0x1ac
	__vo uint32_t C2_Apb2Enr; //0x1b0
	__vo uint32_t C2_Apb4Enr; //0x1b4
	uint32_t RESERVED12; //0x1B8
	__vo uint32_t C2_Ahb3Lpenr; //0x1bc
	__vo uint32_t C2_Ahb1Lpenr; //0x1c0
	__vo uint32_t C2_Ahb2Lpenr; //0x1c4
	__vo uint32_t C2_Ahb4Lpenr; //0x1c8
	__vo uint32_t C2_Apb3Lpenr; //0x1cc
	__vo uint32_t C2_Apb1Llpenr; //0x1d0
	__vo uint32_t C2_Apb1Hlpenr; //0x1d4
	__vo uint32_t C2_Apb2Lpenr; //0x1d8
	__vo uint32_t C2_Apb4Lpenr; //0x1dc
	uint32_t RESERVED13; //0x1e0 - 1fc

} Rcc_RegDef_t;

/*
 * Rcc register definition
 */
//#define RCC		((Rcc_RegDef_t*)RCC_BASEADDR)
#define RCC_AHB4ENR		(uint32_t *)(RCC_BASEADDR + 0x0e0)
/*
 * Clock enable macro for gpiox aka clock enable for bus that this peri hangs on
 */
#define GPIOA_PCLK_EN()		(RCC->Ahb4Enr |= (1 << 0))
#define GPIOB_PCLK_EN()		((RCC->Ahb4Enr) |= (1 << 1))
#define GPIOC_PCLK_EN()		(RCC->Ahb4Enr |= (1 << 2))
#define GPIOD_PCLK_EN()		(RCC->Ahb4Enr |= (1 << 3))
#define GPIOE_PCLK_EN()		(RCC->Ahb4Enr |= (1 << 4))
#define GPIOF_PCLK_EN()		(RCC->Ahb4Enr |= (1 << 5))
#define GPIOG_PCLK_EN()		(RCC->Ahb4Enr |= (1 << 6))
#define GPIOH_PCLK_EN()		(RCC->Ahb4Enr |= (1 << 7))
#define GPIOI_PCLK_EN()		(RCC->Ahb4Enr |= (1 << 8))
#define GPIOJ_PCLK_EN()		(RCC->Ahb4Enr |= (1 << 9))
#define GPIOK_PCLK_EN()		(RCC->Ahb4Enr |= (1 << 10))

//********* CLOCK DISABLE
#define GPIOA_PCLK_DI()		(RCC->Ahb4Enr &= ~(1 << 0))
#define GPIOB_PCLK_DI()		(RCC->Ahb4Enr &= ~(1 << 1))
#define GPIOC_PCLK_DI()		(RCC->Ahb4Enr &= ~(1 << 2))
#define GPIOD_PCLK_DI()		(RCC->Ahb4Enr &= ~(1 << 3))
#define GPIOE_PCLK_DI()		(RCC->Ahb4Enr &= ~(1 << 4))
#define GPIOF_PCLK_DI()		(RCC->Ahb4Enr &= ~(1 << 5))
#define GPIOG_PCLK_DI()		(RCC->Ahb4Enr &= ~(1 << 6))
#define GPIOH_PCLK_DI()		(RCC->Ahb4Enr &= ~(1 << 7))
#define GPIOI_PCLK_DI()		(RCC->Ahb4Enr &= ~(1 << 8))
#define GPIOJ_PCLK_DI()		(RCC->Ahb4Enr &= ~(1 << 9))
#define GPIOK_PCLK_DI()		(RCC->Ahb4Enr &= ~(1 << 10))


/*
 * cLOCK ENABLE FOR I2Cx
 */
#define I2C1_PCLK_EN()		(RCC->Apb1Lenr |= (1<< 21))
#define I2C2_PCLK_EN()		(RCC->Apb1Lenr |= (1<< 22))
#define I2C3_PCLK_EN()		(RCC->Apb1Lenr |= (1<< 23))
#define I2C4_PCLK_EN()		(RCC->Apb4Enr |= (1<< 7))

//******** CLOCK DISABLE
#define I2C1_PCLK_DI()		(RCC->Apb1Lenr &= ~(1<< 21))
#define I2C2_PCLK_DI()		(RCC->Apb1Lenr &= ~(1<< 22))
#define I2C3_PCLK_DI()		(RCC->Apb1Lenr &= ~(1<< 23))
#define I2C4_PCLK_DI()		(RCC->Apb4Enr &= ~(1<< 7))


/*
 * Clock enable for Spix
 */
#define SPI1_PCLK_EN()		(RCC->Apb2Enr |= (1<< 12))
#define SPI2_PCLK_EN()		(RCC->Apb1Lenr |= (1<< 14))
#define SPI3_PCLK_EN()		(RCC->Apb1Lenr |= (1<< 15))
#define SPI4_PCLK_EN()		(RCC->Apb2Enr |= (1<< 13))
#define SPI5_PCLK_EN()		(RCC->Apb2Enr |= (1<< 20))
#define SPI6_PCLK_EN()		(RCC->Apb4Enr |= (1<< 5))

//********** CLOCK DISABLE
#define SPI1_PCLK_DI()		(RCC->Apb2Enr &= ~(1<< 12))
#define SPI2_PCLK_DI()		(RCC->Apb1Lenr &= ~(1<< 14))
#define SPI3_PCLK_DI()		(RCC->Apb1Lenr &= ~(1<< 15))
#define SPI4_PCLK_DI()		(RCC->Apb2Enr &= ~(1<< 13))
#define SPI5_PCLK_DI()		(RCC->Apb2Enr &= ~(1<< 20))
#define SPI6_PCLK_DI()		(RCC->Apb4Enr &= ~(1<< 5))


/*
 * Clock enable for Uartx
 */
#define UART4_PCLK_EN()		(RCC->Apb1Lenr |= (1<< 19))
#define UART5_PCLK_EN()		(RCC->Apb1Lenr |= (1<< 20))
#define UART7_PCLK_EN()		(RCC->Apb1Lenr |= (1<< 30))
#define UART8_PCLK_EN()		(RCC->Apb1Lenr |= (1<< 31))

//****** CLOCK DISABLE
#define UART4_PCLK_DI()		(RCC->Apb1Lenr &= ~(1<< 19))
#define UART5_PCLK_DI()		(RCC->Apb1Lenr  &= ~(1<< 20))
#define UART7_PCLK_DI()		(RCC->Apb1Lenr  &= ~(1<< 30))
#define UART8_PCLK_DI()		(RCC->Apb1Lenr  &= ~(1<< 31))

/*
 * Clock enable for USartx
 */
#define USART1_PCLK_EN()		(RCC->Apb2Enr |= (1<< 4))
#define USART2_PCLK_EN()		(RCC->Apb1Lenr |= (1<< 17))
#define USART3_PCLK_EN()		(RCC->Apb1Lenr |= (1<< 18))
#define USART6_PCLK_EN()		(RCC->Apb2Enr |= (1<< 5))
//********* CLOCK DISABLE
#define USART1_PCLK_DI()		(RCC->Apb2Enr &= ~(1<< 4))
#define USART2_PCLK_DI()		(RCC->Apb1Lenr &= ~(1<< 17))
#define USART3_PCLK_DI()		(RCC->Apb1Lenr &= ~(1<< 18))
#define USART6_PCLK_DI()		(RCC->Apb2Enr &= ~(1<< 5))


/*
 * Clock enable for syscfg
 */
#define SYSCFG_PCLK_EN()		(RCC->Apb4Enr |= (1<< 1))
///**** CLOCK DISABLE
#define SYSCFG_PCLK_DI()		(RCC->Apb4Enr &= ~(1<< 1))

/*
 * RESET GPIO MACRO
 */
#define		GPIOA_REG_RST()		do{ (RCC->Ahb4Rstr |= (1<<0)); (RCC->Ahb4Rstr &= ~(1<<0)); }while(0)
#define		GPIOB_REG_RST()		do{ (RCC->Ahb4Rstr |= (1<<1)); (RCC->Ahb4Rstr &= ~(1<<1)); }while(0)
#define		GPIOC_REG_RST()		do{ (RCC->Ahb4Rstr |= (1<<2)); (RCC->Ahb4Rstr &= ~(1<<2)); }while(0)
#define		GPIOD_REG_RST()		do{ (RCC->Ahb4Rstr |= (1<<3)); (RCC->Ahb4Rstr &= ~(1<<3)); }while(0)
#define		GPIOE_REG_RST()		do{ (RCC->Ahb4Rstr |= (1<<4)); (RCC->Ahb4Rstr &= ~(1<<4)); }while(0)
#define		GPIOF_REG_RST()		do{ (RCC->Ahb4Rstr |= (1<<5)); (RCC->Ahb4Rstr &= ~(1<<5)); }while(0)
#define		GPIOG_REG_RST()		do{ (RCC->Ahb4Rstr |= (1<<6)); (RCC->Ahb4Rstr &= ~(1<<6)); }while(0)
#define		GPIOH_REG_RST()		do{ (RCC->Ahb4Rstr |= (1<<7)); (RCC->Ahb4Rstr &= ~(1<<7)); }while(0)
#define		GPIOI_REG_RST()		do{ (RCC->Ahb4Rstr |= (1<<8)); (RCC->Ahb4Rstr &= ~(1<<8)); }while(0)
#define		GPIOJ_REG_RST()		do{ (RCC->Ahb4Rstr |= (1<<9)); (RCC->Ahb4Rstr &= ~(1<<9)); }while(0)
#define		GPIOK_REG_RST()		do{ (RCC->Ahb4Rstr |= (1<<10)); (RCC->Ahb4Rstr &= ~(1<<10)); }while(0)


//some generic macros
#define ENABLE 		0x1
#define DISABLE		0x0
#define SET			ENABLE
#define RESET		DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET

#include "gpio_driver.h"

#endif /* INC_STM32H755XX_H_ */
