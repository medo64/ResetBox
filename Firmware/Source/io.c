#include "init.h"
#include "io.h"

void io_startup(void) {
    io_led_on();  wait_short();
    io_led_off(); wait_short();
    watchdog();
    io_led_on();  wait_short();
    io_led_off(); wait_short();
    watchdog();
    io_led_on();  wait_short();
    io_led_off();
    watchdog();
}
