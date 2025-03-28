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
static void init();
int score_check();
int collision_check(ball_t, paddle_t);
static void move_ball();
static void move_paddle_first_player(int );
static void move_paddle_second_player(int);
static void move_paddle_ai();
static void draw_ball();
static void draw_paddle();

#endif