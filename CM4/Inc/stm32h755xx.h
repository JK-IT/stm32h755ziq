/*
 * stm32h755zi.h
 *
 *  Created on: Apr 10, 2021
 *      Author: kdg
 */


#ifndef STM32H755XX_H_
#define STM32H755XX_H_
#include "stdint.h"

#define	__vo	volatile
//some generic macros
#define ENABLE 		0x1
#define DISABLE		0x0
#define SET			ENABLE
#define RESET		DISABLE
#define ON			ENABLE
#define OFF			DISABLE
#define GPIO_PIN_SET		SET
#define GPIO_PIN_RESET		RESET
#define FLAG_SET				SET
#define FLAG_RESET			RESET



/*=========================================
	-------->	BUS BASE ADDRESS <----------
 * Base address of AHP & APB bus peripheral
 * ========================================
 */

#define	PERIH_BASE		0x40000000ul

#define	APB1_BASEADDR 	PERIH_BASE  //D2
#define	APB2_BASEADDR	0x40010000ul //D2
#define	APB3_BASEADDR	0x50000000ul //D1
#define	APB4_BASEADDR	0x58000000ul //D3

#define AHB1_BASEADDR	0x40020000ul //D2
#define AHB2_BASEADDR	0x48020000ul //D2
#define AHB3_BASEADDR	0x51000000ul //D1
#define AHB4_BASEADDR	0x58020000ul //D3


/*=========================================
	-------->	OTHER SYSTEM PERI ADDRESS <----------
 * Base address of other system peri address
 * It is outside the range of peri base address
 * ========================================
 */

//Software Trigger Interrupt
#define STIR	((__vo uint32_t*)0xe000ef00)
#define NO_PRI_BITS_IMPLEMENTED		4

/*
 * Base address of flash and sram in memory
 */
#define	M4_FLASH_BASEADDR 		0x08100000ul //for cortex M4
#define	M7_FLASH_BASEADDR 		0x08000000ul //for cortex M7
#define	SRAM1_BASEADDR		0x30000000u	l	//D2
#define SRAM2_BASEADDR		0x30020000ul	//D2
#define	SRAM3_BASEADDR		0x30040000ul	//D2
	//no ROM access on cortex m4 for this board
#define SRAM 						SRAM1_BASEADDR

//***********************************************

/*
 * -------------base address of i2c
 */

#define I2C1_BASEADDR	(APB1_BASEADDR + 0x5400)
#define I2C2_BASEADDR	(APB1_BASEADDR + 0x5800)
#define I2C3_BASEADDR	(APB1_BASEADDR + 0x5C00)
#define I2C4_BASEADDR	(APB4_BASEADDR + 0x1C00)

//*     REGISTER struct of I2c
typedef struct
{
    /* data */
    __vo uint32_t cr1;  //0x0
    __vo uint32_t cr2;  //0x4
    __vo uint32_t oar1; //0x8
    __vo uint32_t oar2; //0xc
    __vo uint32_t timingr; // 0x10
    __vo uint32_t timeoutr1; //0x14
    __vo uint32_t isr; //0x18
    __vo uint32_t icr; //0x1c
    __vo uint32_t pecr; //0x20
    __vo uint32_t rxdr; //0x24
    __vo uint32_t txdr; //0x28
} I2c_reg_t;

#define I2C1  ( (I2c_reg_t *) I2C1_BASEADDR)
#define I2C2  ( (I2c_reg_t *) I2C2_BASEADDR)
#define I2C3  ( (I2c_reg_t *) I2C3_BASEADDR)
#define I2C4  ( (I2c_reg_t *) I2C4_BASEADDR)

//* --------------END I2C SECTION


#define UART4_BASEADDR		(APB1_BASEADDR + 0x4C00)
#define UART5_BASEADDR		(APB1_BASEADDR + 0x5000)
#define UART7_BASEADDR		(APB1_BASEADDR + 0x7800)
#define UART8_BASEADDR		(APB1_BASEADDR + 0x7C00)


#define USART1_BASEADDR	(APB2_BASEADDR + 0x1000)
#define USART6_BASEADDR	(APB2_BASEADDR + 0x1400)
#define USART2_BASEADDR	(APB1_BASEADDR + 0x4400)
#define USART3_BASEADDR	(APB1_BASEADDR + 0x4800)


/*	=========================
 * ------->   NVIC SECTION <-----------
 * =========================
 * Define NVIC CONTROLLER Register
 */
/*
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
*/
typedef struct
{
	__vo uint32_t ISER[8]; // 0xe000e100 -> 0xe00e11c
	__vo uint32_t reserved1[24]; // 0xe000e120 -> 0xe000e180
	__vo uint32_t ICER[8]; // 0xe000e180 -> 0xe000e19c
	__vo uint32_t reserved2[24]; //0xe000e1a0 -> ex000e200
	__vo uint32_t ISPR[8]; //0xe000e200 -> 0xe000e21c
	__vo uint32_t reserved3[24]; //0xe000e220 -> 0xe000e280
	__vo uint32_t ICPR[8]; //0XE000E280 -> 0XE000E29C
	__vo uint32_t reserved4[24]; //0xe000e2a0 -> 0xe000e300
	__vo uint32_t IABR[8]; //0XE000E300 -> 0XE000E31C
	__vo uint32_t reserved5[56]; //0xe000e320 -> 0xe000e400
	__vo uint8_t IPRIR[240]; //0xe000e400 -> 0xe000e4ef
}NVIC_CONTROL_REG;

#define NVIC_BASEADDR 0xe000e100ul
#define NVIC	((NVIC_CONTROL_REG *)NVIC_BASEADDR)

//Interrupt Priority --MERGING WITH NVIC
/*
cortex m4 supports up to 240 external interrupts
 *	stm32h755ziq has 150 irq numbers or 150 interrupts
 *	so need to have 150 IPRs
 *	1 IPR can set priority number for 4 interrupts
 *  priorty level is 256 aka 8 bits for 1 interrupts
 * but only 4 most significant bit can be used
 */
/*
typedef struct {
	__vo uint8_t IprTab[240];
}Ipr_Reg_t;

#define IPR_BASEADDR	0xe000e400ul
#define IPR		((Ipr_Reg_t*)IPR_BASEADDR)
*/
/*	=========================

 * ------->   GPIO SECTION <-----------

 * =========================
 * base address of gpio a-k
	BUS AHB4 - d3
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

/*
* 	GPIO REGISTER STRUC
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

} gpio_reg_t;


/*
 * peripheral definition of gpio - typecast to gpio regdef
 * BUS AHB4
 */
#define GPIOA		((gpio_reg_t*) GPIOA_BASEADDR)
#define GPIOB		((gpio_reg_t*) GPIOB_BASEADDR)
#define GPIOC		((gpio_reg_t*) GPIOC_BASEADDR)
#define GPIOD		((gpio_reg_t*) GPIOD_BASEADDR)
#define GPIOE		((gpio_reg_t*) GPIOE_BASEADDR)
#define GPIOF		((gpio_reg_t*) GPIOF_BASEADDR)
#define GPIOG		((gpio_reg_t*) GPIOG_BASEADDR)
#define GPIOH		((gpio_reg_t*) GPIOH_BASEADDR)
#define GPIOI		((gpio_reg_t*) GPIOI_BASEADDR)
#define GPIOJ		((gpio_reg_t*) GPIOJ_BASEADDR)
#define GPIOK		((gpio_reg_t*) GPIOK_BASEADDR)


/*
 * define gpio base to port code
 */
#define GPIO_TO_PORTCODE(x)		( 	((x) == GPIOA) ? 0 : \
													((x) == GPIOB) ? 1 : \
													((x) == GPIOC) ? 2 : \
													((x) == GPIOD) ? 3 : \
													((x) == GPIOE) ? 4 : \
													((x) == GPIOF) ? 5 : \
													((x) == GPIOG) ? 6 : \
													((x) == GPIOH) ? 7 : \
													((x) == GPIOI) ? 8 : \
													((x) == GPIOJ) ? 9 : \
													((x) == GPIOK) ? 10 : 0 )





/*  ===========================
 * ----->  SPI SECTION <-------
 * ===========================
 * Define SPI peripheral Register and configuration type
 */

#define SPI6_BASEADDR	(APB4_BASEADDR + 0x1400) //D3
#define SPI5_BASEADDR	(APB2_BASEADDR + 0x5000) //D2
#define SPI4_BASEADDR	(APB2_BASEADDR + 0x3400) //D2
#define SPI1_BASEADDR	(APB2_BASEADDR + 0x3000) //D2
#define SPI2_BASEADDR	(APB1_BASEADDR + 0x3800) //D2
#define SPI3_BASEADDR	(APB1_BASEADDR + 0x3C00) //D2

typedef struct {
    __vo uint32_t SPI2S_CR1; //0X00
    __vo uint32_t SPI_CR2; //0X04
    __vo uint32_t SPI_CFG1; //0X08
    __vo uint32_t SPI_CFG2; //0X0C
    __vo uint32_t SPI2S_IER; //0X10
    __vo uint32_t SPI2S_SR; //0X14
    __vo uint32_t SPI2S_IFCR; //0X18
    __vo uint32_t RESERVED0; //0x1C
    __vo uint32_t SPI2S_TXDR; //0X20
    __vo uint32_t RESERVED1[3]; //0X24-0X2C
    __vo uint32_t SPI2S_RXDR; //0X30
    __vo uint32_t RESERVED2[3]; //0X34-0X3C
    __vo uint32_t SPI_CRCPOLY; //0X40
    __vo uint32_t SPI_TXCRC; //0X44
    __vo uint32_t SPI_RXCRC; //0X48
    __vo uint32_t SPI_UDRDR; //0X4C
    __vo uint32_t SPI_I2SCFGR; //0X50
}Spi_RegDef_t;

#define SPI1 		((Spi_RegDef_t*) SPI1_BASEADDR)
#define SPI2	    ((Spi_RegDef_t*) SPI2_BASEADDR)
#define SPI3	    ((Spi_RegDef_t*) SPI3_BASEADDR)
#define SPI4	    ((Spi_RegDef_t*) SPI4_BASEADDR)
#define SPI5	    ((Spi_RegDef_t*) SPI5_BASEADDR)
#define SPI6	    ((Spi_RegDef_t*) SPI6_BASEADDR)




/*  ===========================
 * ----->  PWR SECTION <-------
 * ===========================
 * Define PWR peripheral Register and configuration type
 */
#define PWR_BASEADDR 	(AHB4_BASEADDR + 0x4800)

typedef struct {
	__vo uint32_t PWR_CR1; //0X00
	__vo uint32_t PWR_CSR1; //0X04
	__vo uint32_t PWR_CR2; //0X08
	__vo uint32_t PWR_CR3; //0X0C
	__vo uint32_t PWR_CPU1CR; //0X10
	__vo uint32_t PWR_CPU2CR; //0X14
	__vo uint32_t PWR_D3CR; //0X18
	__vo uint32_t RESERVED; //0X1C
	__vo uint32_t PWR_WKUPCR; //0X20
	__vo uint32_t PWR_WKUPFR; //0X24
	__vo uint32_t PWR_WKUPEPR; //0X28
} Pwr_Reg_t;

#define PWR		( (Pwr_Reg_t*) PWR_BASEADDR)



/*  ===========================
 * ----->  RCC SECTION <-------
 * ===========================
 * Define RCC peripheral Register and configuration type
 */

#define RCC_BASEADDR	(AHB4_BASEADDR + 0x4400)

typedef struct {
	__vo uint32_t RCC_CR; //0X000
	__vo uint32_t  RCC_HSICFGR; //0X004
	__vo uint32_t  RCC_CRRCR; //0X008
	__vo uint32_t  RCC_CSICFGR; //0X00C

	__vo uint32_t RCC_CFGR	;// 0x10)
	__vo uint32_t reserved0	;// 0x14)
	__vo uint32_t RCC_D1CFGR	;//0x18)
	__vo uint32_t RCC_D2CFGR		;//0x1C)
	__vo uint32_t RCC_D3CFGR		;//0x20)
	__vo uint32_t reserved1	;// 0x24)
	__vo uint32_t RCC_PLLCKSELR		;//0x28)
	__vo uint32_t RCC_PLLCFGR		;//0x2C)
	__vo uint32_t RCC_PLL1DIVR		;//0x30)
	__vo uint32_t RCC_PLL1FRACR		;//0x34)
	__vo uint32_t RCC_PLL2DIVR		;//0x38)
	__vo uint32_t RCC_PLL2FRACR		;//0x3C)
	__vo uint32_t RCC_PLL3DIVR		;//0x40)
	__vo uint32_t RCC_PLL3FRACR		;//0x44)
	__vo uint32_t reserved2	;// 0x48)
	__vo uint32_t RCC_D1CCIPR		;//0x4C)
	__vo uint32_t RCC_D2CCIP1R		;//0x50)
	__vo uint32_t RCC_D2CCIP2R		;//0x54)
	__vo uint32_t RCC_D3CCIPR		;//0x58)
	__vo uint32_t reserved3	;// 0x5C)
	__vo uint32_t RCC_CIER		;//0x60)
	__vo uint32_t RCC_CIFR		;//0x64)
	__vo uint32_t RCC_CICR		;//0x68)
	__vo uint32_t reserved4	;// 0x6C)
	__vo uint32_t RCC_BDCR		;//0x70)
	__vo uint32_t RCC_CSR		;//0x74)
	__vo uint32_t reserved5	;// 0x78)
	__vo uint32_t RCC_AHB3RSTR		;//0x7C)
	__vo uint32_t RCC_AHB1RSTR		;//0x80)
	__vo uint32_t RCC_AHB2RSTR		;//0x84)
	__vo uint32_t RCC_AHB4RSTR		;//0x88)
	__vo uint32_t RCC_APB3RSTR		;//0x8C)
	__vo uint32_t RCC_APB1LRSTR		;//0x90)
	__vo uint32_t RCC_APB1HRSTR		;//0x94)
	__vo uint32_t RCC_APB2RSTR		;//0x98)
	__vo uint32_t RCC_APB4RSTR		;//0x9C)
	__vo uint32_t RCC_GCR		;//0xA0)
	__vo uint32_t reserved6	;// 0xA4)
	__vo uint32_t RCC_D3AMR		;//0xA8)
	__vo uint32_t reserved7[9]	;// 0xAC - CC)
	__vo uint32_t RCC_RSR		;//0xD0)
	__vo uint32_t RCC_AHB3ENR		;//0xD4)
	__vo uint32_t RCC_AHB1ENR		;//0xD8)
	__vo uint32_t RCC_AHB2ENR		;//0xDC)
	__vo uint32_t RCC_AHB4ENR		;//0xE0)
	__vo uint32_t RCC_APB3ENR		;//0xE4)
	__vo uint32_t RCC_APB1LENR		;//0xE8)
	__vo uint32_t RCC_APB1HENR		;//0xEC)
	__vo uint32_t RCC_APB2ENR		;//0xF0)
	__vo uint32_t RCC_APB4ENR		;//0xF4)
	__vo uint32_t reserved8	;// 0xF8)
	__vo uint32_t RCC_AHB3LPENR		;//0xFC)
	__vo uint32_t RCC_AHB1LPENR		;//0x100)
	__vo uint32_t RCC_AHB2LPENR		;//0x104)
	__vo uint32_t RCC_AHB4LPENR		;//0x108)
	__vo uint32_t RCC_APB3LPENR		;//0x10C)
	__vo uint32_t RCC_APB1LLPENR		;//0x110)
	__vo uint32_t RCC_APB1HLPENR		;//0x114)
	__vo uint32_t RCC_APB2LPENR		;//0x118)
	__vo uint32_t RCC_APB4LPENR		;//0x11C)
	__vo uint32_t reserved9[4]	;// 0x120 - 12C)
	__vo uint32_t RCC_C1_RSR		;//0x130)
	__vo uint32_t RCC_C1_AHB3ENR		;//0x134)
	__vo uint32_t RCC_C1_AHB1ENR		;//0x138)
	__vo uint32_t RCC_C1_AHB2ENR		;//0x13C)
	__vo uint32_t RCC_C1_AHB4ENR		;//0x140)
	__vo uint32_t RCC_C1_APB3ENR		;//0x144)
	__vo uint32_t RCC_C1_APB1LENR		;//0x148)
	__vo uint32_t RCC_C1_APB1HENR		;//0x14C)
	__vo uint32_t RCC_C1_APB2ENR		;//0x150)
	__vo uint32_t RCC_C1_APB4ENR		;//0x154)
	__vo uint32_t reserved10	;// 0x158)
	__vo uint32_t RCC_C1_AHB3LPENR		;//0x15C)
	__vo uint32_t RCC_C1_AHB1LPENR		;//0x160)
	__vo uint32_t RCC_C1_AHB2LPENR		;//0x164)
	__vo uint32_t RCC_C1_AHB4LPENR		;//0x168)
	__vo uint32_t RCC_C1_APB3LPENR		;//0x16C)
	__vo uint32_t RCC_C1_APB1LLPENR		;//0x170)
	__vo uint32_t RCC_C1_APB1HLPENR		;//0x174)
	__vo uint32_t RCC_C1_APB2LPENR		;//0x178)
	__vo uint32_t RCC_C1_APB4LPENR		;//0x17C)
	__vo uint32_t reserved11[3]	;// 0x180-18C)
	__vo uint32_t RCC_C2_RSR		;//0x190)
	__vo uint32_t RCC_C2_AHB3ENR		;//0x194)
	__vo uint32_t RCC_C2_AHB1ENR		;//0x198)
	__vo uint32_t RCC_C2_AHB2ENR		;//0x19C)
	__vo uint32_t RCC_C2_AHB4ENR		;//0x1A0)
	__vo uint32_t RCC_C2_APB3ENR		;//0x1A4)
	__vo uint32_t RCC_C2_APB1LENR		;//0x1A8)
	__vo uint32_t RCC_C2_APB1HENR		;//0x1AC)
	__vo uint32_t RCC_C2_APB2ENR		;//0x1B0)
	__vo uint32_t RCC_C2_APB4ENR		;//0x1B4)
	__vo uint32_t reserved12	;// 0x1B8)
	__vo uint32_t RCC_C2_AHB3LPENR		;//0x1BC)
	__vo uint32_t RCC_C2_AHB1LPENR		;//0x1C0)
	__vo uint32_t RCC_C2_AHB2LPENR		;//0x1C4)
	__vo uint32_t RCC_C2_AHB4LPENR		;//0x1C8)
	__vo uint32_t RCC_C2_APB3LPENR		;//0x1CC)
	__vo uint32_t RCC_C2_APB1LLPENR		;//0x1D0)
	__vo uint32_t RCC_C2_APB1HLPENR		;//0x1D4)
	__vo uint32_t RCC_C2_APB2LPENR		;//0x1D8)
	__vo uint32_t RCC_C2_APB4LPENR		;//0x1DC)
	__vo uint32_t reserved13[8]	;// 0x1E0 - 1FC)

} Rcc_RegDef_t ;

#define RCC		((Rcc_RegDef_t * )RCC_BASEADDR)

/*  ===========================
 * ----->  EXTI SECTION <-------
 * ===========================
 * Define EXTI peripheral Register and configuration type
 */

#define EXTI_BASEADDR	(APB4_BASEADDR +0x0000)
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

#define EXTI 	((Exti_RegDef_t*)EXTI_BASEADDR)



/*  ===========================
 * ----->  SYSCFG SECTION <-------
 * ===========================
 * Define SYSCFG peripheral Register and configuration type
 */

#define SYSCFG_BASEADDR	(APB4_BASEADDR +0x0400)
typedef struct {
	uint32_t RESERVED1; //0x00
	__vo uint32_t PMCR; //0x04
	__vo uint32_t EXTICR[4]; // 0x08 --- 0x14
	__vo uint32_t CFGR; //0x18  ...
	__vo uint32_t CCCSR; //0x20
	__vo uint32_t CCVR; //0x24
	__vo uint32_t CCCR; //0x28
	uint32_t RESERVED2[62]; //0x2c - 0x122
	__vo uint32_t PKGR; //0x124
	uint32_t RESERVED3[118]; //0x128 - 0x2fc
	__vo uint32_t UR[18]; // 0x300 - 0x344
}SysCfg_RegDef_t;

#define SYSCFG				((SysCfg_RegDef_t*)SYSCFG_BASEADDR)


#endif /* STM32H755XX_H_ */

#include "kommon.h"
