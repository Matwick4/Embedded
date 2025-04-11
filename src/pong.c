#include "pong.h"
#include "HWdependent/display.h"
#include "HWdependent/joystick.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_SCORE 10;
//Globals
static ball_t ball;
static paddle_t paddle[2];
int score[] = {0,0};



static void init()
{
    ball.x = DISPLAY_WIDTH/2;
    ball.y = DISPLAY_HEIGHT/2;
    ball.dx = 1;
    ball.dy = 1;
    ball.h = 10;
    ball.w = 10;

    paddle[0].x = 20;
    paddle[0].y = DISPLAY_HEIGHT/2 - 50;
    paddle[0].w = 10;
    paddle[0].h = 50;
    
    paddle[1].x = DISPLAY_WIDTH/2 - 10;
    paddle[1].y = DISPLAY_HEIGHT/2 - 50;
    paddle[1].w = 10;
    paddle[1].h = 50;
}

int score_check()
{
    int winner = 0;
    for(int j = 0; j<2; j++)
    {
        
        if (score[j] == MAX_SCORE)
        {
            if(j == 0){
                winner = 1;
            }
            else{
                winner = 2;
            }
            score[0] = 0;
            score[1] = 0;
            
            return winner;
        } 
    }
    return winner;
}
int collision_check(ball_t b, paddle_t p)
{
    int b_top,p_top;
    int b_bottom,p_bottom;
    int b_left,p_left;
    int b_right,p_right;

    //Ball
    b_top = b.y;
    b_bottom = b.y + b.h;
    b_left = b.x;
    b_right = b.x + b.w;

    //Paddle
    p_top = p.y;
    p_bottom = p.y + p.h;
    p_left = p.x;
    p_right = p.x + p.w;

    //Check collision cases
    if(b_right < p_left)
    {
        return 0;
    }
    if(b_left > p_right)
    {
        return 0;
    }
    if(b_top > p_bottom)
    {
        return 0;
    }
    if(b_bottom < p_top)
    {
        return 0;
    }
    
    return 1;
}

static void move_paddle_first_player(int m)
{

}

static void move_paddle_second_player(int m)
{

}

static void move_paddle_ai()
{

}

static void move_ball()
{
    ball.x += ball.dx;
    ball.y += ball.dy;

    //Check if a player scored a point and save it (Check if ball collides with screen edge on x axis)
    if(ball.x < 0)
    {
        score[1] +=1;
        init();
    }

    else if(ball.x > DISPLAY_WIDTH-10)
    {
        score[0] +=1;
        init();
    }

    //Check for collision with screen edge on y axis and make it "bounce"
    
    if(ball.y < 0 || ball.y > DISPLAY_HEIGHT-10){
        ball.dy = -ball.dy;
    }

    //Check for paddle collisions

    for(int k = 0; k<2; k++){
        
        //Collision!
        if(collision_check(ball,paddle[k]) == 1)
        {
        
            if(ball.dx < 0)
            {
                ball.dx -=1;
            }
            
            else
            {
                ball.dx +=1;
            }

            ball.dx = -ball.dx;

            int hit_position = (paddle[k].y + paddle[k].h) - ball.y;
            //TODO finish
            
        }
    }

}
static void draw_ball()
{

}

static void draw_paddle()
{

}
bool pong(){

}

