#ifndef I2C_H_
#define I2C_H_

#include <Arduino.h>
#include <Wire.h>

#define I2C_MASTER_SDA_IO 18
#define I2C_MASTER_SCL_IO 19
#define I2C_MASTER_FREQ_HZ 100000
#define I2C_MODE_MASTER 1
#define GPIO_PULLUP_ENABLE = 0x1
#define I2C_MASTER_TX_BUF_DISABLE 0 
#define I2C_MASTER_RX_BUF_DISABLE 0  

class I2C_device
{
public:
    I2C_device(uint8_t addr, TwoWire *theWire = &Wire);
    void begin(void);
    // bool detected(void);
    void write(uint8_t cntrl_reg, uint8_t data);
    void read(uint8_t *data_rd,uint8_t reg);
private:
    uint8_t _addr;
    TwoWire *_wire;
    bool _begun;
};

#endif