#include <ti/devices/msp432p4xx/inc/msp432p401r.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void readJoystickPosition()
{
    ADC14->CTL0 |= ADC14_CTL0_SC;
}

bool isButtonUpPressed()
{
   bool res = (P1->IN & BIT1);
   return res;
}

bool isButtonDownPressed()
{
   bool res = (P1->IN & BIT4);
   return res;
}
