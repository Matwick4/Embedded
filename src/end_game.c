#include "end_game.h"
#include "state.h"
#include "HWdependent/display.h"

void show_end_game_screen(bool won,int player){
    
    if(player == -1)
    {
        clear_Display();
        draw_String_Centered((won? "Congrats! Yow Won": "Sorry! You lost!"),DISPLAY_WIDTH/2,20,false);
        //TODO vedere se aggiungere buzzer. Andrebbe messo include relativo nel .h
        draw_String_Centered("Press S1 to continue",DISPLAY_WIDTH/2,80,false);
    }
    else
    {
        if(player == 1){
            clear_Display();
            draw_String_Centered((won? "Congrats! Player 1 Won" : "Sorry Player 2 lost"),DISPLAY_WIDTH/2,20,false);
            //TODO vedere se aggiungere buzzer. Andrebbe messo include relativo nel .h
            draw_String_Centered("Press S1 to continue",DISPLAY_WIDTH/2,80,false);
        }
        else{
            clear_Display();
            draw_String_Centered((won? "Congrats! Player 2 Won" :"Sorry Player 2 lost"),DISPLAY_WIDTH/2,20,false);
            //TODO vedere se aggiungere buzzer. Andrebbe messo include relativo nel .h
            draw_String_Centered("Press S1 to continue",DISPLAY_WIDTH/2,80,false);
        }
    }
}
