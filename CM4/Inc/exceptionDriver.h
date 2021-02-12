#ifndef INC_EXCEPTIONDRIVER_H
#define INC_EXCEPTIONDRIVER_H

#include "stdint.h"

/*
    Interruption and Exception manager
    These exceptions and irqs are controllered by cortex m4 register in system control block memory area
    0xE000E000 - 0x E000EFFF
*/

/*
 * Define the IRQ number for EXTI
 */
#define IRQ_NO_EXTI0	6
#define IRQ_NO_EXTI1	7
#define IRQ_NO_EXTI2	8
#define IRQ_NO_EXTI3	9
#define IRQ_NO_EXTI4	10
#define IRQ_NO_EXTI9_5	23
#define IRQ_NO_EXTI15_10 	40



void SetIrqNum(uint8_t irqnum);
void DisIrqNum(uint8_t irqnum);
void SetIrqPri(uint8_t irqn, uint8_t prinum);



/*  EXTI SECTION - MOSTLY USED FOR WAKE UP EVENT TO WAKE UP CPU AND DOMAIN
    THE BLOCK implemented by stm32 manufacture
    this block is middle guy between nvic table and event
    This block also have its own event table mapping
    Config will be using EXTI REGISTERS

*/

typedef enum{
    FallEdge,
    RisingEdge,
    BothEdge
} Exti_trigger_edge_t;

/*  
---    Exti block Initialization
    turn on the bus clock
@param null;
@return null;
*/
void ExtiInit(); //===>empty implementation

/*  
---    Exti Set cortex m4 -- Cpu2 on the board 
@param null;
@return null;
*/
void Set_C2IM_ioexti(uint8_t linenum, Exti_trigger_edge_t edge);



#endif