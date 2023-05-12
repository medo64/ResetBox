#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "init.h"
#include "io.h"

#define DEBOUNCE_MAX   20000
#define RESET_COUNTER  20

uint16_t debounceCounter = 0;
uint8_t intensityCounter = 0;

void main(void) {
    init();
    io_startup();
    io_20V();
    io_relay_on();

    io_led_on();
    while(true) {
        watchdog();

        if (io_switch()) {
            if (debounceCounter < DEBOUNCE_MAX) {
                debounceCounter++;
            } else {
                intensityCounter++;
                if ((intensityCounter % 8) == 0) { io_led_on(); } else { io_led_off(); }
            }
        } else {
            if (debounceCounter == DEBOUNCE_MAX) {
                io_relay_on();
                for (int i=0; i<RESET_COUNTER; i++) {
                    io_led_on(); wait_short();
                    io_led_off(); wait_short();
                    watchdog();
                }
                io_relay_off();
            }
            io_led_on()
            debounceCounter = 0;
        }
    }
}
