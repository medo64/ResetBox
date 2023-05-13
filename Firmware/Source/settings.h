#pragma once

#define SETTING_DEFAULT_VOLTAGE  20

#define _SETTINGS_FLASH_RAW {                                                   \
                              SETTING_DEFAULT_VOLTAGE,                          \
                              0, 0, 0, 0, 0, 0, 0,                              \
                              0, 0, 0, 0, 0, 0, 0, 0,                           \
                            }  // reserving space because erase block is 16 words (32 bytes)
#define _SETTINGS_FLASH_LOCATION  0x03F0
const uint8_t _SETTINGS_PROGRAM[] __at(_SETTINGS_FLASH_LOCATION) = _SETTINGS_FLASH_RAW;

typedef struct {
    uint8_t Voltage;
    uint8_t Reserved[15];
} SettingsRecord;

SettingsRecord Settings;


/** Initializes settings. */
void settings_init(void);

/** Saves settings to EEPROM. */
void settings_save(void);


uint8_t settings_getVoltage(void);
void settings_setVoltage(const uint8_t value);
