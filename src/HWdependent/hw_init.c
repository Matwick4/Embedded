#include "hw_init.h"
#include "../state.h"
#include "../../LcdDriver/Crystalfontz128x128_ST7735.h"
//#include "../../LightSensor/HAL_OPT3001.h"
//#include "../../LightSensor/HAL_I2C.h"
#include <ti/devices/msp432p4xx/inc/msp432p401r.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/driverlib/flash.h>
#include <ti/grlib/grlib.h>

#include <stdio.h>


void HW_Init()
{
    // Halt WDT
    WDT_A_holdTimer();
    ADC_config();
    
    // Disable master interrupts
    Interrupt_disableMaster();

    // Set core voltage level to VCORE1
    PCM_setCoreVoltageLevel(PCM_VCORE1);

    // Set 2 flash wait states for Flash bank 0 and 1
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);

    // Initialize clock system
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    //buzzerInit();
    graphic_init();
    init_button();
    //_lightSensorInit();
    __enable_irq();
}

void graphic_init()
{
    // Display initialization
    Crystalfontz128x128_Init();

    // Set default screen orientation
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    // Initializes graphics context
    Graphics_Context *gContext = &gameState.gContext;
    Graphics_initContext(gContext, &g_sCrystalfontz128x128,&g_sCrystalfontz128x128_funcs);

    Graphics_setForegroundColor(gContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(gContext, GRAPHICS_COLOR_WHITE);
    GrContextFontSet(gContext, &g_sFontFixed6x8);
    Graphics_clearDisplay(gContext);
}

void init_button()
{
    // S1 init J4.33 -> P5.1
    P5->SEL0 &= ~BIT1;
    P5->SEL1 &= ~BIT1;
    P5->DIR &= ~BIT1;
    P5->OUT |= BIT1;
    P5->REN |= BIT1;

    // S2 init J4.32 -> P3.5

    P3->SEL0 &= ~BIT5;
    P3->SEL1 &= ~BIT5;
    P3->DIR &= ~BIT5;
    P3->OUT |= BIT5;
    P3->REN |= BIT5;


    NVIC->ISER[1] = 1 << ((PORT5_IRQn) & 31);
    NVIC->ISER[1] = 1 << ((PORT3_IRQn) & 31);

    P2->SEL0 &= ~(BIT1 | BIT2);
       P2->SEL1 &= ~(BIT1 | BIT2);

       /* set Port 2.1 and 2.2 as output */
       P2->DIR |= (BIT1 | BIT2);

       /* clear the pins */
       P2->OUT &= ~(BIT1 | BIT2);

}

void ADC_config()
{
    
    //J3.26->P4.4
    //Pin 4.4, joystick y
    P4->SEL0 &= ~BIT4;
    P4->SEL1 &= ~BIT4;
    P4->DIR &= ~BIT4;
    P4->REN &= ~BIT4;
    P4->OUT |= BIT4;
    P4->IFG &= ~BIT4;
    P4->IES |= BIT4;
    P4->IE &= ~BIT4;

    //J1.2->P6.0
    //Pin 6.0 joystick x
    P6->SEL0 &= ~BIT0;
    P6->SEL1 &= ~BIT0;
    P6->DIR &= ~BIT0;
    P6->REN &= ~BIT0;
    P6->OUT |= BIT0;
    P6->IFG &= ~BIT0;
    P6->IES |= BIT0;
    P6->IE &= ~BIT0;

    //configure adc
    ADC14->CTL0 &= ~ADC14_CTL0_ENC; //disable conversions

    while (REF_A->CTL0 & REF_A_CTL0_GENBUSY)
        ;                                            //wait while generator is busy
    REF_A->CTL0 = REF_A_CTL0_VSEL_0 | REF_A_CTL0_ON; //enable internal 1.2V ref

    ADC14->CTL0 |= ADC14_CTL0_CONSEQ_3 | ADC14_CTL0_SHT0_5 | ADC14_CTL0_ON | ADC14_CTL0_SHP;
    ADC14->CTL1 |= ADC14_CTL1_CH2MAP | ADC14_CTL1_RES__14BIT;

    //y direction joystick A9 (Y)
    ADC14->MCTL[1] |= ADC14_MCTLN_VRSEL_0 | ADC14_MCTLN_INCH_9 | ADC14_CTL1_CSTARTADD_MASK;
    ADC14->IER0 |= ADC14_IER0_IE1; //enable interrupts
    //x direction joystick A15 (X)
    ADC14->MCTL[2] |= ADC14_MCTLN_VRSEL_0 | ADC14_MCTLN_INCH_15 | ADC14_CTL1_CSTARTADD_MASK;
    ADC14->MCTL[2] |= ADC14_MCTLN_EOS; //make this the end of sequence
    ADC14->IER0 |= ADC14_IER0_IE2;     //enable interrupts

    while (!(REF_A->CTL0 & REF_A_CTL0_GENRDY))
        ;                          //wait for generator to settle
    ADC14->CTL0 |= ADC14_CTL0_ENC; //enable conversions
    NVIC_EnableIRQ(ADC14_IRQn);
    
    /* //TODO check should be the same but less verbose

    // Configure ADC module
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1, 0);

    // Configure GPIO pins for analog input
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION); // X-axis
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION); // Y-axis

    // Configure memory buffers for X (A15) and Y (A9)
    ADC14_configureMultiSequenceMode(ADC_MEM2, ADC_MEM1, true);
    ADC14_configureConversionMemory(ADC_MEM2, ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    ADC_INPUT_A15, false);
    ADC14_configureConversionMemory(ADC_MEM1, ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    ADC_INPUT_A9, false);

    // Enable ADC
    ADC14_enableConversion();
    */
}
void ADC14_IRQHandler()
{
    __disable_irq();

    if (ADC14->IFGR0 & ADC14_IFGR0_IFG1)
    {
        gameState.joystickY = ADC14->MEM[1];

    }
    if (ADC14->IFGR0 & ADC14_IFGR0_IFG2)
    {
        gameState.joystickX = ADC14->MEM[2];
    }
    __enable_irq();
}

// Here in the IRQ we check the variable


