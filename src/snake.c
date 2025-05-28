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
    draw_String_Centered("Choose max length", DISPLAY_WIDTH/2,10,true);
    int opt[OPTIONAL_LEN];
    int i = 0;
    for(i = 0; i<OPTIONAL_LEN;i++){
        opt[i] = 10 *(i+1); // Available snake lengths (10,20,30,...)
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
    while(!gameState.buttonClicked){
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
                sprintf(s, "%3d",opt[sel]);
                draw_String_Centered((int8_t *)s,DISPLAY_WIDTH/2,50,false);
            }
            if(isButtonUpPressed()){
                gameState.buttonClicked = true;
            }
        }
        redraw = false;
        int i;
        for (i = 0; i<40000;i++){;} // wait
        gameState.buttonClicked = false;
    }
    return (opt[sel]);

}

bool snake()
{
    //gameState.buttonClicked = false;
    int maxlength = chooseSnakeLength();
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

    enum snake_dir direction = UP;
    enum snake_dir lastDir = UP;
    bool resumed = true;

    int b = 0;

    uint32_t prev_fg = get_Foreground_Color();

    while(!won && alive){
        
        b++;
        if(gameState.buttonClicked){
            //Pause 
            pause();
            resumed = true;
            
            //Paint every piece of the snake after a pause
            int j;
            for(j = 0; j<length_snake;j++)
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
            if(b == 40)
            {
                b = 0;
                //Delete last player segment
                Graphics_Rectangle last = get_Rectangle(segmX[index_tail],segmY[index_tail]);
                uint32_t bc = get_Background_Color();
                set_Foreground_Color_Translated(bc);
                fill_Rectangle(&last);
                
                //Move player
                int prevHead = index_head;
                if(length_snake>1)
                {
                   Graphics_Rectangle r = get_Rectangle_decoration(segmX[index_head],segmY[index_head]);
                    draw_Rectangle(&r);
                }
                index_tail+=1;
                index_tail %= MAX_SNAKE_LENGTH;
                index_head+=1;
                index_head %= MAX_SNAKE_LENGTH;
                segmY[index_head] = segmY[prevHead];
                segmX[index_head] = segmX[prevHead];

                switch(direction){
                    case RIGHT:
                        segmX[index_head] += SPEED;
                        lastDir = RIGHT;
                        break;
                    case LEFT:
                        segmX[index_head] -= SPEED;
                        lastDir = LEFT;
                        break;
                    case DOWN:
                        segmY[index_head] += SPEED;
                        lastDir = DOWN;
                        break;
                    case UP:
                        segmY[index_head] -= SPEED;
                        lastDir = UP;
                        break;
                }
                set_Foreground_Color_Translated(prev_fg);
                Graphics_Rectangle r = get_Rectangle(segmX[index_head],segmY[index_head]);
                fill_Rectangle(&r);

                //Look for collision with wall
                if (segmY[index_head] < 2 || segmY[index_head] > DISPLAY_HEIGHT - 2 || segmX[index_head] < 2 || segmX[index_head] > DISPLAY_WIDTH - 2)
                {
                    alive = false;
                    continue;
                }

                //Create the apple, else look for collision
                Graphics_Rectangle apple = get_Rectangle(Xapple,Yapple);
                if (Xapple == -1 || resumed)
                {
                    if(Xapple == -1){
                            
                            bool valid;
                            do
                            {
                                valid = true;
                                //New apple position
                                Xapple = rand() % (DISPLAY_WIDTH - 4) + 2;
                                Yapple = rand() % (DISPLAY_HEIGHT - 4) + 2;
                                Graphics_Rectangle apple = get_Rectangle(Xapple, Yapple);

                                //Check for overlap
                                int j;
                                for (j = 0; j < length_snake; j++)
                                {
                                    int i = (index_tail + j) % MAX_SNAKE_LENGTH;
                                    Graphics_Rectangle segment = get_Rectangle(segmX[i], segmY[i]);

                                    if (is_Overlapping(&apple, &segment))
                                    {
                                        valid = false;
                                        break;
                                    }
                                }
                            }while (!valid);
                    }
                    set_Foreground_Color(GRAPHICS_COLOR_GREEN);
                    fill_Rectangle(&apple);
                }
                Graphics_Rectangle head = get_Rectangle(segmX[index_head],segmY[index_head]);
                bool overlaps = is_Overlapping(&apple,&head);
                if(overlaps){
                    //Apple is eaten
                    Xapple = -1;
                    uint32_t bc = get_Background_Color();
                    set_Foreground_Color_Translated(bc);
                    fill_Rectangle(&apple);

                    set_Background_Color_Translated(prev_fg);
                    fill_Rectangle(&head);
                    length_snake+=1;
                    //Win condition
                    if(maxlength == MAX_SNAKE_LENGTH)
                    {
                        won = true;
                        continue;
                    }
                    index_tail-=1;
                    index_tail %=MAX_SNAKE_LENGTH;
                }
                head = get_Rectangle(segmX[index_head],segmY[index_head]);
                int k;
                for(k = 0; k<length_snake-1;k++){
                    int x = segmX[(index_tail+k)%MAX_SNAKE_LENGTH];
                    int y = segmY[(index_tail+k)%MAX_SNAKE_LENGTH];
                    if(is_Point_Within_Rectangle(&head,x,y)){
                        alive = false;
                    }
                }
                set_Foreground_Color_Translated(prev_fg);
            }   resumed = false;

        }
        int k;
        for(k = 0;k<20000;k++){;}

    }   
    return alive;
}
