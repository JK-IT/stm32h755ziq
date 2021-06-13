/*
 * i2c.h
 *
 *  Created on: Apr 10, 2021
 *      Author: kdg
 */


#ifndef I2C_H_
#define I2C_H_
#include "stm32h755xx.h"
#include "rcc.h"

//* I2C_CR1 BITS
#define i2c_pe_bit  0
#define i2c_txie_bit 1
#define i2c_rxie_bit 2
#define i2c_analogfilter_bit    12  //0 =enable, 1 = disable
#define i2c_nostretch_bit   17      //0 = enable, 1 = disable

//* I2C_CR2 BITS
#define i2c_rdwrdir_bit 10  // 0 = write, 1 = read direction
#define i2c_add10_bit   11      //0 = 7bit addr mode, 1 = 10bit addr mode
#define i2c_head10r_bit 12
#define i2c_start_bit 13
#define i2c_stop_bit 14
#define i2c_nbytes_bit 16   // 16-23, 7 bit wide
#define i2c_reload_bit 24
#define i2c_autoend_bit 25  //0 = manual, 1 = auto end
#define i2c_perr_bit 26

//*     I2C_TIMING BITS
#define i2c_pres_bits    28 // 31-28
#define i2c_scldel_bits    20 // 23-20
#define i2c_sdadel_bits    16 // 19-16
#define i2c_sclh_bits    8 // 15-8
#define i2c_scll_bits    0 // 7-0

//** STATUS FLAGS  */
#define i2cflag_txe 0
#define i2cflag_txis 1
#define i2cflag_rxne 2
#define i2cflag_addr 3
#define i2cflag_nack 4
#define i2cflag_stopf 5
#define i2cflag_tc 6    // transfer complete
#define i2cflag_tcr 7 // transfer complete reload
#define i2cflag_berr 8 // bus error
#define i2cflag_arlo 9  // arbitration lost
#define i2cflag_ovr 10 // over/underrun slave mode
#define i2cflag_pecerr 11 // pec error in reception
#define i2cflag_timeout 12 // timeout detection
#define i2cflag_alert 13 // smbus alert
#define i2cflag_busy 15 // busy
#define i2cflag_dir 16 // transfer direction

//**CHECK FLAG CONDITION */
#define i2c_flag_check(i2c, x)    ( ((i2c->isr) >> x) & 0x1 )

//*     CONFIG struct OF I2C
typedef struct{
    __vo uint8_t addr_mode ; // 7-bits or 10 bits mode
    __vo uint16_t target_addr;

    __vo uint8_t autoend ; // def: 0
    __vo uint8_t reload;    // def: 0
    __vo uint8_t dir;    // def: 0 = write dir
    __vo uint8_t perrcheck; // 1 : request to check packet, 0: no error

    //todo: field to config as slave mode here
    __vo uint16_t own1_addr;
    __vo uint16_t own2_addr;

} i2c_config_t;

//*     HANDLE struct OF I2C
typedef struct {
    i2c_config_t conf;
    I2c_reg_t* i2c;
} i2c_device_t;

#define i2cn1   1
#define i2cn2   2
#define i2cn3   3
#define i2cn4   4

#define i2c_enable(x) (x->cr1 |= (0x1 << 0))
#define i2c_disable(x) (x->cr1 &= ~(0x1 << 0))
#define i2c_start(x) (x->cr2 |= (0x1 << i2c_start_bit))
#define i2c_stop(x) (x->cr2 |= (0x1 << i2c_stop_bit))


// * ================  I2C function

///<summary>
/**
 * Standart mode - support up to 100khz
 * Fast mode - support up to 400khz
 * Fast mode + support up to 1 mhz
*/
///</summary>


/**
 * @brief 
 * *Set up Kernel Clk with desired Clk Ouput
 * Enable Peripheral Bus clk to access peripheral register
 * Setup output speed of kernel clk and SET PLL3_R as src clk 
 * @param clkspd @ rcc header
 * @param i2cnum the i2c peripheral
 *  */
void I2c_clk_init(uint8_t kerclkspd, uint8_t i2cnum);

/**
 * @brief 
 *      *CONFIG THE MASTER SPEED WITH SDA, SCL, SCLL, SCLH
 *  scllow_per; // t = (scll + 1) * t[presc]
    sclhigh_per; // t = (sclh+1) * t[presc]
    sdadel; // [3:0] data hold time, period between scl falling edge and sda edge --> t = (sdadel ) *  t[prescale] + t[i2cclk]
    scldel; // [3:0] data setup time, period between sda edge and scl rising edge--> t = (scldel + 1)* t[presc]
    presc;  //[3:0]  presacling time --> t = (presc + 1) * t[i2cclk]
 * @param i2c 
 * @param clkspd = master clk speed ( 100khz, 400 khz, 1000khz .....)
 * @param kerclk = kernel clk speed ( 8, 16 ... mhz)
 */
void I2c_master_speed(I2c_reg_t* i2c, uint8_t masterclkspd, uint8_t kerclkmhz);


#define I2C_SM_100  1
#define I2C_FM_400  2
#define I2C_FMPLUS_1000 4
/**
 * @brief 
 *  *BASIC CONFIG OR COMMON CONFIG
 *  - peri clock for bus
 *  - ker clock for master scl
 *  - master clk speed
 * @param i2cn 
 */
void I2c_base_init(uint8_t i2cn, uint8_t masterclk, uint8_t kerclkmhz);

/// ----------> Configure Master features
/**
 * @brief Set up Parameters for use in master mode
 * @param i2cdev
 */
void I2c_master_cfg(i2c_device_t* i2dev);


/**
 * @brief 
 * * RESET THE I2C block
 * 
 * @param i2cn 
 */
void I2c_reset(uint8_t i2cn);

/**
 * @brief   Sending Data from Master
 * @param i2cdev : the i2c Device
 * @param pbuffer : pointer to buffer
 * @param len : length of buffer
 */
void I2c_MasterSend(i2c_device_t* dev, uint8_t * pbuffer, uint32_t len);

#endif /* I2C_H_ */
