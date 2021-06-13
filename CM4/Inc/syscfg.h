/*
 * syscfg.h
 *
 *  Created on: Apr 10, 2021
 *      Author: kdg
 */


#ifndef SYSCFG_H_
#define SYSCFG_H_
#include "stm32h755xx.h"
#include "rcc.h"


typedef enum {
    PA =0,
    PB,
    PC,
    PD,
    PE,
    PF,
    PG,
    PH,
    PI,
    PJ,
    PK // PK PIN 11:8 ARE NOT USED
} Syscfg_port_t;

/*
    ENABLE SYS CONFIG CLK
*/
void Syscfg_init();

/*
    ENABLE GPIO AS INTERRUPT SOURCE
@pa1 : port to enable
@pa2: pin to enable
@ret: void
*/
void Syscfg_exti_source(Syscfg_port_t port, uint8_t pin);

#endif /* SYSCFG_H_ */
