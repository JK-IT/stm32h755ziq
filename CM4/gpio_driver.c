/*
 * gpio_driver.c
 *
 *  Created on: Aug 26, 2020
 *      Author: jkgra
 */


#include "gpio_driver.h"

/*
 * param	gpio handle structure
 * description	configure the gpio
 */
void Gpio_Init(Gpio_Handle_t *pGpioHandle)
{
	uint32_t temp = 0; /// temp register

	//1. gpio mode
	if(pGpioHandle->Gpio_PinConfig.Gpio_PinMode <= GPIO_MODE_ANALOG)
	{
		temp = (pGpioHandle->Gpio_PinConfig.Gpio_PinMode << (2* pGpioHandle->Gpio_PinConfig.Gpio_PinNumber));
		pGpioHandle->pGpiox->Moder &= ~(0x3 << (2* pGpioHandle->Gpio_PinConfig.Gpio_PinNumber)); //clear bit
		pGpioHandle->pGpiox->Moder |= temp; //set bit
		temp = 0;
	} else
	{

	}
	temp = 0;
	//2. speed
	temp = (pGpioHandle->Gpio_PinConfig.Gpio_PinSpeed << (2 * pGpioHandle->Gpio_PinConfig.Gpio_PinNumber));
	pGpioHandle->pGpiox->Ospeedr &= ~(0x3 << (2* pGpioHandle->Gpio_PinConfig.Gpio_PinNumber)); //clear bit
	pGpioHandle->pGpiox->Ospeedr |= temp;

	temp = 0;
	//3. pupd register
	temp = (pGpioHandle->Gpio_PinConfig.Gpio_PinPuPdControl << (2 * pGpioHandle->Gpio_PinConfig.Gpio_PinNumber));
	pGpioHandle->pGpiox->Pupdr &= ~(0x3 << (2* pGpioHandle->Gpio_PinConfig.Gpio_PinNumber)); //clear bit
	pGpioHandle->pGpiox->Pupdr |= temp;

	temp = 0;
	//4.output type
	temp = (pGpioHandle->Gpio_PinConfig.Gpio_PinOPType << pGpioHandle->Gpio_PinConfig.Gpio_PinNumber);
	pGpioHandle->pGpiox->Otyper &= ~(0x3 << (pGpioHandle->Gpio_PinConfig.Gpio_PinNumber)); //clear bit
	pGpioHandle->pGpiox->Otyper |= temp;

	temp =0;
	//5. alt functionality
	if(pGpioHandle->Gpio_PinConfig.Gpio_PinMode == GPIO_MODE_ALTFN)
	{
		/* limit number in a range
		 * num = (rand() % (upper – lower + 1)) + lower
			So, for 0-65:

			rand() % (65 + 1 - 0) + 0
		 */
		uint8_t temp1, temp2;
		temp1 = pGpioHandle->Gpio_PinConfig.Gpio_PinNumber / 8;
		temp2 = pGpioHandle->Gpio_PinConfig.Gpio_PinNumber % 8;
		pGpioHandle->pGpiox->Afr[temp1] &= ~(0xf << (4 * temp2)); //clear bit
		pGpioHandle->pGpiox->Afr[temp1] |= (pGpioHandle->Gpio_PinConfig.Gpio_PinAltFunMode << (4 * temp2));
	}
}



void Gpio_DeInit(Gpio_RegDef_t* pGpiox)
{
	if(pGpiox == GPIOA){
		GPIOA_REG_RST();
	}
	else if(pGpiox == GPIOB){
		GPIOB_REG_RST();
	}
	else if(pGpiox == GPIOC){
			GPIOC_REG_RST();
	}
	else if(pGpiox == GPIOD){
			GPIOD_REG_RST();
	}
	else if(pGpiox == GPIOE){
			GPIOE_REG_RST();
		}
	else if(pGpiox == GPIOF){
			GPIOF_REG_RST();
		}
	else if(pGpiox == GPIOG){
			GPIOG_REG_RST();
		}
	else if(pGpiox == GPIOH){
			GPIOH_REG_RST();
		}
	else if(pGpiox == GPIOI){
			GPIOI_REG_RST();
		}
	else if(pGpiox == GPIOJ){
			GPIOJ_REG_RST();
		}
	else if(pGpiox == GPIOK){
			GPIOK_REG_RST();
		}

}

//==============
/*
 * fn	PERIPHERAL CLOCK CONTROL
 *
 * BRIEF	this enable or disable peripheral clock
 *
 * param 1		GPIO PORT
 * param 2		ENABLE OR DISABLE
 *
 * return		VOID
 */
void Gpio_PeriClkControl(Gpio_RegDef_t* pGpiox, uint8_t EnorDi){

	if(EnorDi == ENABLE)
	{
		if(pGpiox == GPIOA){
			GPIOA_PCLK_EN();
		}
		else if(pGpiox == GPIOB){
			//GPIOB_PCLK_EN();
			//uint32_t val = 0x1 << 1;
			//uint32_t reg = RCC->Ahb4Enr;
			//(RCC->Ahb4Enr |= (0x1 << 1));
			GPIOB_PCLK_EN();
		}
		else if(pGpiox == GPIOC){
			GPIOC_PCLK_EN();
		}
		else if(pGpiox == GPIOD){
			GPIOD_PCLK_EN();
		}
		else if(pGpiox == GPIOE){
			GPIOE_PCLK_EN();
		}
		else if(pGpiox == GPIOF){
			GPIOF_PCLK_EN();
		}
		else if(pGpiox == GPIOG){
			GPIOG_PCLK_EN();
		}
		else if(pGpiox == GPIOH){
			GPIOH_PCLK_EN();
		}
		else if(pGpiox == GPIOI){
			GPIOI_PCLK_EN();
		}
		else if(pGpiox == GPIOJ){
			GPIOJ_PCLK_EN();
		}
		else if(pGpiox == GPIOK){
			GPIOK_PCLK_EN();
		}
	} else {
		if(pGpiox == GPIOA){
			GPIOA_PCLK_DI();
		}
		else if(pGpiox == GPIOB){
			GPIOB_PCLK_DI();
		}
		else if(pGpiox == GPIOC){
			GPIOC_PCLK_DI();
		}
		else if(pGpiox == GPIOD){
			GPIOD_PCLK_DI();
		}
		else if(pGpiox == GPIOE){
			GPIOE_PCLK_DI();
		}
		else if(pGpiox == GPIOF){
			GPIOF_PCLK_DI();
		}
		else if(pGpiox == GPIOG){
			GPIOG_PCLK_DI();
		}
		else if(pGpiox == GPIOH){
			GPIOH_PCLK_DI();
		}
		else if(pGpiox == GPIOI){
			GPIOI_PCLK_DI();
		}
		else if(pGpiox == GPIOJ){
			GPIOJ_PCLK_DI();
		}
		else if(pGpiox == GPIOK){
			GPIOK_PCLK_DI();
		}
	}

}

//==============
//==============
/*
 * fn	READ FROM PIN
 *
 * BRIEF
 *
 * param 1
 * param 2
 *
 * return
 */
uint8_t Gpio_ReadFromInputPin(Gpio_RegDef_t* pGpiox, uint8_t pinNum)
{
	uint8_t val;
	val = (uint8_t)((pGpiox->Idr >> pinNum) & 0x00000001);
	return val;
}
/*
 * fn	READ FROM PORT
 *
 * BRIEF
 *
 * param 1
 * param 2
 *
 * return
 */
uint16_t Gpio_ReadFromInputPort(Gpio_RegDef_t* pGpiox)
{
	uint16_t val;
	val = (uint16_t)(pGpiox->Idr);
	return val;
}
/*
 * fn	WRITE TO PIN
 *
 * BRIEF
 *
 * param 1
 * param 2
 *
 * return
 */
void Gpio_WriteToOutputPin(Gpio_RegDef_t* pGpiox, uint8_t pinNum, uint8_t val)
{
	if(val == GPIO_PIN_SET){
		pGpiox->Odr |= (1 << pinNum);
	} else {
		pGpiox->Odr &= ~(1 << pinNum);
	}
}
/*
 * fn	WRITE TO PORT
 *
 * BRIEF
 *
 * param 1
 * param 2
 *
 * return
 */
void Gpio_WriteToOutputPort(Gpio_RegDef_t* pGpiox, uint16_t val)
{
	pGpiox->Odr = val;
}
/*
 * fn	TOGGLE PIN
 *
 * BRIEF
 *
 * param 1
 * param 2
 *
 * return
 */
void Gpio_TogglePin(Gpio_RegDef_t* pGpiox, uint8_t pinNum)
{
	pGpiox->Odr ^= (1 << pinNum);
}

//============
/*
 * fn	INTERUPT CONFIG
 *
 * BRIEF
 *
 * param 1
 * param 2
 *
 * return
 */
void Gpio_IrqConfig(uint8_t IrqNum, uint8_t IrqPriority, uint8_t EnorDi)
{

}
/*
 * fn	INTERUPT HANDLING
 *
 * BRIEF
 *
 * param 1
 * param 2
 *
 * return
 */
void Gpio_IrqHandling(uint8_t pinNum);
