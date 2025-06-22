#include "HWdependent/display.h"
#include "HWdependent/pcm.h"
#include "HWdependent/joystick.h"
#include "state.h"
#include "pause.h"

void pause()
{
    clear_Display();
    gameState.buttonClicked = false;
    while(!gameState.buttonUpPressed)
    {
        draw_String_Centered("Pause",LCD_HORIZONTAL_MAX/2,20,false);
        draw_String_Centered("Press S1 to resume",LCD_HORIZONTAL_MAX/2,80,false);
        if(!isButtonUpPressed()){
                   gameState.buttonUpPressed=true;
        }
        //gotoLPM(); // it want an interrupt
    }
    gameState.buttonClicked = false;
    gameState.buttonUpPressed=false;
    clear_Display();
}
