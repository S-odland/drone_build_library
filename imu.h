#ifndef IMU_H_
#define IMU_H_

#include <Arduino.h>
#include <Wire.h>
#include "i2c.h"

#define IMU_WHOAMI 0x0F
#define LSM6DS33_ID 0x6B
#define IMU_ADDR_READ 0b11010111
#define IMU_ADDR_WRITE 0b11010110
#define IMU_CTRL1_XL 0x10
#define IMU_CTRL2_G 0x11
#define IMU_CTRL3_C 0x12
#define IMU_OUT_TEMP_L 0x20
#define IMU_OUTX_L_G 0x22
#define IMU_OUTY_L_G 0x24
#define IMU_OUTZ_L_G 0x26
#define IMU_OUTX_L_XL 0x28
#define IMU_OUTY_L_XL 0x2A
#define IMU_OUTZ_L_XL 0x2C

#define LED_1  12
#define LED_2  13
#define LED_3  14
#define LED_4  25
#define LED_5  26
#define LED_6  27
#define LED_7  32
#define LED_8  33
#define LED_9  22
#define LED_10 23

class IMU_device
{
public:
    IMU_device();
    void begin_I2C(uint8_t addr, TwoWire *wire = &Wire);
    void led_setup(void);
    void set_leds(int status);
    void read_data(signed short *data_rd,uint8_t reg);
    void scale_data(signed short *data);
    void detect_tilt_loc(signed short accel_data[3]);
protected: 
    I2C_device *i2c_device = NULL;
};

#endif /* MAIN_IMU_H_ */