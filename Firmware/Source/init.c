#include <xc.h>
#include "init.h"

void init(void) {
    //1 MHz
    OSCCONbits.IRCF = 0b1011;
    OSCCONbits.SCS  = 0b10;
    __delay_us(5);
}
