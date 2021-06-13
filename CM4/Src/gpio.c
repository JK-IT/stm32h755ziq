/*
 * gpio.c
 *
 *  Created on: May 9, 2021
 *      Author: kdg
 */

#include "gpio.h"

/**     --GPIO_INIT FUNC --> Gpio_Init
 * Enable Bus clock to access register
 * setup moder register : input, output , alter
 * setup alternative function number
 * setup output type, outspeed
 * set up output speed
 * @param pdev
 */
void Gpio_Init(gpio_dev_t *pdev)
{
    Rcc_gpio_enable(pdev->pGpiox); // bus enable
    //pin mode config
    if ( pdev->Gpio_PinConfig.Gpio_PinMode < 2 )
    {
        // 0: input, 1: output
        // x << y = x * 2^y
    	//reset the bits before setting up, why???
    	// 0b11 | 0b01 = 0b11
        pdev->pGpiox->Moder &=  ~( 0x3 << (pdev->Gpio_PinConfig.Gpio_PinNumber
                <<1));

    	pdev->pGpiox->Moder |=  ( (uint32_t)pdev->Gpio_PinConfig.Gpio_PinMode << (pdev->Gpio_PinConfig.Gpio_PinNumber
    	        <<1));

    }
    else
    {   // 0x2 = alter func
        if ( pdev->Gpio_PinConfig.Gpio_PinMode == 0x2 )
        {
            pdev->pGpiox->Moder &=  ~( 0x3 << (pdev->Gpio_PinConfig.Gpio_PinNumber <<1));

            pdev->pGpiox->Moder |=  ( (uint32_t)pdev->Gpio_PinConfig.Gpio_PinMode << (pdev->Gpio_PinConfig.Gpio_PinNumber  <<1));
            // set function number in alter func register
            pdev->pGpiox->Afr[pdev->Gpio_PinConfig.Gpio_PinNumber / 8] |= ( pdev->Gpio_PinConfig.Gpio_PinAltFunNum << ((pdev->Gpio_PinConfig.Gpio_PinNumber % 8) * 4) );
        }
        else // this will be for analog and interrupt
        {

        }
    }
    // speed
    pdev->pGpiox->Ospeedr &= ~( (uint32_t) 0x3 << (pdev->Gpio_PinConfig.Gpio_PinNumber
            << 1));
    pdev->pGpiox->Ospeedr |= ( (uint32_t) pdev->Gpio_PinConfig.Gpio_PinSpeed << (pdev->Gpio_PinConfig.Gpio_PinNumber << 1));
    //ouput type
    pdev->pGpiox->Otyper |= ( (uint32_t) pdev->Gpio_PinConfig.Gpio_PinOPType << pdev->Gpio_PinConfig.Gpio_PinNumber);

    // pull up, pull down
    pdev->pGpiox->Pupdr &= ~( (uint32_t) 0x3 << (pdev->Gpio_PinConfig
            .Gpio_PinNumber << 1));
    pdev->pGpiox->Pupdr |= ( (uint32_t) pdev->Gpio_PinConfig.Gpio_PinPuPdControl << (pdev->Gpio_PinConfig.Gpio_PinNumber << 1));
}

/**
 * @brief   RESET FUNCTION --> Gpio_Reset
 * @param pGpiox
 */
void Gpio_Reset(gpio_reg_t * pGpiox)
{
    Rcc_gpio_reset(pGpiox);
}

/**
 * @brief   READ DATA FROM A PIN --> Gpio_read_pin
 * @param pgpiox
 * @param pinNUm
 */
uint8_t Gpio_read_pin(gpio_reg_t * pgpiox, uint8_t pinNUm)
{
    return ( (uint8_t) ((pgpiox->Idr >> pinNUm) & 0x1));
}
/**
 * @brief READ DATA FROM A PORT  --> Gpio_read_port
 * @param pgpiox
 * @return
 */
uint16_t Gpio_read_port(gpio_reg_t* pgpiox)
{
    return ( (uint16_t)  (pgpiox->Idr));
}
