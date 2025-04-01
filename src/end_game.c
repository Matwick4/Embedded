#include "end_game.h"
#include "state.h"
#include "HWdependent/display.h"

void show_end_game_screen(bool won){
    clear_Display();
    draw_String_Centered((won? "Congrats! Yow Won": "Sorry! You lost!"),DISPLAY_WIDTH/2,20,false);
    //TODO vedere se aggiungere buzzer. Andrebbe messo include relativo nel .h
    drawStringCentered("Press S1 to continue",DISPLAY_WIDTH/2,80,false);
}