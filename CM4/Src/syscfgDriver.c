#include "syscfgDriver.h"


/*
    ENABLE SYS CONFIG CLK
*/
void Syscfg_init()
{
    Rcc_sysconfClk_init();
}

void Syscfg_exti_source(Syscfg_port_t port, uint8_t pin)
{
    //            pin / 4                (pin % 4) * 4 , 4 bits is used to define port
    SYSCFG->EXTICR[pin >> 2] = port << (  (pin & 0x03) << 2 ) ;
}
