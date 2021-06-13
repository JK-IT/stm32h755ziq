/*
 * exception.c
 *
 *  Created on: Apr 10, 2021
 *      Author: kdg
 */

#include "exception.h"
#include "stm32h755xx.h"


/*
    Interruption and Exception manager
    These exceptions and irqs are controllered by cortex m4 register in system control block memory area
    0xE000E000 - 0x E000EFFF
*/
void SetIrqNum(uint8_t irqnum)
{
	// the debugger display wrong address of this iser
	//       irqnum / 32 to find pos        0x1f cuz the pos start as 0 , but dec will be %32
    (NVIC->ISER[irqnum >> 5]) = (1 << (irqnum & 0x1f)); // similar to irqnum % 32
}

void DisIrqNum(uint8_t irqnum)
{
    NVIC->ICER[irqnum >> 5] = 1 << (irqnum & 0x1f);
}
void SetIrqPri(uint8_t irqn, uint8_t prinum)
{
    NVIC->IPRIR[irqn] = (prinum << 4) & 0xff;
}


/*
---    Exti block Initialization
    turn on the bus clock
    EXTI BUS CLOCK IS RESERVED SO NO NEED TO CONFIG
    BUT SYSCONF CLOK NEED TO BE ON TO SET INTERRUPT SOURCE FROM INPUT PIN
@param null;
@return null;
*/
void ExtiInit()
{

}

/*
---    Exti IO INTERRUPT Set cortex m4 -- Cpu2 on the board
    Exti Line can wake up any target
@param null;
@return null;
*/
void Set_C2IM_ioexti(uint8_t linenum,Exti_trigger_edge_t edge){
    EXTI->C2IMR1 |= (1 << linenum); //set bit in exti cpu interrupt reg
    EXTI->D3PMR1 |= (1 << linenum); //set bit in d3 pending mask cuz this can wake any target
    //clear exti  pending reg
    EXTI->C2PR1 |= (1 << linenum);
    //setting the trigger edge
    switch (edge)
    {
    case FallEdge:
        EXTI->FTSR1 |= (1 << linenum);
        break;
    case RisingEdge:
        EXTI->RTSR1 |= (1 << linenum);
        break;
    default:
        EXTI->FTSR1 |= (1 << linenum);
        EXTI->RTSR1 |= (1 << linenum);
        break;
    }
    if(linenum <5 ){
        SetIrqNum( (5-0) + IRQ_NO_EXTI0);
    } else if ( (linenum >= 5) && (linenum < 10)) {
        SetIrqNum( IRQ_NO_EXTI9_5);
    } else {
        SetIrqNum ( IRQ_NO_EXTI15_10);
    }
}
