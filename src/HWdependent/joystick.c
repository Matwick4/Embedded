#include <ti/devices/msp432p4xx/inc/msp432p401r.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void readJoystickPosition()
{
    ADC14->CTL0 |= ADC14_CTL0_SC;
}

bool isButtonUpPressed()
{
    return (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_LOW);
}

bool isButtonDownPressed()
{
    return (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4) == GPIO_INPUT_PIN_LOW);
}