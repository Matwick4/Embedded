#include "hw_init.h"
/*      TODO FIX PATHS !!!!!!   
#include "../../LcdDriver/Crystalfontz128x128_ST7735.h"
#include "../../LightSensor/HAL_OPT3001.h"
#include "../../LightSensor/HAL_I2C.h"
#include <ti/devices/msp432p4xx/inc/msp432p401r.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/driverlib/flash.h>
#include <ti/grlib/grlib.h>
*/

void hwInit()
{
    // Halt WDT
    WDT_A_holdTimer();
    _configure_ADC();
    
    // Disable master interrupts
    Interrupt_disableMaster();

    // Set core voltage level to VCORE1
    PCM_setCoreVoltageLevel(PCM_VCORE1);

    // Set 2 flash wait states for Flash bank 0 and 1
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);

    // Initialize clock System
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

void HW_Init()
{
    
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

}

void ADC_config()
{
    
}
