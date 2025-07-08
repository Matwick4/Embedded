#include "src/pong.h"
#include "src/HWdependent/pcm.h"
#include "src/HWdependent/hw_init.h"
#include "src/menu.h"
#include "src/state.h"
#include "src/end_game.h"

#include "src/HWdependent/joystick.h"
#include "src/HWdependent/display.h"



int main(void)
{
    gameState.buttonClicked = false;
    gameState.joystickY = J_V_INITIAL;
    gameState.joystickX = J_H_INITIAL;


    HW_Init();

    show_main_menu();
    int winner_pong =0 ;
    while(true)
    {
        switch(gameState.game_selected){

            case 0: 
                winner_pong = pong();
                gameState.game_selected = -1;
                
            break;

            case -1:
                show_main_menu();
            break;

            default:
                winner_pong = -1;
            break;
        }
      //  gotoLPM();
        
    }
}
