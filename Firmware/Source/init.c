#include <xc.h>
#include "init.h"

void init(void) {
    //1 MHz
    OSCCONbits.IRCF = 0b1011;
    OSCCONbits.SCS  = 0b10;
    __delay_us(5);

    //Setup
    nWPUEN = 0; //pullups enabled
    //PORTA [- - I O - O - -]   [- - CFG1 LED SWITCH RELAY/AUX CFG3 CFG2]
    LATA   = 0b00000000;
    WPUA   = 0b00010000;
    TRISA  = 0b11001100;
}
