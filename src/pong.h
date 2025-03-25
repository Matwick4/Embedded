#ifndef _PONG_H_
#define _PONG_H_
#include <stdbool.h>
typedef struct ball_s {

	int x, y; //position on the screen 
	int w,h; // ball width and height
	int dx, dy; // movement vector 

} ball_t;

typedef struct paddle {

	int x,y; // position on the screen
	int w,h; // paddle width and height

} paddle_t;

bool pong();

#endif