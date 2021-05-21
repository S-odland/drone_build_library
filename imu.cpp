#include "imu.h"
#include <Wire.h>

IMU_device::IMU_device(void) {};

void IMU_device::begin_I2C(uint8_t addr, TwoWire *wire){
    
    i2c_device = new I2C_device(addr, wire);
    i2c_device->begin();

    uint8_t who;
    bool stop;
    stop = false;
    wire->beginTransmission(LSM6DS33_ID);
    wire->write(IMU_WHOAMI);
    wire->endTransmission(stop);
    stop = true;
    wire->requestFrom(LSM6DS33_ID,1);
    while (wire->available()){
        who = wire->read();
    }  
	if (who != 0b01101001){
		while(1)
		{
			Serial.println(who);
		}
	}

	// init IMU_CTRL1_XL
	i2c_device->write(IMU_CTRL1_XL,0b10000010);

	// init IMU_CTRL2_G
	i2c_device->write(IMU_CTRL2_G,0b10001000);

	// init IMU_CTRL3_C
	i2c_device->write(IMU_CTRL3_C,0b00000100);

}

void IMU_device::read_data(float *data_rd,uint8_t reg){

    unsigned char data1;
	unsigned char data2;

	i2c_device->read(&data1,reg);
	i2c_device->read(&data2,reg + 0x01);

	*data_rd = (data2 << 8) | data1;	

}

// void IMU_device::read_accel_data(float *acc_x,float *acc_y, float *acc_z){

// 	read_data((accel_data+0),IMU_OUTX_L_XL);
// 	read_data((accel_data+1),IMU_OUTY_L_XL);
// 	read_data((accel_data+2),IMU_OUTZ_L_XL);

// }

// void IMU_device::read_gyro_data(float *gyr_x, float *gyr_y,float *gyr_z){

// 	read_data((gyro_data+0),IMU_OUTX_L_G);
// 	read_data((gyro_data+1),IMU_OUTY_L_G);
// 	read_data((gyro_data+2),IMU_OUTZ_L_G);

// }

// void IMU_device::get_imu_data(float *acc_x,float *acc_y, float *acc_z, float *gyr_x, float *gyr_y,float *gyr_z) {
	
// 	read_gyro_data(float *gyr_x, float *gyr_y,float *gyr_z);
// 	read_accel_data(float *acc_x,float *acc_y, float *acc_z);
// }

// void IMU_device::imu_filter(float accel_data[3], float gyro_data[3], float *accel_mag, float *pitch_accel, float *roll_accel, float *yaw_mag, float filter_accel_data[3], float filter_gyro_data[3]) {

// 	*(filter_accel_data) = *(filter_accel_data) + 0.1*(*(accel_data) - *(filter_accel_data));
// 	*(filter_accel_data+1) = *(filter_accel_data+1) + 0.1*(*(accel_data+1) - *(filter_accel_data+1));
// 	*(filter_accel_data+2) = *(filter_accel_data+2) + 0.1*(*(accel_data+2) - *(filter_accel_data+2));
	
// 	*(filter_gyro_data) += *(gyro_data) * DeltaT;
// 	*(filter_gyro_data+1) += *(gyro_data+1) * DeltaT;
// 	*(filter_gyro_data+2) += *(gyro_data+2) * DeltaT;

// 	*accel_mag = fabs(*(filter_accel_data)) + fabs(*(filter_accel_data+1)) + fabs(*(filter_accel_data+2));
	
// 	if (fabs(*accel_mag - 1) < 0.2) {

// 		*pitch_accel = (180/M_PI) * atan2(- *(filter_accel_data+1), *(filter_accel_data+2));
// 		*roll_accel = (180/M_PI) * atan2( *(filter_accel_data), sqrt( (*(filter_accel_data+1) * *(filter_accel_data+1)) +  (*(filter_accel_data+2) * *(filter_accel_data+2))));

// 		*(filter_gyro_data) = 0.99* *(filter_gyro_data) + 0.01 * *pitch_accel;
// 		*(filter_gyro_data+1) = 0.99* *(filter_gyro_data) + 0.01 * *roll_accel;

// 	}

// }

















/*          LED LOCATIONS
 *
 *   (led_1) 	 O O    (led_10)
 *   (led_2)   O     O  (led_9)
 *   (led_3)  O       O (led_8)
 *   (led_4)   O     O  (led_7)
 *   (led_5)     O O    (led_6)
 *
 */

// void IMU_device::detect_tilt_loc(double accel_data[3], double tilt_loc[10]){

// 	double x = *(accel_data);
// 	double y = *(accel_data+1);
// 	//signed short z = *(accel_data+2);

// 	float mag = abs(x) + abs(y);
// 	float mag_x = abs(x)/mag;
// 	float mag_y = abs(y)/mag;

// 	if (x > 0 && y > 0) {

// 		if (mag_y > mag_x) {
// 			reset_tilt_loc(tilt_loc);
// 			*(tilt_loc+3) = 1;
// 		} else {
// 			reset_tilt_loc(tilt_loc);
// 			*(tilt_loc+4) = 1;
// 		}

// 	} else if (x < 0 && y > 0) {

// 		if (mag_y > mag_x) {
// 			reset_tilt_loc(tilt_loc);
// 			*(tilt_loc+1) = 1;
// 		} else {
// 			reset_tilt_loc(tilt_loc);
// 			*(tilt_loc) = 1;
// 		}

// 	} else if (x < 0 && y < 0) {

// 		if (mag_y > mag_x) {
// 			reset_tilt_loc(tilt_loc);
// 			*(tilt_loc+8) = 1;
// 		} else {
// 			reset_tilt_loc(tilt_loc);
// 			*(tilt_loc+9) = 1;
// 		}

// 	} else if (x > 0 && y < 0) {

// 		if (mag_y > mag_x) {
// 			reset_tilt_loc(tilt_loc);
// 			*(tilt_loc+6) = 1;
// 		} else {
// 			reset_tilt_loc(tilt_loc);
// 			*(tilt_loc+5) = 1;
// 		}

// 	} else if (x == 0 && y > 0) {

// 		reset_tilt_loc(tilt_loc);
// 		*(tilt_loc+2) = 1;

// 	} else if ( x == 0 && y < 0) {

// 		reset_tilt_loc(tilt_loc);
// 		*(tilt_loc+7) = 1;

// 	} else {

// 		reset_tilt_loc(tilt_loc);

// 	}

// }