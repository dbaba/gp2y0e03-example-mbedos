#pragma once

#include "mbed-drivers/mbed.h"
#include "mbed-drivers/v2/I2C.hpp"
#include "gp2y0e03-example/gp2y0e03.hpp"

void ir_distance_async_task_init(void);

void ir_distance_async_task(void);
