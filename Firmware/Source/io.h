#ifndef IO_H
#define	IO_H

    #include <xc.h>

    void io_startup(void);

    #define io_led_off()    LATAbits.LATA4 = 0;
    #define io_led_on()     LATAbits.LATA4 = 1;

    #define io_relay_off()  LATAbits.LATA2 = 0;
    #define io_relay_on()   LATAbits.LATA2 = 1;

    #define io_switch()     PORTAbits.RA3

    #define io_5V()         LATAbits.LATA5 = 1; LATAbits.LATA0 = 0; LATAbits.LATA1 = 0;
    #define io_9V()         LATAbits.LATA5 = 0; LATAbits.LATA0 = 0; LATAbits.LATA1 = 0;
    #define io_12V()        LATAbits.LATA5 = 0; LATAbits.LATA0 = 0; LATAbits.LATA1 = 1;
    #define io_15V()        LATAbits.LATA5 = 0; LATAbits.LATA0 = 1; LATAbits.LATA1 = 1;
    #define io_20V()        LATAbits.LATA5 = 0; LATAbits.LATA0 = 1; LATAbits.LATA1 = 0;

#endif	/* IO_H */
