#include "state.h"
#include "menu.h"
#include <stdio.h>
#include "HWdependent/joystick.h"
#include "HWdependent/display.h"

const char *const game_opt[] = {"Pong","Snake"};
const int lengthOptMenu = 2;
const int offsetOptMenu = 60;

void show_main_menu(){

        clear_Display();
        int selected_curr = 0;
        int step = get_Font_Height()*2;

        int prev_sel = selected_curr;
        gameState.buttonClicked = false;

        Graphics_Rectangle prevRect;
        prevRect.xMin = 0;
        prevRect.xMax = 0;
        prevRect.yMin = 0;
        prevRect.yMax = 0;

        while(!(gameState.buttonClicked))
        {
            readJoystickPosition();

            if(gameState.joystickY < J_DOWN_TRESH)
            {
                selected_curr = min(selected_curr+1,lengthOptMenu-1);
                gameState.joystickY = J_DOWN_TRESH+1;
                int j;
                for(j = 0;j<400000;j++){;}

            }
            else if(gameState.joystickY > J_UP_TRESH)
            {
                selected_curr = max(selected_curr-1,0);
                gameState.joystickY = J_UP_TRESH-1;
                int j;
                for(j = 0;j<400000;j++){;}


            }
            if(isButtonUpPressed()){
                gameState.buttonClicked = true;
            }
            show_title();

            if(selected_curr != prev_sel)
            {
                clean_rect(&prevRect);
                prev_sel = selected_curr;
            }
            prevRect = draw_selection_rectangle(selected_curr,step);
            show_games_options(step);

            /*
            if(gameState.buttonClicked)
            {
                if(selected_curr == lengthOptMenu)
                {
                    gameState.buttonClicked = false;
                }
            }
            */
        }
        gameState.buttonClicked = false;
        gameState.game_selected = selected_curr;

}

void show_title(){
    uint32_t pc = get_Foreground_Color();
    set_Foreground_Color(GRAPHICS_COLOR_GREEN);
    int w = DISPLAY_WIDTH;
    const Graphics_Font *prevFont = get_Font();
    const Graphics_Font *titleFont = &g_sFontCm20b;
    set_Font(titleFont);
    draw_String_Centered("Games",w/2,22,false);
    set_Font(prevFont);
    set_Foreground_Color_Translated(pc);
}
void show_games_options(int s){
    int yOffs = offsetOptMenu;
    int hwidth = DISPLAY_WIDTH/2;
    int k;
    for(k = 0;k<lengthOptMenu;k++)
    {
        draw_String_Centered(game_opt[k],hwidth,yOffs,false);
        yOffs+=s;
    }
}

Graphics_Rectangle draw_selection_rectangle(const int sel, const int s)
{
       const int padding = 20;
       Graphics_Rectangle rect;
       rect.xMax = DISPLAY_WIDTH - padding;
       rect.xMin = padding;
       rect.yMin = offsetOptMenu + sel * s - s/2 ;
       rect.yMax = offsetOptMenu + sel * s + s/2 ;

       if(sel == lengthOptMenu)
       {
           rect.xMax = DISPLAY_WIDTH-1;
           rect.xMin = DISPLAY_WIDTH-20;
           rect.yMin = DISPLAY_HEIGHT-15;
           rect.yMax = DISPLAY_HEIGHT-2;
       }
       draw_Rectangle(&rect);
       return rect;
}
