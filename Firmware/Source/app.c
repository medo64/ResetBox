#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "init.h"
#include "io.h"
#include "timer0.h"
#include "settings.h"

#define COUNTER_CONFIG_MAX     72  //  3 seconds
#define COUNTER_RESET_MAX      48  //  2 seconds
#define COUNTER_POWEROFF_MAX  120  //  5 seconds
#define COUNTER_CANCEL_MAX    240  // 10 seconds


void setVoltage(uint8_t voltage) {
    switch (voltage) {
        case 9: io_9V(); break;
        case 12: io_12V(); break;
        case 15: io_15V(); break;
        case 20: io_20V(); break;
        default: io_5V(); break;
    }
}

void work(void) {
    io_power_on();
    io_led_on();
    setVoltage(settings_getVoltage());

    uint16_t resetCounter = 0;

    while(true) {
        watchdog();

        if (io_switch_main()) {

            if (timer0_wasTriggered()) {
                resetCounter++;

                if (resetCounter == COUNTER_RESET_MAX) {  // held it long enough
                    uint8_t intensityRatioCounter = 0;
                    uint8_t cancelCounter = 0;
                    while(io_switch_main()) {  // wait until released
                        watchdog();
                        if (timer0_wasTriggered()) {
                            cancelCounter++;
                            if (cancelCounter == COUNTER_CANCEL_MAX) {  // well, canceled reset
                                io_led_on();
                                while(io_switch_main()) { watchdog(); }  // wait until released
                                resetCounter = 0;
                                continue;  // start from beginning
                            }
                        }

                        if (intensityRatioCounter == 0) { io_led_on(); } else { io_led_off(); }
                        intensityRatioCounter++;
                        if (intensityRatioCounter > 7) { intensityRatioCounter = 0; }  // just to decrease brightness a bit 
                    }

                    // power off
                    if (resetCounter == COUNTER_RESET_MAX) {
                        timer0_reset();
                        io_power_off();
                        uint8_t powerCounter = 0;
                        while(powerCounter < COUNTER_POWEROFF_MAX) {
                            watchdog();
                            if (timer0_wasTriggered()) {
                                powerCounter++;
                                if (powerCounter % 6 == 0) { io_led_toggle(); }
                            }
                        }
                        io_power_on();
                        io_led_on();
                        resetCounter = 0;
                    }
                }
            }

        } else {
            timer0_reset();
            resetCounter = 0;
            io_led_on()
        }
    }
}

void config(void) {
    io_led_off();
    while(io_switch_cfg()) { watchdog(); }  // wait to depress

    uint8_t currentVoltage = settings_getVoltage();
    while(true) {
        watchdog();
        if (io_switch_cfg()) {
            timer0_waitTick();  // poor man's debounce
            if (!io_switch_cfg()) { continue; }

            uint8_t saveCounter = 0;
            timer0_reset();
            while (io_switch_cfg()) {  // figure out if it's a long press
                watchdog();
                if (timer0_wasTriggered()) {
                    if (saveCounter > 24) { io_led_toggle(); }  // only toggle once we're after 1 second
                    saveCounter++;
                    if (saveCounter == COUNTER_CONFIG_MAX) {  // save settings
                        io_led_off();
                        settings_setVoltage(currentVoltage);
                        settings_save();
                        io_led_on();
                        while (io_switch_cfg()) {  // wait for depress
                            watchdog();
                        }
                        reset();  // proceed with normal startup
                    }
                }
            }
            io_led_off();

            switch (currentVoltage) {
                case 5: currentVoltage = 9; break;
                case 9: currentVoltage = 12; break;
                case 12: currentVoltage = 15; break;
                case 15: currentVoltage = 20; break;
                default: currentVoltage = 5; break;
            }
            setVoltage(currentVoltage);
        }

        if (io_switch_main()) {  // just for troubleshooting
            io_led_on();
        } else {
            io_led_off();
        }
    }
}

void main(void) {
    init();
    io_init();
    timer0_init();
    settings_init();

    setVoltage(settings_getVoltage());

    // startup flash
    io_led_on();
    for (uint8_t i = 0; i < 6; i++) {
        watchdog();
        timer0_waitTick();
        io_led_toggle();
    }

    // check for config button
    bool useConfig = false;
    uint8_t waitCounter = 0;
    while (true) {
        watchdog();
        if (io_switch_cfg()) {
            if (timer0_wasTriggered()) {
                waitCounter++;
                io_led_toggle();
                if (waitCounter == COUNTER_CONFIG_MAX) {
                    useConfig = true;
                    break;
                }
            }
        } else {
            break;
        }
    }

    if (useConfig) {
        config();
    }

    // normal startup
    io_init2();
    work();
}
