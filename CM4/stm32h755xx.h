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

#define RCC_CR		(uint32_t *)(RCC_BASEADDR + 0x00)
#define RCC_HSICFGR		(uint32_t *)(RCC_BASEADDR + 0x04)
#define RCC_CRRCR		(uint32_t *)(RCC_BASEADDR + 0x08)
#define RCC_CSICFGR		(uint32_t *)(RCC_BASEADDR + 0x0C)
#define RCC_CFGR		(uint32_t *)(RCC_BASEADDR + 0x10)
#define RCC_D1CFGR		(uint32_t *)(RCC_BASEADDR + 0x18)
#define RCC_D2CFGR		(uint32_t *)(RCC_BASEADDR + 0x1C)
#define RCC_D3CFGR		(uint32_t *)(RCC_BASEADDR + 0x20)
#define RCC_PLLCKSELR		(uint32_t *)(RCC_BASEADDR + 0x28)
#define RCC_PLLCFGR		(uint32_t *)(RCC_BASEADDR + 0x2C)
#define RCC_PLL1DIVR		(uint32_t *)(RCC_BASEADDR + 0x30)
#define RCC_PLL1FRACR		(uint32_t *)(RCC_BASEADDR + 0x34)
#define RCC_PLL2DIVR		(uint32_t *)(RCC_BASEADDR + 0x38)
#define RCC_PLL2FRACR		(uint32_t *)(RCC_BASEADDR + 0x3C)
#define RCC_PLL3DIVR		(uint32_t *)(RCC_BASEADDR + 0x40)
#define RCC_D1CCIPR		(uint32_t *)(RCC_BASEADDR + 0x4C)
#define RCC_D2CCIP1R		(uint32_t *)(RCC_BASEADDR + 0x50)
#define RCC_D2CCIP2R		(uint32_t *)(RCC_BASEADDR + 0x54)
#define RCC_D3CCIPR		(uint32_t *)(RCC_BASEADDR + 0x58)
#define RCC_CIER		(uint32_t *)(RCC_BASEADDR + 0x60)
#define RCC_CIFR		(uint32_t *)(RCC_BASEADDR + 0x64)
#define RCC_CICR		(uint32_t *)(RCC_BASEADDR + 0x68)
#define RCC_BDCR		(uint32_t *)(RCC_BASEADDR + 0x70)
#define RCC_CSR		(uint32_t *)(RCC_BASEADDR + 0x74)
#define RCC_AHB3RSTR		(uint32_t *)(RCC_BASEADDR + 0x7C)
#define RCC_AHB1RSTR		(uint32_t *)(RCC_BASEADDR + 0x80)
#define RCC_AHB2RSTR		(uint32_t *)(RCC_BASEADDR + 0x84)
#define RCC_AHB4RSTR		(uint32_t *)(RCC_BASEADDR + 0x88)
#define RCC_APB3RSTR		(uint32_t *)(RCC_BASEADDR + 0x8C)
#define RCC_APB1LRSTR		(uint32_t *)(RCC_BASEADDR + 0x90)
#define RCC_APB1HRSTR		(uint32_t *)(RCC_BASEADDR + 0x94)
#define RCC_APB2RSTR		(uint32_t *)(RCC_BASEADDR + 0x98)
#define RCC_APB4RSTR		(uint32_t *)(RCC_BASEADDR + 0x9C)
#define RCC_GCR		(uint32_t *)(RCC_BASEADDR + 0xA0)
#define RCC_D3AMR		(uint32_t *)(RCC_BASEADDR + 0xA8)
#define RCC_RSR		(uint32_t *)(RCC_BASEADDR + 0xD0)
#define RCC_AHB1ENR		(uint32_t *)(RCC_BASEADDR + 0xD8)
#define RCC_AHB2ENR		(uint32_t *)(RCC_BASEADDR + 0xDC)
#define RCC_AHB4ENR		(uint32_t *)(RCC_BASEADDR + 0xE0)
#define RCC_APB3ENR		(uint32_t *)(RCC_BASEADDR + 0xE4)
#define RCC_APB1LENR		(uint32_t *)(RCC_BASEADDR + 0xE8)
#define RCC_APB1HENR		(uint32_t *)(RCC_BASEADDR + 0xEC)
#define RCC_APB2ENR		(uint32_t *)(RCC_BASEADDR + 0xF0)
#define RCC_APB4ENR		(uint32_t *)(RCC_BASEADDR + 0xF4)
#define RCC_AHB3LPENR		(uint32_t *)(RCC_BASEADDR + 0xFC)
#define RCC_AHB1LPENR		(uint32_t *)(RCC_BASEADDR + 0x100)
#define RCC_AHB2LPENR		(uint32_t *)(RCC_BASEADDR + 0x104)
#define RCC_AHB4LPENR		(uint32_t *)(RCC_BASEADDR + 0x108)
#define RCC_APB3LPENR		(uint32_t *)(RCC_BASEADDR + 0x10C)
#define RCC_APB1LLPENR		(uint32_t *)(RCC_BASEADDR + 0x110)
#define RCC_APB1HLPENR		(uint32_t *)(RCC_BASEADDR + 0x114)
#define RCC_APB2LPENR		(uint32_t *)(RCC_BASEADDR + 0x118)
#define RCC_APB4LPENR		(uint32_t *)(RCC_BASEADDR + 0x11C)

#define RCC_C1_RSR		(uint32_t *)(RCC_BASEADDR + 0x130)
#define RCC_C1_AHB3ENR		(uint32_t *)(RCC_BASEADDR + 0x134)
#define RCC_C1_AHB1ENR		(uint32_t *)(RCC_BASEADDR + 0x138)
#define RCC_C1_AHB2ENR		(uint32_t *)(RCC_BASEADDR + 0x13C)
#define RCC_C1_AHB4ENR		(uint32_t *)(RCC_BASEADDR + 0x140)
#define RCC_C1_APB3ENR		(uint32_t *)(RCC_BASEADDR + 0x144)
#define RCC_C1_APB1LENR		(uint32_t *)(RCC_BASEADDR + 0x148)
#define RCC_C1_APB1HENR		(uint32_t *)(RCC_BASEADDR + 0x14C)
#define RCC_C1_APB2ENR		(uint32_t *)(RCC_BASEADDR + 0x150)
#define RCC_C1_APB4ENR		(uint32_t *)(RCC_BASEADDR + 0x154)
#define RCC_C1_AHB3LPENR		(uint32_t *)(RCC_BASEADDR + 0x15C)
#define RCC_C1_AHB1LPENR		(uint32_t *)(RCC_BASEADDR + 0x160)
#define RCC_C1_AHB2LPENR		(uint32_t *)(RCC_BASEADDR + 0x164)
#define RCC_C1_AHB4LPENR		(uint32_t *)(RCC_BASEADDR + 0x168)
#define RCC_C1_APB3LPENR		(uint32_t *)(RCC_BASEADDR + 0x16C)
#define RCC_C1_APB1LLPENR		(uint32_t *)(RCC_BASEADDR + 0x170)
#define RCC_C1_APB1HLPENR		(uint32_t *)(RCC_BASEADDR + 0x174)
#define RCC_C1_APB2LPENR		(uint32_t *)(RCC_BASEADDR + 0x178)
#define RCC_C1_APB4LPENR		(uint32_t *)(RCC_BASEADDR + 0x17C)

#define RCC_C2_RSR		(uint32_t *)(RCC_BASEADDR + 0x190)
#define RCC_C2_AHB3ENR		(uint32_t *)(RCC_BASEADDR + 0x194)
#define RCC_C2_AHB1ENR		(uint32_t *)(RCC_BASEADDR + 0x198)
#define RCC_C2_AHB2ENR		(uint32_t *)(RCC_BASEADDR + 0x19C)
#define RCC_C2_AHB4ENR		(uint32_t *)(RCC_BASEADDR + 0x1A0)
#define RCC_C2_APB3ENR		(uint32_t *)(RCC_BASEADDR + 0x1A4)
#define RCC_C2_APB1LENR		(uint32_t *)(RCC_BASEADDR + 0x1A8)
#define RCC_C2_APB1HENR		(uint32_t *)(RCC_BASEADDR + 0x1AC)
#define RCC_C2_APB2ENR		(uint32_t *)(RCC_BASEADDR + 0x1B0)
#define RCC_C2_APB4ENR		(uint32_t *)(RCC_BASEADDR + 0x1B4)
#define RCC_C2_AHB3LPENR		(uint32_t *)(RCC_BASEADDR + 0x1BC)
#define RCC_C2_AHB1LPENR		(uint32_t *)(RCC_BASEADDR + 0x1C0)
#define RCC_C2_AHB2LPENR		(uint32_t *)(RCC_BASEADDR + 0x1C4)
#define RCC_C2_AHB4LPENR		(uint32_t *)(RCC_BASEADDR + 0x1C8)
#define RCC_C2_APB3LPENR		(uint32_t *)(RCC_BASEADDR + 0x1CC)
#define RCC_C2_APB1LLPENR		(uint32_t *)(RCC_BASEADDR + 0x1D0)
#define RCC_C2_APB1HLPENR		(uint32_t *)(RCC_BASEADDR + 0x1D4)
#define RCC_C2_APB2LPENR		(uint32_t *)(RCC_BASEADDR + 0x1D8)
#define RCC_C2_APB4LPENR		(uint32_t *)(RCC_BASEADDR + 0x1DC)

/*
 * EXTI register definition
 */

#define RCC_AHB4ENR		(uint32_t *)(RCC_BASEADDR + 0x0e0)
/*
 * Clock enable macro for gpiox aka clock enable for bus that this peri hangs on
 */
#define GPIOA_PCLK_EN()		(*(RCC_AHB4ENR) |= (1 << 0))
#define GPIOB_PCLK_EN()		(*(RCC_AHB4ENR) |= (1 << 1))
#define GPIOC_PCLK_EN()		(*(RCC_AHB4ENR) |= (1 << 2))
#define GPIOD_PCLK_EN()		(*(RCC_AHB4ENR) |= (1 << 3))
#define GPIOE_PCLK_EN()		(*(RCC_AHB4ENR) |= (1 << 4))
#define GPIOF_PCLK_EN()		(*(RCC_AHB4ENR) |= (1 << 5))
#define GPIOG_PCLK_EN()		(*(RCC_AHB4ENR) |= (1 << 6))
#define GPIOH_PCLK_EN()		(*(RCC_AHB4ENR) |= (1 << 7))
#define GPIOI_PCLK_EN()		(*(RCC_AHB4ENR) |= (1 << 8))
#define GPIOJ_PCLK_EN()		(*(RCC_AHB4ENR) |= (1 << 9))
#define GPIOK_PCLK_EN()		(*(RCC_AHB4ENR) |= (1 << 10))

//********* CLOCK DISABLE
#define GPIOA_PCLK_DI()		(*(RCC_AHB4ENR) &= ~(1 << 0))
#define GPIOB_PCLK_DI()		(*(RCC_AHB4ENR) &= ~(1 << 1))
#define GPIOC_PCLK_DI()		(*(RCC_AHB4ENR) &= ~(1 << 2))
#define GPIOD_PCLK_DI()		(*(RCC_AHB4ENR) &= ~(1 << 3))
#define GPIOE_PCLK_DI()		(*(RCC_AHB4ENR) &= ~(1 << 4))
#define GPIOF_PCLK_DI()		(*(RCC_AHB4ENR) &= ~(1 << 5))
#define GPIOG_PCLK_DI()		(*(RCC_AHB4ENR) &= ~(1 << 6))
#define GPIOH_PCLK_DI()		(*(RCC_AHB4ENR) &= ~(1 << 7))
#define GPIOI_PCLK_DI()			(*(RCC_AHB4ENR) &= ~(1 << 8))
#define GPIOJ_PCLK_DI()		(*(RCC_AHB4ENR) &= ~(1 << 9))
#define GPIOK_PCLK_DI()		(*(RCC_AHB4ENR) &= ~(1 << 10))


/*
 * cLOCK ENABLE FOR I2Cx
 */
#define I2C1_PCLK_EN()		(*(RCC_APB1LENR) |= (1 << 21))
#define I2C2_PCLK_EN()		(*(RCC_APB1LENR) |= (1 << 22))
#define I2C3_PCLK_EN()		(*(RCC_APB1LENR) |= (1 << 23))
#define I2C4_PCLK_EN()		(*(RCC_APB4ENR) |= (1 << 7))

//******** CLOCK DISABLE
#define I2C1_PCLK_DI()		(*(RCC_APB1LENR) &= ~(1 << 21))
#define I2C2_PCLK_DI()		(*(RCC_APB1LENR) &= ~(1 << 22))
#define I2C3_PCLK_DI()		(*(RCC_APB1LENR) &= ~(1 << 23))
#define I2C4_PCLK_DI()		(*(RCC_APB4ENR) &= ~(1 << 7))


/*
 * Clock enable for Spix
 */
#define SPI1_PCLK_EN()		(*(RCC_APB2ENR) |= (1 << 12))
#define SPI2_PCLK_EN()		(*(RCC_APB1LENR) |= (1 << 14))
#define SPI3_PCLK_EN()		(*(RCC_APB1LENR) |= (1 << 15))
#define SPI4_PCLK_EN()		(*(RCC_APB2ENR) |= (1 << 13))
#define SPI5_PCLK_EN()		(*(RCC_APB2ENR) |= (1 << 20))
#define SPI6_PCLK_EN()		(*(RCC_APB4ENR) |= (1 << 5))

//********** CLOCK DISABLE
#define SPI1_PCLK_DI()		(*(RCC_APB2ENR) &= ~(1 << 12))
#define SPI2_PCLK_DI()		(*(RCC_APB1LENR) &= ~(1 << 14))
#define SPI3_PCLK_DI()		(*(RCC_APB1LENR) &= ~(1 << 15))
#define SPI4_PCLK_DI()		(*(RCC_APB2ENR) &= ~(1 << 13))
#define SPI5_PCLK_DI()		(*(RCC_APB2ENR) &= ~(1 << 20))
#define SPI6_PCLK_DI()		(*(RCC_APB4ENR) &= ~(1 << 5))


/*
 * Clock enable for Uartx
 */
#define UART4_PCLK_EN()		(*(RCC_APB1LENR) |= (1 << 19))
#define UART5_PCLK_EN()		(*(RCC_APB1LENR) |= (1 << 20))
#define UART7_PCLK_EN()		(*(RCC_APB1LENR) |= (1 << 30))
#define UART8_PCLK_EN()		(*(RCC_APB1LENR) |= (1 << 31))

//****** CLOCK DISABLE
#define UART4_PCLK_DI()		(*(RCC_APB1LENR) &= ~(1 << 19))
#define UART5_PCLK_DI()		(*(RCC_APB1LENR) &= ~(1 << 20))
#define UART7_PCLK_DI()		(*(RCC_APB1LENR) &= ~(1 << 30))
#define UART8_PCLK_DI()		(*(RCC_APB1LENR) &= ~(1 << 31))

/*
 * Clock enable for USartx
 */
#define USART1_PCLK_EN()		(*(RCC_APB2ENR) |= (1 << 4))
#define USART2_PCLK_EN()		(*(RCC_APB1LENR) |= (1 << 17))
#define USART3_PCLK_EN()		(*(RCC_APB1LENR) |= (1 << 18))
#define USART6_PCLK_EN()		(*(RCC_APB2ENR) |= (1 << 5))
//********* CLOCK DISABLE
#define USART1_PCLK_DI()		(*(RCC_APB2ENR) &= ~(1 << 4))
#define USART2_PCLK_DI()		(*(RCC_APB1LENR) &= ~(1 << 17))
#define USART3_PCLK_DI()		(*(RCC_APB1LENR) &= ~(1 << 18))
#define USART6_PCLK_DI()		(*(RCC_APB2ENR) &= ~(1 << 5))


/*
 * Clock enable for syscfg
 */
#define SYSCFG_PCLK_EN()		(*(RCC_APB4ENR) |= (1 << 1))
///**** CLOCK DISABLE
#define SYSCFG_PCLK_DI()		(*(RCC_APB4ENR) &= ~(1 << 1))

/*
 * RESET GPIO MACRO
 */
#define		GPIOA_REG_RST()		do{ (*(RCC_AHB4RSTR) |= (1<<0)); (*(RCC_AHB4RSTR) &= ~(1<<0)); }while(0)
#define		GPIOB_REG_RST()		do{ (*(RCC_AHB4RSTR) |= (1<<1)); (*(RCC_AHB4RSTR) &= ~(1<<1)); }while(0)
#define		GPIOC_REG_RST()		do{ (*(RCC_AHB4RSTR) |= (1<<2)); (*(RCC_AHB4RSTR) &= ~(1<<2)); }while(0)
#define		GPIOD_REG_RST()		do{ (*(RCC_AHB4RSTR) |= (1<<3)); (*(RCC_AHB4RSTR) &= ~(1<<3)); }while(0)
#define		GPIOE_REG_RST()		do{ (*(RCC_AHB4RSTR) |= (1<<4)); (*(RCC_AHB4RSTR) &= ~(1<<4)); }while(0)
#define		GPIOF_REG_RST()		do{ (*(RCC_AHB4RSTR) |= (1<<5)); (*(RCC_AHB4RSTR) &= ~(1<<5)); }while(0)
#define		GPIOG_REG_RST()		do{ (*(RCC_AHB4RSTR) |= (1<<6)); (*(RCC_AHB4RSTR) &= ~(1<<6)); }while(0)
#define		GPIOH_REG_RST()		do{ (*(RCC_AHB4RSTR) |= (1<<7)); (*(RCC_AHB4RSTR) &= ~(1<<7)); }while(0)
#define		GPIOI_REG_RST()		do{ (*(RCC_AHB4RSTR) |= (1<<8)); (*(RCC_AHB4RSTR) &= ~(1<<8)); }while(0)
#define		GPIOJ_REG_RST()		do{ (*(RCC_AHB4RSTR) |= (1<<9)); (*(RCC_AHB4RSTR) &= ~(1<<9)); }while(0)
#define		GPIOK_REG_RST()		do{ (*(RCC_AHB4RSTR) |= (1<<10)); (*(RCC_AHB4RSTR) &= ~(1<<10)); }while(0)


//some generic macros
#define ENABLE 		0x1
#define DISABLE		0x0
#define SET			ENABLE
#define RESET		DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET

#include "gpio_driver.h"

#endif /* INC_STM32H755XX_H_ */
