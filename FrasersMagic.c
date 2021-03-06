/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "bno055.h"
#include "project.h"
#include "FrasersMagic.h"

uint8 read8(uint8 reg_addr)
{
    volatile uint8 status = 0;
    volatile uint8 dataStored = 0;
    status = I2C_MasterSendStart(dev_addr,I2C_WRITE_XFER_MODE);
    status = I2C_MasterWriteByte(reg_addr);
    status = I2C_MasterSendStop();
    status = I2C_MasterSendStart(dev_addr, I2C_READ_XFER_MODE);
    dataStored = I2C_MasterReadByte(I2C_NAK_DATA);
    I2C_MasterSendStop();
    status = I2C_MasterStatus();
    if(status !=0)
    {
        LCD_PrintString("Read Error");
    }
    return dataStored;
}

void write8(uint8 reg_addr, uint8 data)
{
    volatile uint8 status = 0;
    status = I2C_MasterSendStart(dev_addr, I2C_WRITE_XFER_MODE);
    status = I2C_MasterWriteByte(reg_addr);
    status = I2C_MasterWriteByte(data);
    I2C_MasterSendStop();
}
/*
s8 set_data_type()
{
    write8(
}
*/
void set_page_zero()
{
    write8(BNO055_PAGE_ID_REG,0);
}

void power_set_mode()
{
    set_page_zero();
    write8(BNO055_PWR_MODE_ADDR,BNO055_POWER_MODE_NORMAL);
    CyDelay(10);
}    
    
// set the units
void units_set_mode()
{
    	    /*
    uint8_t unitsel = (0 << 7) | // Orientation = Android
                    (0 << 4) | // Temperature = Celsius
                    (0 << 2) | // Euler = Degrees
                    (1 << 1) | // Gyro = Rads
                    (0 << 0);  // Accelerometer = m/s^2
    */
    write8(BNO055_PAGE_ID_ADDR,0);
    write8(BNO055_UNIT_SEL_ADDR, 0<<7);
    write8(BNO055_SYS_TRIGGER_ADDR,0x00);
    CyDelay(10);
}

void sensor_set_mode()
{
    set_page_zero();
    write8(BNO055_OPERATION_MODE_REG, BNO055_OPERATION_MODE_NDOF);
}

u8 read_quat_data()
{
    set_page_zero();
	u8 data_u8[4] = {0, 0, 0, 0};
			/* Read the eight byte value
			of quaternion wxyz data*/
			/* Data W*/
            data_u8[0] = read_qw();
			/* Data X*/
            data_u8[1] =read_qx();
            /* Data Y*/
            data_u8[2] = read_qy();
			/* Data Z*/
            data_u8[3] = read_qz();
    return data_u8[0];
    return data_u8[1];
    return data_u8[2];
    return data_u8[3];    
}

//read from the quaternion registers:

//Reading quaternion W
s8 read_qw()
{
    set_page_zero();
    s8 qw1 = read8(BNO055_QUATERNION_DATA_W_LSB_VALUEW_REG);
    s8 qw2 = read8(BNO055_QUATERNION_DATA_W_MSB_VALUEW_REG);
    s16 qw = (s16)qw1;
    qw = qw<<8;
    qw |= qw2;
    return qw;
}
//Reading quaternion X
s8 read_qx()
{
    set_page_zero();
    s8 qx1 = read8(BNO055_QUATERNION_DATA_W_LSB_ADDR);
    s8 qx2 = read8(BNO055_QUATERNION_DATA_W_MSB_ADDR);
    s16 qx = (s16)qx1;
    qx = qx<<8;
    qx |= qx2;
    return qx;
}
//Reading quaternion Y
s8 read_qy()
{
    set_page_zero();
    s8 qy1 = read8(BNO055_QUATERNION_DATA_W_LSB_ADDR);
    s8 qy2 = read8(BNO055_QUATERNION_DATA_W_MSB_ADDR);
    s16 qy = (s16)qy1;
    qy = qy<<8;
    qy |= qy2;
    return qy;
}
//Reading quaternion Z
s8 read_qz()
{
    set_page_zero();
    s8 qz1 = read8(BNO055_QUATERNION_DATA_W_LSB_ADDR);
    s8 qz2 = read8(BNO055_QUATERNION_DATA_W_MSB_ADDR);
    s16 qz = (s16)qz1;
    qz = qz<<8;
    qz |= qz2;
    return qz;
}
