
#ifndef GPIO_H
#define GPIO_H

#include <stm32h755xx.h>
#include "rcc.h"
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
	uint8_t Gpio_PinAltFunNum;
}gpio_conf_t;

/*
 * handle structure for gpio pin
 */
typedef struct {
	gpio_reg_t *pGpiox;  //pointer to gpio port(base address) reg the pin belongs to
	gpio_conf_t Gpio_PinConfig;
} gpio_dev_t;

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
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15


/*
 * @GPIO MODE
 */
#define GPIO_MODE_IN		0
#define GPIO_MODE_OUT		1
#define GPIO_MODE_ALTFN		2 //0x2
#define GPIO_MODE_ANALOG		3 //0b11
#define GPIO_MODE_IT_FT		4 //interupt fall edge 0b100
#define GPIO_MODE_IT_RT		5	//interupt rising edge  0b101
#define GPIO_MODE_IT_RFT	6	//interupt rising falling edge 0b110

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

/// -----> Init Function
void Gpio_Init(gpio_dev_t *pdev);

/// ---------> Reset Function
void Gpio_Reset(gpio_reg_t* pGpiox);

/// ----------> Read data of a pin
uint8_t Gpio_read_pin(gpio_reg_t* pGpiox, uint8_t pinNum);

/// -----------> Ready data of  a port
uint16_t GGpio_read_port(gpio_reg_t* pgpiox);

/// -----------> writing to a pin

#define Gpio_pin_on(port, pin)  (port->Odr |= (0x1 << pin))

#define Gpio_pin_off(port, pin) (port->Odr &= ~(0x1 << pin))

/// ------------> writing to a port
#define Gpio_write_port(port, val)    ( (port->Odr |= val) )

/// ------------> toggling a pin
#define Gpio_toggle_pin(port, pin)  ( (port->Odr ^= (0x1 << pin)) )

#endif
