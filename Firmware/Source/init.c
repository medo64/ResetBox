#include <xc.h>
#include "init.h"

void init(void) {
    //1 MHz
    OSCCONbits.IRCF = 0b1011;
    OSCCONbits.SCS  = 0b10;
    __delay_us(5);

    //Setup
    nWPUEN = 0; //pullups enabled
    //PORTA [- - I O - O - -]   [- - SWITCH LED ICSP RELAY ICSP ICSP]
    LATA   = 0b00000100;
    WPUA   = 0b00100000;
    TRISA  = 0b11101011;
}
