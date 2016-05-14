gp2y0e03-example
====
Sharp IR Sensor GP2Y0E03 Example on mbed OS with Sync and Async I2C API

# Setup instruction for ST-Microsystems Nucleo

    $ yt target st-nucleo-f401re-gcc
    $ yt install

# Choose I2C Async API or I2C Sync API

Edit `ASYNC` definition in app.cpp.

    #define ASYNC 1

The value `1` for enabling asynchronous API and `0` for enabling synchronous API.

`ASYNC` is `1` by default.

# Modify I2C device address

Change `I2C_DISTANCE_ADDRESS` definition in gp2y0e03.hpp.

# USB Serial Baud rate

Set 115200 bps in order to connect to the USB serial port. The baud rate is set in config.json file.
