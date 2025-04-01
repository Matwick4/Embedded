#include <stdbool.h>
#include <cstdint>
//#include "ti/grlib/grlib.h"
#ifndef _STATE_H_
#define _STATE_H_

//TODO CHECK FOR THESE ONES 
#define J_UP_TRESH 10000
#define J_DOWN_TRESH 6000
#define J_RIGHT_TRESH 10000
#define J_LEFT_TRESH 6000
#define J_H_INITIAL 8000
#define J_V_INITIAL 8000

/*
typedef enum
{
    DARK,
    LIGHT,
    AUTO
} brightnessType;
*/
typedef struct 
{
    int game_selected;
    bool buttonClicked;

    uint16_t joystickX;
    uint16_t joystickY;


    Graphics_Context gContext;
    //brightnessType brightness;
    
}GameState;

GameState gameState;

#endif
