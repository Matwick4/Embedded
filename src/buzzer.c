#include "buzzer.h"
#include <ti/devices/msp432p4xx/inc/msp432p401r.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/driverlib/flash.h>
#include <ti/grlib/grlib.h>

void beep()
{
           Timer_A_generatePWM(TIMER_A0_BASE,&testPWM);

           int k=0;
           for(k=0;k<10000;k++); // this maybe do with timer

           Timer_A_stopTimer(TIMER_A0_BASE);
}
