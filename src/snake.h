 #ifndef _SNAKE_H_
 #define _SNAKE_H_
#include <stdbool.h>

enum snake_dir
{
    RIGHT,
    LEFT,
    UP,
    DOWN,
};
// The player chooses the maximun length of the snake
inline int chooseSnakeLength();
//Play snake. If won returns true, false otherwise
bool snake();

 #endif