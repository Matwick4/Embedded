#ifndef _MENU_H_
#define _MENU_H_
#include <ti/grlib/grlib.h>
#include <stdbool.h>

//Show the main menu where one of the two games can be selected 
//TODO CHECK IF TO PUT BIRGHTNESS
void show_main_menu();
void show_title();
void show_games_options(int); // TODO check if options are the games or not

Graphics_Rectangle draw_selection_rectangle(const int selected, const int step);

//TODO CHECK IF BRIGHTNESS CAN BE ADDED 
//void _drawLightDarkSwitch();
//void adjustBrightness(bool *previouslyDark);
#endif
