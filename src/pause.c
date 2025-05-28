#include "HWdependent/display.h"
#include "HWdependent/pcm.h"
#include "state.h"
#include "pause.h"

void pause()
{
    clear_Display();
    gameState.buttonClicked = false;
    while(!gameState.buttonClicked)
    {
        draw_String_Centered("Pause",LCD_HORIZONTAL_MAX/2,20,false);
        draw_String_Centered("Press S1 to resume",LCD_HORIZONTAL_MAX/2,80,false);
        gotoLPM();
    }
    gameState.buttonClicked = false;
    clear_Display();
}