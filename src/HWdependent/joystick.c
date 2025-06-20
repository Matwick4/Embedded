#include <ti/devices/msp432p4xx/inc/msp432p401r.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void readJoystickPosition()
{
    ADC14->CTL0 |= ADC14_CTL0_SC;
}

bool isButtonDownPressed()
{
    if (P3->IN & BIT5)
        return true;
    else
        return false;
}
bool isButtonUpPressed()

{
    if (P5->IN & BIT1)
        return true;
    else
        return false;
}
