#include "src/snake.h"
#include "src/pong.h"
#include "src/HWdependent/pcm.h"
#include "src/HWdependent/hw_init.h"
#include "src/menu.h"
#include "src/state.h"
#include "src/end_game.h"



int main(void)
{
    gameState.buttonClicked = false;
    gameState.joystickY = J_V_INITIAL;
    gameState.joystickX = J_H_INITIAL;

    HW_Init();
    while(true)
    {
        gameState.game_selected = 0;
        show_main_menu();
        int winner_pong;
        bool winner_snake;
        switch(gameState.game_selected){

            case 0: 
                winner_pong = pong();
                show_end_game_screen(true,winner_pong);
                
            break;

            case 1: 
                winner_snake = snake();
                show_end_game_screen(winner_snake,-1);
            break;

            case -1:
                //back to the main menu
            break;

            default:
                winner_snake = false;
                winner_pong = -1;
            break;
        }
        gotoLPM();
        
    }
}
