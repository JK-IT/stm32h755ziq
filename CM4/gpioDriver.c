/*
 * gpioDriver.c
 *
 *  Created on: Nov 20, 2020
 *      Author: jkgra
 */

#include "gpioDriver.h"

/*
 * param	gpio handle structure
 * description	configure the gpio
 */
void Gpio_Init(Gpio_Handle_t *pGpioHandle)
{
	uint32_t temp = 0; /// temp register

	//enable peripheral clock on that gpio
	Gpio_PeriClkControl(pGpioHandle->pGpiox, ENABLE);

	//1. gpio mode
	if(pGpioHandle->Gpio_PinConfig.Gpio_PinMode <= GPIO_MODE_ANALOG)
	{
		temp = ((uint32_t)pGpioHandle->Gpio_PinConfig.Gpio_PinMode << (2* pGpioHandle->Gpio_PinConfig.Gpio_PinNumber));
		pGpioHandle->pGpiox->Moder &= ~((uint32_t)0x3 << (2* pGpioHandle->Gpio_PinConfig.Gpio_PinNumber)); //clear bit
		pGpioHandle->pGpiox->Moder |= temp; //set bit
		temp = 0;
	} else //extended interrupt  = detects rising/ falling edge of peri/input event
	{
		// enable pin as input mode but also trigger interrupt
		// at reset all pin is set in analog mode
		pGpioHandle->pGpiox->Moder &= ~((uint32_t)0x3 << (2 * pGpioHandle->Gpio_PinConfig.Gpio_PinNumber));

		if(pGpioHandle->Gpio_PinConfig.Gpio_PinMode == GPIO_MODE_IT_FT)
		{
			EXTI->FTSR1 |= (1 << pGpioHandle->Gpio_PinConfig.Gpio_PinNumber);
			//clear the bit in rising edge detection
			EXTI->RTSR1 &= ~(1 << pGpioHandle->Gpio_PinConfig.Gpio_PinNumber);
		}
		else if(pGpioHandle->Gpio_PinConfig.Gpio_PinMode == GPIO_MODE_IT_RT)
		{
			EXTI->RTSR1 |= (1 << pGpioHandle->Gpio_PinConfig.Gpio_PinNumber);
			//clear the bit in falling edge detection
			EXTI->FTSR1 &= ~(1 << pGpioHandle->Gpio_PinConfig.Gpio_PinNumber);
		}
		else if(pGpioHandle->Gpio_PinConfig.Gpio_PinMode == GPIO_MODE_IT_RFT)
		{
			//enable both detecting
			EXTI->FTSR1 |= (1 << pGpioHandle->Gpio_PinConfig.Gpio_PinNumber);
			//clear the bit in rising edge detection
			EXTI->RTSR1 |= (1 << pGpioHandle->Gpio_PinConfig.Gpio_PinNumber);
		}

		//config port selection in syscfg_extireg
		uint8_t temp1 = (pGpioHandle->Gpio_PinConfig.Gpio_PinNumber / 4);
		uint8_t temp2 = (pGpioHandle->Gpio_PinConfig.Gpio_PinNumber % 4);
		uint8_t portcode = GPIO_TO_PORTCODE(pGpioHandle->pGpiox);
		SYSCFG->EXTICR[temp1] &= ~(0xf << (temp2 * 4));
		SYSCFG->EXTICR[temp1] |= (portcode << (temp2 * 4));

		//enable exti interrupt delivery using interrupt mask: 1-unmasked-enable, 0-masked-disable
		EXTI->C2IMR1 |= (1 << pGpioHandle->Gpio_PinConfig.Gpio_PinNumber);
		EXTI->C1IMR1 |= (1 << pGpioHandle->Gpio_PinConfig.Gpio_PinNumber);
	}
	temp = 0;
	//2. speed
	temp = (pGpioHandle->Gpio_PinConfig.Gpio_PinSpeed << (2 * pGpioHandle->Gpio_PinConfig.Gpio_PinNumber));
	pGpioHandle->pGpiox->Ospeedr &= ~((uint32_t)0x3 << (2* pGpioHandle->Gpio_PinConfig.Gpio_PinNumber)); //clear bit
	pGpioHandle->pGpiox->Ospeedr |= temp;

	temp = 0;
	//3. pupd register
	temp = (pGpioHandle->Gpio_PinConfig.Gpio_PinPuPdControl << (2 * pGpioHandle->Gpio_PinConfig.Gpio_PinNumber));
	pGpioHandle->pGpiox->Pupdr &= ~((uint32_t)0x3 << (2* pGpioHandle->Gpio_PinConfig.Gpio_PinNumber)); //clear bit
	pGpioHandle->pGpiox->Pupdr |= temp;

	temp = 0;
	//4.output type
	temp = (pGpioHandle->Gpio_PinConfig.Gpio_PinOPType << pGpioHandle->Gpio_PinConfig.Gpio_PinNumber);
	pGpioHandle->pGpiox->Otyper &= ~((uint32_t)0x3 << (pGpioHandle->Gpio_PinConfig.Gpio_PinNumber)); //clear bit
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
		pGpioHandle->pGpiox->Afr[temp1] |= (pGpioHandle->Gpio_PinConfig.Gpio_PinAltFunNum << (4 * temp2));
	}
}

/*--------------------------------
 * fn	***********PERIPHERAL RESET--------------------
 *
 * BRIEF	this RESET GPIO BLOCK
 * param 1		GPIO PORT
 * return		VOID
 * ----------------------------------
 */

void Gpio_Reset(Gpio_RegDef_t* pGpiox)
{
	RccGpio_Rst(pGpiox);
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
void Gpio_PeriClkControl(Gpio_RegDef_t* pGpiox, uint8_t EnorDi)
{
	RccGpio_ClkCon(pGpiox, EnorDi);
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
 * According to Cortex M4 General Device Guide
 * 	M4 has NVIC_XXX0 - NVIC_XXX7 / total of 8 register for masking interupt
 * 	For other registers, refer to manual
 *
 * return
 */
void Gpio_IrqConfig(uint8_t IrqNum, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{	// set/enable the interrupt number in NVIC table
		if( IrqNum <= 31) // use NVIC_ISER0
		{
			*NVIC_ISER0 |=		(1 << IrqNum);
		}
		else if( IrqNum > 31 && IrqNum < 64) // use NVIC_ISER1 //32-63
		{
			*NVIC_ISER1 |= (1 << (IrqNum % 32));
		}
		else if( IrqNum >= 64 && IrqNum < 96) // use NVIC_ISER2 // 64-95
		{
			*NVIC_ISER2 |= (1 << (IrqNum % 32));
		}
		else if( IrqNum >= 96 && IrqNum < 128) // use NVIC_ISER3 // 96-127
		{
			*NVIC_ISER3 |= (1 << (IrqNum % 32));
		}
		else if( IrqNum >= 128 && IrqNum <= 149) // use NVIC_ISER4
		{
			*NVIC_ISER4 |= (1 << (IrqNum % 32));
		}
	}
	else
	{		//clear  the interrupt number in NVIC table
		if( IrqNum <= 31) // use NVIC_ISER0
		{
			*NVIC_ICER0 &=		~(1 << IrqNum);
		}
		else if( IrqNum > 31 && IrqNum < 64) // use NVIC_ISER1 //32-63
		{
			*NVIC_ICER1 &=		~ (1 << (IrqNum % 32));
		}
		else if( IrqNum >= 64 && IrqNum < 96) // use NVIC_ISER2 // 64-95
		{
			*NVIC_ICER2 &=		~ (1 << (IrqNum % 32));
		}
		else if( IrqNum >= 96 && IrqNum < 128) // use NVIC_ISER3 // 96-127
		{
			*NVIC_ICER3 &=		~ (1 << (IrqNum % 32));
		}
		else if( IrqNum >= 128 && IrqNum <= 149) // use NVIC_ISER4
		{
			*NVIC_ICER4 &=		~ (1 << (IrqNum % 32));
		}
	}

}

/*
 * fn	SET INTERUPT PRIORITY
 *
 * BRIEF
 *
 * param 1
 * param 2
 *
 * return
 */
void Gpio_SetIpr(uint8_t IrqNum, uint32_t IprNum)
{
	uint8_t iprreg = IrqNum / 4;
	uint8_t iprpos = IrqNum % 4;
	uint8_t shift_amount = (8 * iprpos) + (8 - NO_PRI_BITS_IMPLEMENTED);
	IPR->IprTab[iprreg] |= (IprNum << (shift_amount));
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
void Gpio_IrqHandling(uint8_t pinNum)
{
	// clear the exti pending register corresponding to the pin
	if(EXTI->C2PR1 & (1 << pinNum) || EXTI->C1PR1 & (1 << pinNum))
	{
		//clear the pending by writing 1 into the bit, according to stm32 reference manual
		EXTI->C2PR1 |= ( 1 << pinNum);
		EXTI->C1PR1 |= ( 1 << pinNum);

	}
}
