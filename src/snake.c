#include "snake.h"
#include "HWdependent/display.h"
#include "HWdependent/joystick.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_SNAKE_LENGTH 100
#define OPTIONAL_LEN 10


inline int chooseSnakeLength()
{
    clear_Display();
    draw_String_Centered("Choose max snake length", DISPLAY_WIDTH/2,10,true);
    int opt[OPTIONAL_LEN];
    
    for(int i = 0; i<OPTIONAL_LEN;i++){
        opt[i] = 10 *(i+1) // Available snake lengths (10,20,30,...)
    }
    int sel = 0;
    Graphics_Rectangle r;
    r.xMin = 0;
    r.xMax = DISPLAY_WIDTH;
    r.yMin = 40;
    r.yMax = 60;

    uint32_t prev_FgColor = get_Foreground_Color();

    int k = 0;
    bool redraw = true;
    while(!gameState.buttonClicked()){
        k++;
        readJoystickPosition();
        
        if (k == 10 || redraw){
            k = 0;
            if (gameState.joystickY < J_DOWN_TRESH){
                gameState.joystickY = J_DOWN_TRESH + 1;
                sel--;
                
                if(sel < 0){
                    sel = OPTIONAL_LEN -1;
                }
                redraw = true;
            }
            else if (gameState.joystickY > J_UP_TRESH){
                gameState.joystickY = J_UP_TRESH -1;
                sel++;
                sel %= OPTIONAL_LEN;
                redraw = true;
            }
            if (redraw){
                set_Foreground_Color_Translated(get_Background_Color());
                fill_Rectangle(&r);
                set_Foreground_Color_Translated(prev_FgColor);
                char s[4];
                sprintf(string, "%3d",opt[sel]);
                draw_String_Centered((int8_t *)s,DISPLAY_WIDTH/2,50,false);
            }
        }
        redraw = false;
        for (int i = 0; i<40000;i++){;} // wait
        gameState.buttonClicked = false;
        return opt[sel];
    }
}

bool snake()
{
    
}
