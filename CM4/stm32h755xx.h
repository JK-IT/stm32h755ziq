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
 * Define NVIC Register
 */
// Interrupt Set Enable
#define NVIC_ISER0	((__vo uint32_t*)0xe000e100)
#define NVIC_ISER1	((__vo uint32_t*)0xe000e104)
#define NVIC_ISER2	((__vo uint32_t*)0xe000e108)
#define NVIC_ISER3	((__vo uint32_t*)0xe000e10c)
#define NVIC_ISER4	((__vo uint32_t*)0xe000e110)
#define NVIC_ISER5	((__vo uint32_t*)0xe000e114)
#define NVIC_ISER6	((__vo uint32_t*)0xe000e118)
#define NVIC_ISER7	((__vo uint32_t*)0xe000e11c)

// Interrupt Clear Enable
#define NVIC_ICER0	((__vo uint32_t*)0xe000e180)
#define NVIC_ICER1	((__vo uint32_t*)0xe000e184)
#define NVIC_ICER2	((__vo uint32_t*)0xe000e188)
#define NVIC_ICER3	((__vo uint32_t*)0xe000e18c)
#define NVIC_ICER4	((__vo uint32_t*)0xe000e190)
#define NVIC_ICER5	((__vo uint32_t*)0xe000e194)
#define NVIC_ICER6	((__vo uint32_t*)0xe000e198)
#define NVIC_ICER7	((__vo uint32_t*)0xe000e19c)

//Interrupt Set Pending
#define NVIC_ISPR0	((__vo uint32_t*)0xe000e200)
#define NVIC_ISPR1	((__vo uint32_t*)0xe000e204)
#define NVIC_ISPR2	((__vo uint32_t*)0xe000e208)
#define NVIC_ISPR3	((__vo uint32_t*)0xe000e20c)
#define NVIC_ISPR4	((__vo uint32_t*)0xe000e210)
#define NVIC_ISPR5	((__vo uint32_t*)0xe000e214)
#define NVIC_ISPR6	((__vo uint32_t*)0xe000e218)
#define NVIC_ISPR7	((__vo uint32_t*)0xe000e21c)

//Interrupt Clear Pending
#define NVIC_ICPR0	((__vo uint32_t*)0xe000e280)
#define NVIC_ICPR1	((__vo uint32_t*)0xe000e284)
#define NVIC_ICPR2	((__vo uint32_t*)0xe000e288)
#define NVIC_ICPR3	((__vo uint32_t*)0xe000e28c)
#define NVIC_ICPR4	((__vo uint32_t*)0xe000e290)
#define NVIC_ICPR5	((__vo uint32_t*)0xe000e294)
#define NVIC_ICPR6	((__vo uint32_t*)0xe000e298)
#define NVIC_ICPR7	((__vo uint32_t*)0xe000e29c)

//Interrupt Active Bit
#define NVIC_IABR0	((__vo uint32_t*)0xe000e300)
#define NVIC_IABR1	((__vo uint32_t*)0xe000e304)
#define NVIC_IABR2	((__vo uint32_t*)0xe000e308)
#define NVIC_IABR3	((__vo uint32_t*)0xe000e30c)
#define NVIC_IABR4	((__vo uint32_t*)0xe000e310)
#define NVIC_IABR5	((__vo uint32_t*)0xe000e314)
#define NVIC_IABR6	((__vo uint32_t*)0xe000e318)
#define NVIC_IABR7	((__vo uint32_t*)0xe000e31c)

//Interrupt Priority
/*
 *	stm32h755ziq has 150 irq numbers or 150 interrupts
 *	so need to have 150 IPRs
 *	1 IPR can set priority number for 4 interrupts
 */

typedef struct {
	__vo uint32_t IPR[60];
}Ipr_t;

#define Ipr_BaseAddr	0xe000e400U
#define Ipr		((Ipr_t*)Ipr_BaseAddr)


//Software Trigger Interrupt
#define STIR	((__vo uint32_t*)0xe000ef00)

#define NO_PRI_BITS_IMPLEMENTED		4

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
	BUS AHB4
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

}Gpio_RegDef_t;

/*
 * peripheral definition of gpio - typecast to gpio regdef
 * BUS AHB4
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
 * define gpio base to port code
 */
#define GPIO_TO_PORTCODE(x)		( 	(x == GPIOA) ? 0 : \
													(x == GPIOB) ? 1 : \
													(x == GPIOC) ? 2 : \
													(x == GPIOD) ? 3 : \
													(x == GPIOE) ? 4 : \
													(x == GPIOF) ? 5 : \
													(x == GPIOG) ? 6 : \
													(x == GPIOH) ? 7 : \
													(x == GPIOI) ? 8 : \
													(x == GPIOJ) ? 9 : \
													(x == GPIOK) ? 10 : 0 )
/*
 * peripheral definition register map for RCC
 * BUS AHB4
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
 * BUS APB4 0X58000000
 */
typedef struct {
	__vo uint32_t RTSR1; //0x00
	__vo uint32_t FTSR1; //0x04
	__vo uint32_t SWIER1; //0x08
	__vo uint32_t D3PMR1; //0x0C
	__vo uint32_t D3PCR1L; //0x10
	__vo uint32_t D3PCR1H; //0x14
	__vo uint32_t RESERVED1; //0x18
	__vo uint32_t RESERVED2; //0x1C
	__vo uint32_t RTSR2; //0x20
	__vo uint32_t FTSR2; //0x24
	__vo uint32_t SWIER2; //0x28
	__vo uint32_t D3PMR2; //0x2C
	__vo uint32_t D3PCR2L; //0x30
	__vo uint32_t D3PCR2H; //0x34
	__vo uint32_t RESERVED3; //0x38
	__vo uint32_t RESERVED4; //0x3C
	__vo uint32_t RTSR3; //0x40
	__vo uint32_t FTSR3; //0x44
	__vo uint32_t SWIER3; //0x48
	__vo uint32_t D3PMR3; //0x4C
	__vo uint32_t D3PCR3L; //0x50
	__vo uint32_t D3PCR3H; //0x54
	uint32_t RESERVED5[10];
	//uint32_t RESERVED5; //0x58
	//__vo uint32_t RESERVED6; //0x5C
	//__vo uint32_t RESERVED7; //0x60
	//__vo uint32_t RESERVED8; //0x64
	//__vo uint32_t RESERVED9; //0x68
	//__vo uint32_t RESERVED10; //0x6C
	//__vo uint32_t RESERVED11; //0x70
	//__vo uint32_t RESERVED12; //0x74
	//__vo uint32_t RESERVED13; //0x78
	//uint32_t RESERVED14; //0x7C
	__vo uint32_t C1IMR1; //0x80
	__vo uint32_t C1EMR1; //0x84
	__vo uint32_t C1PR1; //0x88
	uint32_t RESERVED15; //0x8C
	__vo uint32_t C1IMR2; //0x90
	__vo uint32_t C1EMR2; //0x94
	__vo uint32_t C1PR2; //0x98
	uint32_t RESERVED16; //0x9C
	__vo uint32_t C1IMR3; //0xA0
	__vo uint32_t C1EMR3; //0xA4
	__vo uint32_t C1PR3; //0xA8
	uint32_t RESERVED17[5];
	//__vo uint32_t RESERVED17; //0xAC
	//__vo uint32_t RESERVED18; //0xB0
	//__vo uint32_t RESERVED19; //0xB4
	//__vo uint32_t RESERVED20; //0xB8
	//__vo uint32_t RESERVED21; //0xBC
	__vo uint32_t C2IMR1; //0xC0
	__vo uint32_t C2EMR1; //0xC4
	__vo uint32_t C2PR1; //0xC8
	uint32_t RESERVED22; //0xCC
	__vo uint32_t C2IMR2; //0xD0
	__vo uint32_t C2EMR2; //0xD4
	__vo uint32_t C2PR2; //0xD8
	uint32_t RESERVED23; //0xDC
	__vo uint32_t C2IMR3; //0xE0
	__vo uint32_t C2EMR3; //0xE4
	__vo uint32_t C2PR3; //0xE8
	//__vo uint32_t RESERVED22; //0xEC
}Exti_RegDef_t ;
#define EXTI	((Exti_RegDef_t*)EXTI_BASEADDR)

/*
 * Define the IRQ number for EXTI
 */
#define IRQ_NO_EXTI0	6
#define IRQ_NO_EXTI1	7
#define IRQ_NO_EXTI2	8
#define IRQ_NO_EXTI3	9
#define IRQ_NO_EXTI4	10
#define IRQ_NO_EXTI9_5	23
#define IRQ_NO_EXTI15_10 	40

/*
 * Define System Config Register
 */

typedef struct {
	uint32_t RESERVED1; //0x00
	__vo uint32_t PMCR; //0x04
	__vo uint32_t EXTICR[4]; // 0x08 --- 0x14
	__vo uint32_t CFGR; //0x18
	__vo uint32_t CCCSR; //0x20
	__vo uint32_t CCVR; //0x24
	__vo uint32_t CCCR; //0x28
	uint32_t RESERVED2[62]; //0x2c - 0x122
	__vo uint32_t PKGR; //0x124
	uint32_t RESERVED3[118]; //0x128 - 0x2fc
	__vo uint32_t UR[18]; // 0x300 - 0x344
}SysCfg_RegDef_t;

#define SYSCFG				((SysCfg_RegDef_t*)SYSCFG_BASEADDR)
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
