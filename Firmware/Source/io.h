#ifndef IO_H
#define	IO_H

    #include <xc.h>

    void io_startup(void);

    #define io_led_off()    LATAbits.LATA4 = 0;
    #define io_led_on()     LATAbits.LATA4 = 1;

    #define io_relay_off()  LATAbits.LATA2 = 1;
    #define io_relay_on()   LATAbits.LATA2 = 0;

    #define io_switch()     PORTAbits.RA5

#endif	/* IO_H */
