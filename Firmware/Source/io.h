#pragma once
#include <xc.h>

void io_init(void);
void io_init2(void);

#define io_led_off()      LATAbits.LATA4 = 0;
#define io_led_on()       LATAbits.LATA4 = 1;
#define io_led_toggle()   LATAbits.LATA4 = !LATAbits.LATA4;

#define io_power_off()    LATAbits.LATA2 = 0;
#define io_power_on()     LATAbits.LATA2 = 1;

#define io_switch_main()  PORTAbits.RA3
#define io_switch_cfg()   PORTAbits.RA2

#define io_5V()           LATAbits.LATA5 = 1; LATAbits.LATA0 = 0; LATAbits.LATA1 = 0;
#define io_9V()           LATAbits.LATA5 = 0; LATAbits.LATA0 = 0; LATAbits.LATA1 = 0;
#define io_12V()          LATAbits.LATA5 = 0; LATAbits.LATA0 = 0; LATAbits.LATA1 = 1;
#define io_15V()          LATAbits.LATA5 = 0; LATAbits.LATA0 = 1; LATAbits.LATA1 = 1;
#define io_20V()          LATAbits.LATA5 = 0; LATAbits.LATA0 = 1; LATAbits.LATA1 = 0;
