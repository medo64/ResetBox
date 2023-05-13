#pragma once

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = ON        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = ALL        // Flash Memory Self-Write Protection (000h to 1FFFh write protected, no addresses may be modified by EECON control)
#if defined(_12F1571)
    #pragma config PLLEN = OFF  // PLL Disable
#endif
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = HI        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), high trip point selected.)
#if defined(_12F1571)
    #pragma config LPBOREN = ON // Low-Power Brown Out Reset (Low-Power BOR is enabled)
#else
    #pragma config LPBOR = ON   // Low-Power Brown Out Reset (Low-Power BOR is enabled)
#endif
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)


#include <xc.h>

#ifndef INIT_H
    #define	INIT_H

    #define _XTAL_FREQ 1000000

    void init(void);
    void init2(void);

    #define reset()       __asm("RESET")
    #define watchdog()    __asm("CLRWDT")
    #define wait_short()  __delay_ms(100)

#endif	/* INIT_H */
