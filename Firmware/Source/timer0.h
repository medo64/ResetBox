#pragma once
#include <xc.h>
#include <stdbool.h>

void timer0_init(void);
void timer0_reset(void);
bool timer0_wasTriggered(void);
void timer0_waitTick(void);
