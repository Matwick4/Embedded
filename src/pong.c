#include "pong.h"
#include "state.h"
#include "end_game.h"
#include "HWdependent/display.h"
#include "HWdependent/joystick.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_SCORE 10

//Globals
static ball_t ball;
static paddle_t paddle[2];
int score[] = {0,0};
static bool AI = false;
const char *const gameOptions[] = {"PvE","PvP"};
const int lengthOpt = 2;
const int offsetOpt = 60;

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
    int j;
    for(j = 0; j<2; j++)
    {
        
        if(score[j] == MAX_SCORE)
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

static void move_paddle_first_player(paddle_direction_t dir)
{
    //TODO. For the joystick part only check for movement on the y axis(theoretically)
    //Read input from joystick in the pong.c then draw the paddle based on value dir
    
    if(dir == UPp && paddle[0].last_dir != UPp)
    {
        if(paddle[0].y <= 0) {
		
			paddle[0].y = 0;

		} else {
		
			paddle[0].y -= 2; // TODO check if correct
		}
        paddle[0].last_dir = UPp;
    }
    else if(dir == DOWNp && paddle[0].last_dir != DOWNp)
    {
        if(paddle[0].y >= DISPLAY_HEIGHT - paddle[0].h) {
		
			paddle[0].y = DISPLAY_HEIGHT - paddle[0].h;
		
		} else { 
		
			paddle[0].y += 2;
		}
        paddle[0].last_dir = DOWNp;
    }
    draw_paddle(0);
}

static void move_paddle_second_player(paddle_direction_t dir)
{
    //TODO read from pong.c the button pressed then call this funct with appropriate parameter dir
    if(dir == UPp && paddle[0].last_dir != UPp)
    {
        if(paddle[1].y <= 0) {
		
			paddle[1].y = 0;

		} else {
		
			paddle[1].y -= 2; // TODO check if correct
		}
        paddle[1].last_dir = UPp;
    }
    else if(dir == DOWNp && paddle[1].last_dir != DOWNp)
    {
        if(paddle[1].y >= DISPLAY_HEIGHT - paddle[1].h) {
		
			paddle[1].y = DISPLAY_HEIGHT - paddle[1].h;
		
		} else { 
		
			paddle[1].y += 2;
		}
        paddle[1].last_dir = DOWNp;
    } 
    draw_paddle(1);

}

static void move_paddle_ai()
{
    int c = paddle[1].y + paddle[1].h /2;
    int screen_c = DISPLAY_HEIGHT/2;
    int ball_speed = abs(ball.dy);


    //Case of ball moving towards the ai paddle(to the right)
    if(ball.dx > 0)
    {
        if(c < screen_c)
        {
            paddle[1].y += ball_speed;
        }
        else
        {
            paddle[1].y -= ball_speed;
        }
    }
    //Case of ball moving to the left
    else
    {
        //The ball is moving UPp //TODO check if correct
        if(ball.dy > 0)
        {
            if (ball.y > c) { 
				
				paddle[1].y += ball_speed;

			} else { 
			
				paddle[1].y -= ball_speed;
			} 
        }
        //The ball is moving down //TODO check if correct
        if(ball.dy < 0)
        {
            if (ball.dy < 0) {
		
                if (ball.y < c) {
                    
                    paddle[1].y -= ball_speed;
                
                } else {
                
                    paddle[1].y += ball_speed;
                }
            }
        }
        //The ball is moving on a straight line
        if(ball.dy == 0)
        {
            if (ball.y < c) { 
			
				paddle[1].y -= 2;

			} else {
			
				paddle[1].y += 2;
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
    int k;
    for(k = 0; k<2; k++){
        
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
    //the lowest part of the paddle and so it needs "to go UPp".
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

    else if (hit_position < 20)
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
        
            ball.x = DISPLAY_WIDTH - ball.w - 2;
        }
    }
}
static void draw_ball()
{
    //TODO draw the ball using the ball fields

    Graphics_Rectangle ball_rect = get_Rectangle(ball.x,ball.y);
    set_Foreground_Color(GRAPHICS_COLOR_RED);
    fill_Rectangle(&ball_rect);
    
    //Check if necessary to do collision check part here
}

static void draw_paddle(int paddle_index)
{
    //TODO draw the paddle based on paddle index to identify the right paddle
    Graphics_Rectangle paddle_rect = get_Rectangle(paddle[paddle_index].x,paddle[paddle_index].y);
    set_Foreground_Color(GRAPHICS_COLOR_WHITE);
    fill_Rectangle(&paddle_rect);
    
    //Check if necessary to do collision check part here
}
static void draw_pong_options(int step)
{
    int h_w = DISPLAY_WIDTH/2;
    int offset = offsetOpt;
    int j = 0;
    for(j = 0; j<lengthOpt;j++)
    {
        draw_String_Centered(gameOptions[j],h_w,offset,false);
        offset+=step;
    }
}
static void draw_pong_menu()
{
    clear_Display();
    int selected_curr = 0;
    int step = get_Font_Height()*2;

    int prev_sel = selected_curr;
    gameState.buttonClicked = false;

    Graphics_Rectangle prevRect;
    prevRect.xMin = 0;
    prevRect.xMax = 0;
    prevRect.yMin = 0;
    prevRect.yMax = 0;
    
    while(!(gameState.buttonClicked))
    {
        readJoystickPosition();

        if(gameState.joystickY < J_DOWN_TRESH)
        {
            selected_curr = min(selected_curr+1,lengthOpt-1);
            gameState.joystickY = J_DOWN_TRESH+1;
            int j;
            for(j = 0;j<400000;j++){;}

        }
        else if(gameState.joystickY > J_UP_TRESH)
        {
            selected_curr = max(selected_curr-1,0);
            gameState.joystickY = J_UP_TRESH-1;
            int j;
            for(j = 0;j<400000;j++){;}
                
            
        }
        if(gameState.buttonClicked)
        {
                 gameState.buttonClicked = true;
        }
        draw_title_play_options();

        if(selected_curr != prev_sel)
        {
            clean_rect(&prevRect);
            prev_sel = selected_curr;
        }
        prevRect = draw_selection_rect(selected_curr,step);
        draw_pong_options(step);


    }
    gameState.buttonClicked = false;
    if (selected_curr == 0)
    {
        AI = true;
    }
    else
    {
        AI = false;
    }
}

void draw_title_play_options()
{
    uint32_t prev_color = get_Foreground_Color();
    set_Foreground_Color(GRAPHICS_COLOR_RED);
    int w = DISPLAY_WIDTH;

    const Graphics_Font *prev_font = get_Font();
    //set_Font(titleFont);

    draw_String_Centered("Choose gamemode",w/2,22,false);
    set_Font(prev_font);
    set_Foreground_Color_Translated(prev_color);
}


Graphics_Rectangle draw_selection_rect(const int sel, const int s)
{
    const int padding = 20;
    Graphics_Rectangle rect;
    rect.xMax = DISPLAY_WIDTH - padding;
    rect.xMin = padding;
    rect.yMin = offsetOpt + sel * s - s/2 ;
    rect.yMax = offsetOpt + sel * s + s/2 ;

    if(sel == lengthOpt)
    {
        rect.xMax = DISPLAY_WIDTH-1;
        rect.xMin = DISPLAY_WIDTH-20;
        rect.yMin = DISPLAY_HEIGHT-15;
        rect.yMax = DISPLAY_HEIGHT-2;
    }
    draw_Rectangle(&rect);
    return rect;
}   

bool pong(){
    
    //Clear display, set ball and paddles
    clear_Display();
    init();
    uint32_t previous_foregroundColor = get_Foreground_Color();
    int quit = 0;
    int state = 1;

    while(quit == 0)
    {
        //Show menu (decide whether play against AI or other player)
        if(state == 1)
        {
            draw_pong_menu();
            state = 2;
        }
        //Game
        else if(state == 2)
        {
            int s = score_check();
            //Nobody has won yet; continue
            if(s == 0)
            {
                //Changes based on selected AI
                if(AI)
                {
                    readJoystickPosition();
                    move_paddle_ai();
                    move_ball();
                    draw_paddle(1);
                    draw_ball();
                    if(gameState.joystickY < J_DOWN_TRESH)
                    {
                        move_paddle_first_player(DOWNp);
                    }
                    else if(gameState.joystickY > J_UP_TRESH)
                    {
                        move_paddle_first_player(UPp);
                    }
                    draw_paddle(0);

                }
                else
                {
                    readJoystickPosition();
                    if(isButtonUpPressed())
                    {
                        move_paddle_second_player(UPp);
                    }
                    else if(isButtonDownPressed())
                    {
                        move_paddle_second_player(DOWNp);
                    }
                    move_ball();
                    draw_paddle(1);
                    draw_ball();
                    if(gameState.joystickY < J_DOWN_TRESH)
                    {
                        move_paddle_first_player(DOWNp);
                    }
                    else if(gameState.joystickY > J_UP_TRESH)
                    {
                        move_paddle_first_player(UPp);
                    }
                    draw_paddle(0);
                }
            }
            else{
                state = 3;
            }
        }
        //Game over TODO
        else if(state == 3)
        {
            quit = 1;
        }
    }
    return score_check();
}

