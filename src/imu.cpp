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

void IMU_device::led_setup(void){

    pinMode(LED_1,OUTPUT);
    pinMode(LED_2,OUTPUT);
    pinMode(LED_3,OUTPUT);
    pinMode(LED_4,OUTPUT);
    pinMode(LED_5,OUTPUT);
    pinMode(LED_6,OUTPUT);
    pinMode(LED_7,OUTPUT);
    pinMode(LED_8,OUTPUT);
    pinMode(LED_9,OUTPUT);
    pinMode(LED_10,OUTPUT);

	set_leds(HIGH);

}

void IMU_device::set_leds(int status){

    digitalWrite(LED_1, status);
	digitalWrite(LED_2, status);
	digitalWrite(LED_3, status);
	digitalWrite(LED_4, status);
	digitalWrite(LED_5, status);
	digitalWrite(LED_6, status);
	digitalWrite(LED_7, status);
	digitalWrite(LED_8, status);
	digitalWrite(LED_9, status);
	digitalWrite(LED_10,status);

}

void IMU_device::read_data(signed short *data_rd,uint8_t reg){

    unsigned char data1;
	unsigned char data2;

	i2c_device->read(&data1,reg);
	i2c_device->read(&data2,reg + 0x01);

	*data_rd = (data2 << 8) | data1;

	scale_data(data_rd);

}

void IMU_device::scale_data(signed short *data){

    // int gyro_scale = 8.75;
    // int dps_to_rads = 0.0175;

    // int accel_scale = 0.061;
    // int accel_gravity = 9.801;

    // *data = accel_scale * (*data) * accel_gravity / 1000;
    *data = 16 * (*data) / 16383;
}

/*          LED LOCATIONS
 *
 *   (led_1) 	 O O    (led_10)
 *   (led_2)   O     O  (led_9)
 *   (led_3)  O       O (led_8)
 *   (led_4)   O     O  (led_7)
 *   (led_5)     O O    (led_6)
 *
 */

void IMU_device::detect_tilt_loc(signed short accel_data[3]){

	signed short x = *(accel_data);
	signed short y = *(accel_data+1);
	//signed short z = *(accel_data+2);

	float mag = abs(x) + abs(y);
	float mag_x = abs(x)/mag;
	float mag_y = abs(y)/mag;

	if (x > 0 && y > 0) {

		if (mag_y > mag_x) {
			set_leds(0);
			digitalWrite(LED_4,1);
		} else {
			set_leds(0);
			digitalWrite(LED_5,1);
		}

	} else if (x < 0 && y > 0) {

		if (mag_y > mag_x) {
			set_leds(0);
			digitalWrite(LED_2,1);
		} else {
			set_leds(0);
			digitalWrite(LED_1,1);
		}

	} else if (x < 0 && y < 0) {

		if (mag_y > mag_x) {
			set_leds(0);
			digitalWrite(LED_9,1);
		} else {
			set_leds(0);
			digitalWrite(LED_10,1);
		}

	} else if (x > 0 && y < 0) {

		if (mag_y > mag_x) {
			set_leds(0);
			digitalWrite(LED_7,1);
		} else {
			set_leds(0);
			digitalWrite(LED_6,1);
		}

	} else if (x == 0 && y > 0) {

		set_leds(0);
		digitalWrite(LED_3,1);

	} else if ( x == 0 && y < 0) {

		set_leds(0);
		digitalWrite(LED_8,1);

	} else {

		set_leds(0);

	}

}