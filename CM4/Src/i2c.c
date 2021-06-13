/*
 * i2c.c
 *
 *  Created on: Apr 10, 2021
 *      Author: kdg
 */


#include "i2c.h"

//* Kernel Clk Config for I2c
void I2c_clk_init(uint8_t clkspd, uint8_t i2cnum)
{
    // enable bus clk
    if(i2cnum !=  4)
    {
        Rcc_I2cBusCfg(i2cnum);
    } else 
    {
        Rcc_I2c4BusCfg();
    }
    // enable ker clk
    Rcc_Cfg_i2c_kerclk_speed(clkspd);
    Rcc_Cfg_i2c_kerclk(); // setting clk src
}


//?----------------------------------------------
//* set up the sda, scl, scll, sclh that fits the speed
    //* NOT ALLOWED WHEN PE BIT IS SET
//? Rising edge take 1 us, falling edge take .3us
void I2c_master_speed(I2c_reg_t* i2c, uint8_t masterclkspd, uint8_t kerclkmhz)
{
    if(masterclkspd == I2C_SM_100)
    {
        //data set up min time : .25 us
        // t(scl) = 1 / 100khz ~= 10 * 10 ^ -6(micro sec) = 10 us
        // tscl = tscllow + tsclhigh
        // tsync = scledge + filter + kerclksync
        //?tscllow = tdatahold + tvaliddata +  sdaedge + tdatasetup
        //?tsclhigh = tstartholding + tstartsetup + tstopsetup + busfreetime
        // tscl = tsync2 + tscllow + tsync1 + tsclhigh 
        //* according to example, tscllow or high also include tsync
        //=> tscllow = 5us, tsclhigh = 4us (defined by user)

        //*sdadel and scldel in practical also include the tsync, therefore u need to include tsync factor to calculate tsda or tscldel

        if(kerclkmhz == I2C_KERCLK_8MHZ)
        {
            // tkerclk = 1 / 8mhz = .125us
            //set PRESC = 1 => tpres = (1 + 1) * tkerclk = .25us
            i2c->timingr |= (0x01 << i2c_pres_bits);
            // set scllow = 0x13 => 0x13 + 1 * tpres = 5us
            i2c->timingr |= ( 0x13 << i2c_scll_bits);
            //set sclhigh = 0xf => 0xf + 1 * tpres = 4us
            i2c->timingr |= (0xf << i2c_sclh_bits);
            //tsdadel(max or recommended) = tscledgefalling + tfilter + tholdingdata = .3 + .26+ 0 = .56 us
            // set sdadel = 0x2 => 0x2 * tpres + tkerclk = .675us
            i2c->timingr |= (0x2 << i2c_sdadel_bits);
            //tscldel (max or recommended) = tsdaedge + tsetupdata = 1 + .25 = 1.25 us
            //set scldel = 0x4 => (0x4 + 1) * tpres = 1.25us
            i2c->timingr |= (0x4 << i2c_scldel_bits);
        } 
        else if(kerclkmhz == I2C_KERCLK_16MHZ)
        {
            // keep value the same for tscll, tsclh, tsda, tscl
            //tkerclk = 1 / 16 mhz = 0.0625 us
            // tpres = .25us => pres = 3
            i2c->timingr |= (0x03 << i2c_pres_bits);
            i2c->timingr |= (0x13 << i2c_scll_bits);
            i2c->timingr |= (0xf << i2c_sclh_bits);
            i2c->timingr |= (0x2 << i2c_sdadel_bits);
            i2c->timingr |= (0x4 << i2c_scldel_bits);
        }

    } else if(masterclkspd == I2C_FM_400)
    {
        // 1 / 400khz ~= 2.5 * 10 ^ -6(micro sec)= 2.5us
        if(kerclkmhz == I2C_KERCLK_8MHZ)
        {
            i2c->timingr |= (0x01 << i2c_pres_bits); // presc = 1
            i2c->timingr |= (0x02 << i2c_scldel_bits);
            i2c->timingr |= (0x01 << i2c_sdadel_bits);
            i2c->timingr |= (0x05 << i2c_scll_bits);
            i2c->timingr |= (0x02 << i2c_sclh_bits);
        }
        else if(kerclkmhz == I2C_KERCLK_16MHZ)
        {
            i2c->timingr |= (0x03 << i2c_pres_bits); // presc = 3
            i2c->timingr |= (0x02 << i2c_scldel_bits);
            i2c->timingr |= (0x01 << i2c_sdadel_bits);
            i2c->timingr |= (0x05 << i2c_scll_bits);
            i2c->timingr |= (0x02 << i2c_sclh_bits);
        }

    } else if(masterclkspd == I2C_FMPLUS_1000)
    {
        // 1 / 1000khz ~= 1 * 10 ^ -6(micro sec) = 1us
        if(kerclkmhz ==    I2C_KERCLK_8MHZ)
        {
            i2c->timingr &= ~(0x01 << i2c_pres_bits); // presc = 0
            i2c->timingr |= (0x01 << i2c_scldel_bits);
            i2c->timingr |= (0x01 << i2c_sdadel_bits);
            i2c->timingr |= (0x03 << i2c_scll_bits);
            i2c->timingr |= (0x02 << i2c_sclh_bits);

        } else if (kerclkmhz == I2C_KERCLK_16MHZ)
        {
            i2c->timingr |= (0x01 << i2c_pres_bits); // presc =1
            i2c->timingr |= (0x01 << i2c_scldel_bits);
            i2c->timingr |= (0x01 << i2c_sdadel_bits);
            i2c->timingr |= (0x03 << i2c_scll_bits);
            i2c->timingr |= (0x02 << i2c_sclh_bits);
        }
        
    }
}

/**
 * @brief 
 *  *BASIC CONFIG OR COMMON CONFIG
 *  * CONFIG BUS CLK, KERNEL CLK, MASTER CLK SPEED
 *  NOT ALLOWED WHEN PE BIT IS SET
 * @param i2cn 
 */
void I2c_base_init(uint8_t i2cn, uint8_t masterclk, uint8_t kerclkmhz)
{
    if(i2cn == i2cn1)
    {
        I2c_clk_init(kerclkmhz, i2cn);
        I2c_master_speed(I2C1, masterclk, kerclkmhz);
    } 
    else if(i2cn == i2cn2)
    {
        I2c_clk_init(kerclkmhz, i2cn);
        I2c_master_speed(I2C2, masterclk, kerclkmhz);
    } 
    else if(i2cn == i2cn3)
    {
        I2c_clk_init(kerclkmhz, i2cn);
        I2c_master_speed(I2C3, masterclk, kerclkmhz);
    } 
    else 
    {
        I2c_clk_init(kerclkmhz, i2cn);
        I2c_master_speed(I2C4, masterclk, kerclkmhz);
    }
}

/**
 * @brief Configure master feature I2c_master_cfg
 * @param i2dev
 * Set target address, set autoend, reload, direction bits
 * Set the number of datas to be transfered
 */
void I2c_master_cfg(i2c_device_t* i2dev)
{
    if(i2dev->conf.addr_mode == 0)    // 7-bit mode
    {
        //set bit[7:0]
        i2dev->i2c->cr2 &= ~(0x03ff) ; // clear the field
        i2dev->i2c->cr2 |= (i2dev->conf.target_addr << 1); // bit [9][8][0] don't care
        i2dev->i2c->oar1 &= ~(0x03ff);
        i2dev->i2c->oar1 |= (i2dev->conf.own1_addr << 1);
    } 
    else    //10-bit mode 
    {
        i2dev->i2c->cr2 &= ~(0x03ff) ; // clear the field
        i2dev->i2c->cr2 |= (i2dev->conf.target_addr);
        i2dev->i2c->oar1 &= ~(0x03ff);
        i2dev->i2c->oar1 |= (i2dev->conf.own1_addr);
    }

    i2dev->i2c->cr2 |= (i2dev->conf.autoend << i2c_autoend_bit) ;
    i2dev->i2c->cr2 |= (i2dev->conf.reload << i2c_reload_bit) ;
    i2dev->i2c->cr2 |= (i2dev->conf.dir << i2c_rdwrdir_bit);
    if(i2dev->conf.perrcheck == 1)
    {
        i2dev->i2c->cr1 |= (1 << 23); // enable pec calculation bit in cr1
        i2dev->i2c->cr2 |= (i2dev->conf.perrcheck << i2c_perr_bit);
    }
}


/**
 * @brief 
 * *$ RESET I2C BLOCK
 * @param i2cn 
 */
void I2c_reset(uint8_t i2cn)
{
    if(i2cn == i2cn1)
    {
        RCC->RCC_APB1LRSTR &= ~(1 << 21);
        RCC->RCC_APB1LRSTR |= (1 << 21);
    } 
    else if(i2cn == i2cn2)
    {
    	RCC->RCC_APB1LRSTR &= ~(1 << 22);
        RCC->RCC_APB1LRSTR |= (1 << 22);
    } 
    else if(i2cn == i2cn3)
    {
    	RCC->RCC_APB1LRSTR &= ~(1 << 23);
        RCC->RCC_APB1LRSTR |= (1 << 23);
    }
    else {
    	RCC->RCC_APB4RSTR &= ~(1 << 7);
        RCC->RCC_APB4RSTR |= (1 << 7);
    }
}


void I2c_MasterSend(i2c_device_t* dev, uint8_t * pbuffer, uint32_t len)
{
    //set the len to Nbytes bits
    dev->i2c->cr2 &= ~(0xff << i2c_nbytes_bit); // clear the fields
    dev->i2c->cr2 |= ( ((uint8_t) len) << i2c_nbytes_bit);
    // Set start bits of CR2
    // start bit is clear after address sequence is sent, or arbitration loss, or timeout or when PE=0
    // aka, as long as start bit is set, device is not in master mode yet
    // we can poll the start bit to know if device is turned on as master
    // device automatically sends start condition as soon as it detects the bus is free(BUSY=0) and after a delay
    i2c_start(dev->i2c);
    // polling the start bit to see if busy condition is set
    while ( (dev->i2c->cr2 >> i2c_start_bit) & 0x01);
    //check TXIS flag, why????
    // TXIS flag is set after each byte transmission, after 9th pulse when ACK is received
    // this flag is not set if NACK is received or byte transmission failed
    // follow NACK IS STOP CONDITION => BUSY=0, bus not occupied by this dev
    // todo: check more status in case, the busy=1 but from another master, not this device
    // if we see BUSY=1  and TXIS = 0, then bus may be occupied by another master
    //todo : use this flag to see if master really connects to any slave with that address
    if ( i2c_flag_check(dev->i2c, i2cflag_txis)) // => successful captures bus, and ACK received
    {
        // now the start bit is clear, busy flag should be set and your device is a master
        if( i2c_flag_check(dev->i2c, i2cflag_busy))
        {
            // now sending data
            while(len > 0)
            {
                while( !i2c_flag_check(dev->i2c, i2cflag_txe)); // txdr is not empty
                dev->i2c->txdr = (uint8_t) (*pbuffer);
                pbuffer++;
                len--;
                // todo: check if nack error, arbitration loss
            }

            // len is 0, now check if TC flag is set
            //TC flag = 1 , when reload = 0, autoend =0, NBYTES data have been transferred
            //TC flag is cleared by software when , start or stop condition is sent
            while( !i2c_flag_check(dev->i2c, i2cflag_tc));
            // set the stop bit
            i2c_stop(dev->i2c);
        }

        //while (1 );
    }
    else
    {
        //check NACKF in status register -> confirm if NACK IS RECEIVED, which causes TXIS NOT SET
        i2c_flag_check(dev->i2c, i2cflag_nack);
        // check if there is bus error, arbitration loss
        i2c_flag_check(dev->i2c, i2cflag_arlo);
        i2c_flag_check(dev->i2c, i2cflag_berr); //bus error flag
        //while (1);
    }
    // the bus bit status will be busy, when Start condition is detected
}
