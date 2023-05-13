#include <xc.h>
#include <stdbool.h>
#include "timer0.h"

// 24x per second
#define TMR0_START 107
#define POSTSCALER_TARGET 41

uint8_t postscaler = 0;

void timer0_init(void) {
    OPTION_REGbits.TMR0CS = 0;    // FOSC/4
    OPTION_REGbits.PSA = 1;       // Prescaler is not assigned to the Timer0 module
    TMR0 = 96;
}

void timer0_reset(void) {
    TMR0 = TMR0_START;
    postscaler = 0;
}

bool timer0_wasTriggered(void) {  // 24x per second
    if (INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        postscaler++;
        if (postscaler == POSTSCALER_TARGET) { 
            postscaler = 0;
            TMR0 = TMR0_START;
            return true;
        }
    }
    return false;
}

void timer0_waitTick(void) {
    timer0_reset();
    while (!timer0_wasTriggered()) {
        asm("CLRWDT");
    }
}
