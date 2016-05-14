#include "gp2y0e03-example/ir_async.hpp"

static mbed::drivers::v2::I2C i2cAsyncBus(PB_9, PB_8);

static void ir_spot_data_callback(mbed::drivers::v2::I2CTransaction * t, uint32_t event) {
    (void) event;
    t->reset_current();
    uint8_t* data = (uint8_t*) t
        ->get_current() // get the first segment (the tx segment)
        ->get_next()    // get the second segment (the rx segment)
        ->get_buf();    // get the buffer pointer

    if (data[0] < data[1]) {
        printf("IR Spot => %s\r\n", "Not Available");
    } else {
        printf("IR Spot => %d\r\n", (data[0] - data [1]));
    }
}

static void ir_spot_task(void) {
    uint8_t cmd = SPOT;
    i2cAsyncBus.transfer_to(I2C_DISTANCE_ADDRESS)
        .tx_ephemeral(&cmd, 1)
        .rx(2)
        .on(I2C_EVENT_TRANSFER_COMPLETE, ir_spot_data_callback)
        .apply();
}

static void ir_distance_data_callback(mbed::drivers::v2::I2CTransaction * t, uint32_t event) {
    (void) event;
    t->reset_current();
    uint8_t* data = (uint8_t*) t
        ->get_current() // get the first segment (the tx segment)
        ->get_next()    // get the second segment (the rx segment)
        ->get_buf();    // get the buffer pointer

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
    ir_spot_task();
}

void ir_distance_async_task(void) {
    uint8_t cmd = DISTANCE_11_4;
    i2cAsyncBus.transfer_to(I2C_DISTANCE_ADDRESS)
        .tx_ephemeral(&cmd, 1)
        .rx(2)
        .on(I2C_EVENT_TRANSFER_COMPLETE, ir_distance_data_callback)
        .apply();
}

void ir_distance_async_task_init(void) {
    i2cAsyncBus.frequency(I2C_FREQ);
}
