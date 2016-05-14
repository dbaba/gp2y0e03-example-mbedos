#include "gp2y0e03-example/ir_sync.hpp"

static I2C i2cBus(PB_9, PB_8);

static uint8_t data[2];

static void _i2c_read(I2C *i2c, uint8_t address, uint8_t register_address) {
    if (i2c->write(address, (char *) &register_address, 1)) {
        memset(data, 0x00, 2);
        return;
    }
    if (i2c->read(address, (char *) data, 2)) {
        memset(data, 0x00, 2);
        return;
    }
}

void ir_distance_sync_task(void) {
    _i2c_read(&i2cBus, I2C_DISTANCE_ADDRESS, DISTANCE_11_4);
    // Out of range
    if (data[0] == 0xff && data[1] == 0x0f) {
        printf("IR Distance => %s\r\n", "Out of Ramge");
        return;
    }
    // Not yet installed
    if (data[0] == 0x00 && data[1] == 0x00) {
        printf("IR Distance => %s\r\n", "Not Available");
        return;
    }
    printf("IR Distance => %dcm\r\n", ((((uint16_t) data[0] << 4) + (data[1] & 0x0f)) / 16 / 4));

    _i2c_read(&i2cBus, I2C_DISTANCE_ADDRESS, SPOT);
    if (data[0] < data[1]) {
        printf("IR Spot => %s\r\n", "Not Available");
    } else {
        printf("IR Spot => %d\r\n", (data[0] - data [1]));
    }
}

void ir_distance_sync_task_init(void) {
    i2cBus.frequency(I2C_FREQ);
}
