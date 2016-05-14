#pragma once

#define I2C_DISTANCE_ADDRESS (uint8_t) (0x40 << 1) // Default
// #define I2C_DISTANCE_ADDRESS (uint8_t) (0x38 << 1) // 7

/*
    http://www.sharp-world.com/products/device/lineup/data/pdf/datasheet/gp2y0e02_03_appl_e.pdf
    Table.11 Register Map (Bank0)
*/
#define DISTANCE_11_4 0x5E // Distance Value=(Distance[11:4]*16+Distance[3:0])/16/2^n n : Shift Bit (Register 0x35)
#define SPOT 0xF8 // Spot Size = Right Edge Coordinate :0xF8 - Left Edge Coordinate :0xF9

#define I2C_FREQ 400000
