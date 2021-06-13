/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stm32h755xx.h>
#include "rcc.h"
#include "string.h"
//#include "kommon.h"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
void delay(void);


// enable gpio with i2c function
void I2c1Gpio()
{
    // enable gpio B as i2c1 -alter func 4
    gpio_dev_t  dev;
    dev.pGpiox = GPIOB;

    dev.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_HIGH;
    dev.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_OP; // must be open drain
    dev.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_ALTFN;
    dev.Gpio_PinConfig.Gpio_PinAltFunNum = 4;
    dev.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PU;

    // serial clocks -> pb8
    dev.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_8;
    Gpio_Init(&dev);
    // sda -> pb9
    dev.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_9;
    Gpio_Init(&dev);
}

void Pg11butNledInit()
{
    gpio_dev_t butt, led;

    //button init => PG11
    butt.pGpiox = GPIOG;
    butt.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_11;
    butt.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_IN;
    butt.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_PIN_PD;
    butt.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_FAST;
    Gpio_Init(&butt);

    // led init => pg13
    led.pGpiox = GPIOG;
    led.Gpio_PinConfig.Gpio_PinNumber = GPIO_PIN_NO_13;
    led.Gpio_PinConfig.Gpio_PinSpeed = GPIO_SPEED_FAST;
    led.Gpio_PinConfig.Gpio_PinPuPdControl = GPIO_NO_PUPD;
    led.Gpio_PinConfig.Gpio_PinOPType = GPIO_OUT_PP;
    led.Gpio_PinConfig.Gpio_PinMode = GPIO_MODE_OUT;
    Gpio_Init(&led);
}

int main(void)
{
	Rcc_Init();
    // init butt, led gpio
	Pg11butNledInit();
	// using i2c 1 peripheral
	I2c1Gpio();
    I2c_base_init(i2cn1, I2C_SM_100, I2C_KERCLK_8MHZ);

    // set up data before using i2c peripheral
    i2c_device_t idev;
    idev.i2c = I2C1;
    idev.conf.autoend = 0;
    idev.conf.reload = 0;
    idev.conf.dir = 0;
    idev.conf.addr_mode = 0;
    idev.conf.target_addr = 0x68;
    idev.conf.own1_addr = 0x61;

    I2c_master_cfg(&idev);
    uint8_t data[] = "ardu this one is ..";
    /* Loop forever */
    while(1){
        while( !Gpio_read_pin(GPIOG, GPIO_PIN_NO_11));
        delay();
        i2c_enable(I2C1);
        Gpio_pin_on(GPIOG, GPIO_PIN_NO_13);
        I2c_MasterSend(&idev, data, strlen(data));
        delay();
        i2c_disable(I2C1);
        Gpio_pin_off(GPIOG, GPIO_PIN_NO_13);
	};
}

void delay()
{
    for(uint32_t i =0; i < 250000;i++);
}

#pragma clang diagnostic pop