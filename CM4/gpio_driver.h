/*
 * gpio_driver.h
 *
 *  Created on: Aug 26, 2020
 *      Author: jkgra
 */

#ifndef INC_GPIO_DRIVER_H_
#define INC_GPIO_DRIVER_H_

#include "stm32h755xx.h"
#include "stdint.h"

/*
 * 	PIN CONFIGURATION TYPE
 */
typedef struct {	//contain values to pass into gpio configuration register
	uint8_t Gpio_PinNumber;
	uint8_t Gpio_PinMode;	// POSSIBLE VAL FROM @GPIO MODE
	uint8_t Gpio_PinSpeed;
	uint8_t Gpio_PinPuPdControl;
	uint8_t Gpio_PinOPType;
	uint8_t Gpio_PinAltFunMode;
}Gpio_PinConfig_t;



/*
 * handle structure for gpio pin
 */
typedef struct {

	Gpio_RegDef_t *pGpiox;  //pointer to gpio port(base address) reg the pin belongs to
	Gpio_PinConfig_t Gpio_PinConfig;
} Gpio_Handle_t;

/*
 * @GPIO PIN NUMBER
 */
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3 //0x11
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10	10
#define GPIO_PIN_NO_11	11
#define GPIO_PIN_NO_12	12
#define GPIO_PIN_NO_13	13
#define GPIO_PIN_NO_14	14
#define GPIO_PIN_NO_15	15


/*
 * @GPIO MODE
 */
#define GPIO_MODE_IN		0
#define GPIO_MODE_OUT		1
#define GPIO_MODE_ALTFN		2 //0x10
#define GPIO_MODE_ANALOG		3 //0x11
#define GPIO_MODE_IT_FT		4 //interupt fall edge 0x100
#define GPIO_MODE_IT_RT		5	//interupt rising edge  0x101
#define GPIO_MODE_IT_RFT	6	//interupt rising falling edge 0x110

/*
 * @GPIO OUTPUT TYPE
 */
#define GPIO_OUT_PP	0
#define GPIO_OUT_OP	1

/*
 * @GPIO OUTPUT SPEED
 */
#define GPIO_SPEED_LOW	0
#define GPIO_SPEED_MED	1
#define GPIO_SPEED_FAST	2
#define GPIO_SPEED_HIGH	3

/*
 * @GPIO PULL UP PULL DOWN CONFIG
 */
#define GPIO_NO_PUPD		0
#define GPIO_PIN_PU		1
#define GPIO_PIN_PD		2


/*
 * api supported by the drivers
 */
void Gpio_Init(Gpio_Handle_t *pGpioHandle);
void Gpio_DeInit(Gpio_RegDef_t* pGpiox);

//==============
void Gpio_PeriClkControl(Gpio_RegDef_t* pGpiox, uint8_t EnorDi);

//==============
uint8_t Gpio_ReadFromInputPin(Gpio_RegDef_t* pGpiox, uint8_t pinNum);

uint16_t Gpio_ReadFromInputPort(Gpio_RegDef_t* pGpiox);

void Gpio_WriteToOutputPin(Gpio_RegDef_t* pGpiox, uint8_t pinNum, uint8_t val);

void Gpio_WriteToOutputPort(Gpio_RegDef_t* pGpiox, uint16_t val);

void Gpio_TogglePin(Gpio_RegDef_t* pGpiox, uint8_t pinNum);

//============
void Gpio_IrqConfig(uint8_t IrqNum, uint8_t EnorDi);

void Gpio_SetIpr(uint8_t IrqNum, uint32_t IprNum);

void Gpio_IrqHandling(uint8_t pinNum);




#endif /* INC_GPIO_DRIVER_H_ */
