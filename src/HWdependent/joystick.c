#include <ti/devices/msp432p4xx/inc/msp432p401r.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


void readJoystickPosition()
{
    ADC14->CTL0 |= ADC14_CTL0_SC;
}
bool isJoystickButtonPressed()
{
    if (!(P4IN & GPIO_PIN1))
    {
        int i;
        for(i=0;i<3000;i++);
        return true;
    }

    else

    {
        int i;
        for(i=0;i<3000;i++);
        return false;
    }

}
bool isButtonDownPressed()
{
    if (P3->IN & BIT5)
    {
        int i;
        for(i=0;i<3000;i++);
        return true;
    }

    else
    {
        int i;
        for(i=0;i<3000;i++);
        return false;
    }

}
bool isButtonUpPressed()

{
    if (P5->IN & BIT1)
    {
        int i;
        for(i=0;i<3000;i++);
        return true;
    }

    else
    {
        int i;
        for(i=0;i<3000;i++);
        return false;
    }

}
