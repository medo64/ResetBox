#include "init.h"
#include "io.h"

void io_init(void) {
    //Setup
    nWPUEN = 0; //pullups enabled

    //PORTA [- - O O I I O O]   [- - CFG1 LED SWITCH AUX CFG3 CFG2]
    LATA   = 0b00000000;
    WPUA   = 0b00001000;
    TRISA  = 0b11001100;
    ANSELA = 0b00000000;
}

void io_init2(void) {
    //PORTA [- - O O I O O O]   [- - CFG1 LED SWITCH POWER CFG3 CFG2]
    TRISA  = 0b11001000;
}
