#include "timer.h"

#include <ti/devices/msp432p4xx/driverlib/timer_a.h>

void startTimer()
{
    TIMER_A0->CTL |= TIMER_A_UP_MODE;
}

void stopTimer()
{
    TIMER_A0->CTL |= TIMER_A_STOP_MODE;
}
