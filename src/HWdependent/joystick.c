//#include <ti/devices/msp432p4xx/inc/msp432p401r.h> fix the path

void readJoystickPosition()
{
    ADC14->CTL0 |= ADC14_CTL0_SC;
}