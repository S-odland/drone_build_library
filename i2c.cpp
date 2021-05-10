extern "C" {
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
}

#include "i2c.h"


I2C_device::I2C_device(uint8_t addr, TwoWire *theWire) {
    _addr = addr;
    _wire = theWire;
    _begun = false;
};

void I2C_device::begin(void) {
    _wire->begin();
}

// bool I2C_device::detected(void) {
//   if (!_begun && !begin()) {
//     return false;
//   }

//   _wire->beginTransmission(_addr);
//   if (_wire->endTransmission() == 0) {
//     return true;
//   }
//   return false;
// }

void I2C_device::write(uint8_t cntrl_reg, uint8_t data){
    bool stop;
    stop = true;
    // write to slave address
    _wire->beginTransmission(_addr);
    // write the reg to which we want to send data
    _wire->write(cntrl_reg);
    // write the data we want to send to that register
    _wire->write(data);
    _wire->endTransmission(stop);

}

void I2C_device::read(uint8_t *data_rd,uint8_t reg){
    bool stop;
    stop=false;
    // write to slave address
    _wire->beginTransmission(_addr);
    // write the reg from which we want to read data
    _wire->write(reg);
    _wire->endTransmission(stop);
    stop = true;
    _wire->requestFrom(_addr,1,stop);
    while(_wire->available()){
        *data_rd = _wire->read();
    }
    //_wire->endTransmission(stop);

}