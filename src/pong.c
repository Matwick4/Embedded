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
    ball.h = 6;
    ball.w = 6;

    paddle[0].x = 10;
    paddle[0].y = DISPLAY_HEIGHT/2 - 15;
    paddle[0].w = 6;
    paddle[0].h = 30;
    
    paddle[1].x = DISPLAY_WIDTH - 4; //4 = 10-6(paddle width)
    paddle[1].y = DISPLAY_HEIGHT/2 - 15;
    paddle[1].w = 6;
    paddle[1].h = 30;
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
    if(b_right < p_left || b_left > p_right || b_top > p_bottom || b_bottom < p_top)
    {
        return 0;
    }
    return 1;
}

static void move_paddle_first_player(int m)
{
    //TODO. For the joystick part only check for movement on the y axis(theoretically)
}

static void move_paddle_second_player(int m)
{
    //TODO. Need to use the othe buttons for it to work.
}

static void move_paddle_ai()
{
    int c = paddle[0].y + paddle[0].h /2;
    int screen_c = DISPLAY_HEIGHT/2;
    int ball_speed = abs(ball.dy);


    //Case of ball moving towards the ai paddle(to the right)
    if(ball.dx > 0)
    {
        if(c < screen_c)
        {
            paddle[0].y += ball_speed;
        }
        else
        {
            paddle[0].y -= ball_speed;
        }
    }
    //Case of ball moving to the left
    else
    {
        //The ball is moving up //TODO check if correct
        if(ball.dy > 0)
        {
            if (ball.y > c) { 
				
				paddle[0].y += ball_speed;

			} else { 
			
				paddle[0].y -= ball_speed;
			} 
        }
        //The ball is moving down //TODO check if correct
        if(ball.dy < 0)
        {
            if (ball.dy < 0) {
		
                if (ball.y < center) { 
                    
                    paddle[0].y -= ball_speed;
                
                } else {
                
                    paddle[0].y += ball_speed;
                }
            }
        }
        //The ball is moving on a straight line
        if(ball.dy == 0)
        {
            if (ball.y < c) { 
			
				paddle[0].y -= 2;

			} else {
			
				paddle[0].y += 2;
			}
        }
    }
    //Adjust the paddle if it arrives at the top/bottom of the screen
    if(paddle[0].y < 0)
    {
        paddle[0].y = 0;
    }
    if(paddle[0].y + paddle[0].h > DISPLAY_HEIGHT)
    {
        paddle[0].y = DISPLAY_HEIGHT - paddle[0].h;
    }
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
            change_ball_vector(k); 
        }
    }
}
static void change_ball_vector(int k){

    //Case of ball moving left
    if(ball.dx < 0)
    {
        ball.dx -=1;
    }
    
    //Case of ball moving right
    else
    {
        ball.dx +=1;
    }

    //Changed direction to "bounce"
    ball.dx = -ball.dx;

    //Modify the ball.dy based on the point where it hit the paddle.
    //If the value below (hit_position) is low it means that the ball hit
    //the lowest part of the paddle and so it needs "to go up". 
    //If instead it's big it means the ball hit the highest part of the paddle
    //and so the ball needs "to go down". Intermediate values are calculated as such.
    
    int hit_position = (paddle[k].y + paddle[k].h) - ball.y;

    if (hit_position >= 0 && hit_position < 5) {
        ball.dy = 3;
    }

    else if (hit_position < 10) 
    {
        ball.dy = 2;
    }
    
    else if (hit_position < 15) 
    {
        ball.dy = 1;
    }

    else if (&& hit_position < 20) 
    {
        ball.dy = 0;
    }

    else if (hit_position < 25) 
    {
        ball.dy = -1;
    }
    else if (hit_position < 30)
    {
        ball.dy = -2;
    }
    else{
        ball.dy = -3;
    }

    //Handle cases where ball can glitch
    if (ball.dx > 0) {

        if (ball.x < 2) {
        
            ball.x = 2;
        }
        
    } else {
        
        if (ball.x > DISPLAY_WIDTH - ball.w - 2) {
        
            ball.x = DISPLAY_WIDTH - ball.w - 2
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

