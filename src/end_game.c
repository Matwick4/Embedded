#include "end_game.h"
#include "state.h"
#include "HWdependent/display.h"

void show_end_game_screen(bool won,int player){
    
    if(player == -1)
    {
        clear_Display();
        draw_String_Centered((won? "Congrats! Yow Won": "Sorry! You lost!"),DISPLAY_WIDTH/2,20,false);
        //TODO vedere se aggiungere buzzer. Andrebbe messo include relativo nel .h
        drawStringCentered("Press S1 to continue",DISPLAY_WIDTH/2,80,false);
    }
    else
    {
        if(player == 1){
            clear_Display();
            draw_String_Centered((won? "Congrats! Player 1 Won"),DISPLAY_WIDTH/2,20,false);
            //TODO vedere se aggiungere buzzer. Andrebbe messo include relativo nel .h
            drawStringCentered("Press S1 to continue",DISPLAY_WIDTH/2,80,false);
        }
        else{
            clear_Display();
            draw_String_Centered((won? "Congrats! Player 2 Won"),DISPLAY_WIDTH/2,20,false);
            //TODO vedere se aggiungere buzzer. Andrebbe messo include relativo nel .h
            drawStringCentered("Press S1 to continue",DISPLAY_WIDTH/2,80,false);
        }
    }
}