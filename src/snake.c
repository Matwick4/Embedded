#include "snake.h"
#include "HWdependent/display.h"
#include "HWdependent/joystick.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_SNAKE_LENGTH 100
#define OPTIONAL_LEN 10
#define SPEED 5


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
    int max_length = chooseSnakeLength();
    clear_Display();
    bool won = false;
    bool alive = true;
    gameState.buttonClicked = false;

    int length_snake = 1;
    int index_tail = 0;
    int index_head = 0;
    int segmY[MAX_SNAKE_LENGTH];
    int segmX[MAX_SNAKE_LENGTH];

    int Xapple = -1;
    int Yapple = -1;

    segmY[0] = DISPLAY_HEIGHT/2;
    segmX[0] = DISPLAY_WIDTH/2;

    snake_dir direction = UP;
    snake_dir lastDir = UP;
    bool resumed = true;

    int a = 0;
    int b = 0;

    uint32_t prev_fg = get_Foreground_Color();

    while(!won && alive){
        
        b++;
        if(gameState.buttonClicked){
            //Pause 
            pause();
            resumed = true;
            
            //Paint every piece of the snake after a pause
            for(int j = 0; j<length_snake;j++)
            {
                int ind = (j+index_tail)%MAX_SNAKE_LENGTH;
                set_Foreground_Color_Translated(prev_fg);
                Graphics_Rectangle r1 = get_Rectangle(segmX[ind],segmY[ind]);
                fill_Rectangle(&r1);
                Graphics_Rectangle r2 = get_Rectangle_decoration(segmX[ind],segmY[ind]);
                set_Foreground_Color_Translated(get_Background_Color());
                draw_Rectangle(&r2);
                set_Foreground_Color_Translated(prev_fg);
            }
        }
        else{
            readJoystickPosition();
            //Horizontal movement
            int left = (gameState.joystickX < J_LEFT_TRESH) ? (J_LEFT_TRESH - gameState.joystickX) : 0;
            int right = (gameState.joystickX > J_RIGHT_TRESH) ? (gameState.joystickX - J_RIGHT_TRESH) : 0;
            //Vertical movement
            int down = (gameState.joystickY < J_DOWN_TRESH) ? (J_DOWN_TRESH - gameState.joystickY) : 0;
            int up = (gameState.joystickY > J_UP_TRESH) ? (gameState.joystickY - J_UP_TRESH) : 0;

            if (up > 0 || down > 0) {
                if (right > up && right > down && lastDir != LEFT) {
                    direction = RIGHT;
                }
                else if (left > up && left > down && lastDir != RIGHT) {
                    direction = LEFT;
                }
                else if (up > down && lastDir != DOWN) {
                    direction = UP;
                }
                else if (down >= up && lastDir != UP) {
                    direction = DOWN;
                }
            }
            else if (right > 0 && lastDir != LEFT) {
                direction = RIGHT;
            }
            else if (left > 0 && lastDir != RIGHT) {
                direction = LEFT;
            }   
        }
    }
    
}
