#include "mbed-drivers/mbed.h"

#define ASYNC 1

#if ASYNC
    #include "gp2y0e03-example/ir_async.hpp"
#else
    #include "gp2y0e03-example/ir_sync.hpp"
#endif

static DigitalOut led(LED1);
static void blinky(void) {
    led = !led;
}

void app_start(int, char**) {
#if ASYNC
    ir_distance_async_task_init();
    minar::Scheduler::postCallback(ir_distance_async_task).period(minar::milliseconds(40));
#else
    ir_distance_sync_task_init();
    minar::Scheduler::postCallback(ir_distance_sync_task).period(minar::milliseconds(40));
#endif
    minar::Scheduler::postCallback(blinky).period(minar::milliseconds(1000)); // 1Hz
}
