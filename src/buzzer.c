#include "buzzer.h"
#include <ti/devices/msp432p4xx/inc/msp432p401r.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/driverlib/flash.h>
#include <ti/grlib/grlib.h>
#include <math.h>


int championMelody[] = {

  NOTE_D5, NOTE_CS5, NOTE_D5, NOTE_CS5, NOTE_A4, 0, NOTE_FS4, NOTE_B4, NOTE_FS4,

  NOTE_G3, 0, NOTE_A3, 0,

  NOTE_D5, NOTE_E5, NOTE_FS5, NOTE_A5, NOTE_FS5, NOTE_B4, NOTE_CS5, NOTE_B4,

  NOTE_FS3, NOTE_F3, NOTE_E3, NOTE_C4, NOTE_B3,

  NOTE_B4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4, 0,
  NOTE_G5, NOTE_FS5, NOTE_G5, NOTE_FS5, NOTE_E5, 0,

  NOTE_FS5, 0, NOTE_D5, NOTE_G5,
  NOTE_FS5, 0, NOTE_D5, NOTE_G5,
  NOTE_F5, 0, NOTE_D5, NOTE_G5,
  NOTE_F5, 0, NOTE_D5,

  NOTE_A3, 0, NOTE_A3,

  NOTE_C5, NOTE_A4, NOTE_D5,
};


// Note durations
int championNoteDurations[] = {

  1, 4, 4, 2, 2, 4, 4, 2, 1,

  2, 4, 2, 4,

  1, 4, 4, 2, 2, 4, 4, 1,

  4, 4, 2, 2, 2,

  1, 4, 4, 2, 2, 2,
  1, 4, 4, 2, 2, 2,

  2, 4, 2, 4,
  2, 4, 2, 4,
  2, 4, 2, 4,
  2, 4, 1,

  8, 8, 1,

  4, 8, 1,
};

void beep(float tone, int duration_ms)
{
    TIMER_A1->CCR[0] = duration_ms;

        // need to stay here for the time needed
        /*
         * Need to make the buzzer here
         */
        Timer_A_PWMConfig testPWM =
                       {
                            TIMER_A_CLOCKSOURCE_ACLK, // ACLK 32 kHz clock
                            TIMER_A_CLOCKSOURCE_DIVIDER_1,
                            (int)tone,
                            TIMER_A_CAPTURECOMPARE_REGISTER_4,
                            TIMER_A_OUTPUTMODE_TOGGLE_SET,
                            ceil(tone/2)
                       };
        Timer_A_generatePWM(TIMER_A0_BASE,&testPWM);
        TIMER_A1->CTL |= TIMER_A_CTL_MC__UP;
        __sleep();
}


void playWeAreTheChampion()
{
    int i;
    for(i=0;i<SIZE;i++)
    {
        beep(championMelody[i],1000/championNoteDurations[i]);

    }
}
