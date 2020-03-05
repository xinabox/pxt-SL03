#pragma once
#ifdef CODAL_I2C
#include "I2C.h"
#include "Pin.h"
#endif
#include "inttypes.h"
#include "pxt.h"

#define INPUT_P0 (uint8_t)0x00
#define INPUT_P1 (uint8_t)0x01
#define OUTPUT_P0 (uint8_t)0x02
#define OUTPUT_P1 (uint8_t)0x03
#define POL_INV_P0 (uint8_t)0x04
#define POL_INV_P1 (uint8_t)0x05
#define CONFIG_P0 (uint8_t)0x06
#define CONFIG_P1 (uint8_t)0x07

#define TCA9539_I2C_ADDR 0x74

class SL03 {
    public:
      SL03();
      SL03(uint8_t addr);
      void begin();
      uint8_t readInput(uint8_t *input);
      uint8_t irLedState(bool state);
      uint8_t bufferState(bool state);
      
    private:
      uint8_t writePin(uint8_t pinNo, uint8_t state);
      uint8_t i2cAddr;

};