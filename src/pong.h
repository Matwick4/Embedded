#ifndef _PONG_H_
#define _PONG_H_

#include <stdbool.h>
typedef struct ball_s {

	int x, y; //position on the screen
	int w,h; // ball width and height
	int dx, dy; // movement vector

} ball_t;

typedef enum paddle_direction_e {

    UP, // paddle up
    DOWN // paddle down

} paddle_direction_t;
typedef struct paddle_s {

	int x,y; // position on the screen
	int w,h; // paddle width and height
	paddle_direction_t last_dir;

} paddle_t;


//Pong game
bool pong();
//Initialize starting pos of ball and paddles
static void init(); 
//Check score of players
int score_check();
//Check if there is a collision between ball and paddle. If return value == 1 then collision, if 0 no collision
int collision_check(ball_t, paddle_t);
//Move the ball 
static void move_ball();
static void change_ball_vector(int);
//Mode paddle of first player
static void move_paddle_first_player(paddle_direction_t);
//Move paddle of second player
static void move_paddle_second_player(paddle_direction_t);
//Move AI paddle (if selected)
static void move_paddle_ai();
//Draw ball on the screen
static void draw_ball();
//Draw paddle on the screen
static void draw_paddle(int paddle);
//Draw menu
static void draw_pong_menu();
//Draw the game options (auxiliary function of the menu)
static void draw_pong_options(int step);
//Draw title of the gamemode selection menu 
void draw_title_play_options();
//Clear given rectangle
void clean_rect(const Graphics_Rectangle *rect);
//Draw a selectable rectangle
Graphics_Rectangle draw_selection_rect(const int,const int);

#endif
