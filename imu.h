#ifndef IMU_H_
#define IMU_H_

#include <Arduino.h>
#include <Wire.h>
#include "i2c.h"
#include <math.h>

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

#define DeltaT 0.002

class IMU_device
{
public:

    IMU_device();
    void begin_I2C(uint8_t addr, TwoWire *wire = &Wire);
    void read_data(signed short *data_rd,uint8_t reg);
    //void get_imu_data(float acc_x,float acc_y, float acc_z, float gyr_x, float gyr_y,float gyr_z);

    // void imu_filter(float accel_data[3], 
    //                 float gyro_data[3], 
    //                 float *accel_mag, 
    //                 float *pitch_accel, 
    //                 float *roll_accel, 
    //                 float *yaw_mag,
    //                 float filter_accel_data[3],
    //                 float filter_gyro_data[3]);

private:

    //void read_accel_data(float *acc_x,float *acc_y, float *acc_z);
    //void read_gyro_data(float *acc_x,float *acc_y, float *acc_z);

protected: 

    I2C_device *i2c_device = NULL;

};


#endif /* MAIN_IMU_H_ */