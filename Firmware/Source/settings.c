#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "settings.h"


void settings_init() {
    uint8_t* settingsPtr = (uint8_t*)&Settings;
    for (uint8_t i = 0; i < sizeof(Settings); i++) {
        *settingsPtr = _SETTINGS_PROGRAM[i];
        settingsPtr++;
    }
}

void settings_save() {
    bool hadInterruptsEnabled = (INTCONbits.GIE != 0);  // save if interrupts enabled
    INTCONbits.GIE = 0;  // disable interrupts
    PMCON1bits.WREN = 1;  // enable writes

    uint16_t address = _SETTINGS_FLASH_LOCATION;
    uint8_t* settingsPtr = (uint8_t*)&Settings;

    // erase
    PMADR = address;         // set location
    PMCON1bits.CFGS = 0;     // program space
    PMCON1bits.FREE = 1;     // erase
    PMCON1bits.WREN = 1;     // allows program/erase cycles
    PMCON2 = 0x55;           // unlock
    PMCON2 = 0xAA;           // unlock
    PMCON1bits.WR = 1;       // begin erase
    asm("NOP"); asm("NOP");  // forced

    // write
    PMCON1bits.WREN = 1;        // allows program/erase cycles
    PMCON1bits.CFGS = 0;        // program space
    for (uint8_t  i = 1; i <= sizeof(Settings); i++) {
        uint8_t latched = (i == sizeof(Settings)) ? 0 : 1;  // latch load is done for all except last

        PMCON1bits.LWLO = latched;  // load write latches
        PMADR = address;            // set location
        PMDATL = *settingsPtr;      // load data
        PMCON2 = 0x55;              // unlock
        PMCON2 = 0xAA;              // unlock
        PMCON1bits.WR = 1;          // begin write
        asm("NOP"); asm("NOP");     // forced
        address++;                  // move write address
        settingsPtr++;              // move data pointer
    }

    PMCON1bits.WREN = 0;  // disable writes
    if (hadInterruptsEnabled) { INTCONbits.GIE = 1; }  // restore interrupts
}


uint8_t settings_getVoltage() {
    uint8_t value = Settings.Voltage;
    return (value > 0) ? value : SETTING_DEFAULT_VOLTAGE;
}

void settings_setVoltage(const uint8_t value) {
    Settings.Voltage = value;
}
