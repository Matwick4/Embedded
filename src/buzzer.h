#ifndef _BUZZER_H_
#define _BUZZER_H_

#include <ti/devices/msp432p4xx/inc/msp432p401r.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/driverlib/flash.h>
#include <ti/grlib/grlib.h>

static const Timer_A_PWMConfig testPWM =
               {
                    TIMER_A_CLOCKSOURCE_ACLK, // ACLK 32 kHz clock
                    TIMER_A_CLOCKSOURCE_DIVIDER_1,
                    40,
                    TIMER_A_CAPTURECOMPARE_REGISTER_4,
                    TIMER_A_OUTPUTMODE_TOGGLE_SET,
                    20
               };


void beep();



#endif
