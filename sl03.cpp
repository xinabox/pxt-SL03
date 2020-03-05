#include "sl03.h"

using namespace pxt;

uint8_t i2cwrite(uint16_t address, uint8_t reg, uint8_t *data, int len) {
    int i2c_error_status = 0;
#ifdef CODAL_I2C
    auto sda = LOOKUP_PIN(SDA);
    auto scl = LOOKUP_PIN(SCL);
    codal::I2C *i2c = pxt::getI2C(sda, scl);
#endif
    uint8_t val[len + 1];
    val[0] = reg;
    for (uint8_t i = 0; i < len; i++) {
        val[i+1] = data[i];
    }
#ifdef CODAL_I2C
    return i2c_error_status = i2c->write((uint16_t)address, (uint8_t *)&val, len + 1, false);
#else
    return i2c_error_status = uBit.i2c.write(address, (const char *)&val, len + 1, false);
#endif
}

uint8_t i2cread(uint16_t address, uint8_t reg, uint8_t *data, int len) {
#ifdef CODAL_I2C
    auto sda = LOOKUP_PIN(SDA);
    auto scl = LOOKUP_PIN(SCL);
    codal::I2C *i2c = pxt::getI2C(sda, scl);
#endif
    int i2c_error_status = 0;

#ifdef CODAL_I2C
    i2c_error_status = i2c->write((uint16_t)address, (uint8_t *)&reg, 1, true);
#else
    i2c_error_status = uBit.i2c.write(address, (const char *)&reg, 1, true);
#endif

#ifdef CODAL_I2C
    return i2c_error_status = i2c->read((uint16_t)address, (uint8_t *)data, len, false);
#else
    return i2c_error_status = uBit.i2c.read(address, (char *)data, len, false);
#endif
}

void _sleep(uint16_t time_ms) {
#ifdef CODAL_I2C
    sleep_ms(time_ms);
#else
    uBit.sleep(time_ms);
#endif
}

SL03::SL03() {
    i2cAddr = TCA9539_I2C_ADDR << 1;
}

SL03::SL03(uint8_t addr) {
    i2cAddr = addr << 1;
}
void SL03::begin() {
    uint8_t c[1] = {0xFF};
    uint8_t c1[1] = {0x00};
    uint8_t c2[1] = {0x02};
    i2cwrite(i2cAddr, CONFIG_P0, c, 1);
    i2cwrite(i2cAddr, CONFIG_P1, c1, 1);
    irLedState(true);
    bufferState(false); // active low
}

uint8_t SL03::readInput(uint8_t *input) {
    i2cread(i2cAddr, INPUT_P0, input, 1);
}

uint8_t SL03::writePin(uint8_t pinNo, uint8_t state) {
    uint8_t old_state[1];
    uint8_t new_state[1];
    i2cread(i2cAddr, OUTPUT_P1, old_state, 1);
    _sleep(10);
    if (state == true) {
        new_state[0] = old_state[0] | (1 << pinNo);
        i2cwrite(i2cAddr, OUTPUT_P1, new_state, 1);
    }
    if (state == false) {
        new_state[0] = old_state[0] & ~(1 << pinNo);
        i2cwrite(i2cAddr, OUTPUT_P1, new_state, 1);
    }
}

uint8_t SL03::irLedState(bool state) {
    writePin(1, state);
}

uint8_t SL03::bufferState(bool state) {
    writePin(0, state);
}

namespace sl03 {

static SL03 *ptr = new SL03;
//%
void begin() {
    ptr->begin();
}

//%
void irLedState(bool state) {
    ptr->irLedState(state);
}

//%
void bufferState(bool state) {
    ptr->bufferState(state);
}

//%
uint8_t readInput() {
    uint8_t input[1];
    ptr->readInput(input);
    return input[0];
}
} // namespace sl03