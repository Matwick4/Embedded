#include "pong.h"
#include "state.h"
#include "end_game.h"
#include "menu.h"
#include "HWdependent/display.h"
#include "HWdependent/joystick.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_SCORE 3
#define PADDLE_MARGIN 5

//Globals
static ball_t ball;
static paddle_t paddle[2];
int score[] = {0,0};
static bool AI = false;
const char *const gameOptions[] = {"Player vs CPU","Player vs Player"};
const int lengthOpt = 2;
const int offsetOpt = 60;
const int EXTRA_THRESHOLD = 1000;    //joystick drifts on the right so we need an extra threshold



//================================================================================
//==========INIT SECTION==========================================================
//================================================================================
static void init()
{
    // Initial position in the center
    ball.x = DISPLAY_WIDTH / 2;
    ball.y = DISPLAY_HEIGHT / 2;
    ball.w = 6;
    ball.h = 6;

    // Random horizontal direction: -1 or 1
    ball.dx = (rand() % 2 == 0) ? -1 : 1;

    // Random vertical  direction: -1 or 1
    int r = rand() % 3; // 0, 1 o 2
    if (r == 0)
        ball.dy = -1;
    else if (r == 1)
        ball.dy = 0;
    else
        ball.dy = 1;

    // Initialize left paddle
    paddle[0].w = 4;
    paddle[0].h = 20;
    paddle[0].x = PADDLE_MARGIN;
    paddle[0].y = DISPLAY_HEIGHT / 2 - paddle[0].h / 2;

    // Initialize right paddle
    paddle[1].w = 4;
    paddle[1].h = 20;
    paddle[1].x = DISPLAY_WIDTH - PADDLE_MARGIN - paddle[1].w;
    paddle[1].y = DISPLAY_HEIGHT / 2 - paddle[1].h / 2;
}



//================================================================================
//==========TIMER SECTION=========================================================
//================================================================================
void delay_ms(int ms) {
    int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 3000; j++);
}



//================================================================================
//==========CHECK SECTION=========================================================
//================================================================================

//==========SCORE CHECK======================================================
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

//==========COLLISION CHECK==================================================
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



//================================================================================
//==========CLEAR SECTION=========================================================
//================================================================================

//==========UNDRAW BALL======================================================
static void undraw_ball()
{
    Graphics_Rectangle ball_rect = get_Rectangle(ball.x,ball.y);
    clean_rect(&ball_rect);
}

//==========UNDRAW PADDLE======================================================
static void undraw_paddle(int paddle_index)
{
    Graphics_Rectangle rect;
    rect.xMin = paddle[paddle_index].x;
    rect.xMax = paddle[paddle_index].x + paddle[paddle_index].w - 1;
    rect.yMin = paddle[paddle_index].y;
    rect.yMax = paddle[paddle_index].y + paddle[paddle_index].h - 1;

    set_Foreground_Color(GRAPHICS_COLOR_WHITE);
    clean_rect(&rect);
}



//================================================================================
//==========MOVING SECTION========================================================
//================================================================================

//==========MOVE PADDLE PLAYER 1=============================================
static void move_paddle_first_player(paddle_direction_t dir)
{
    undraw_paddle(0);

    if(dir == UPp)
    {
        if(paddle[0].y > 0)
            paddle[0].y -= 1;
        else
            paddle[0].y = 0;
    }
    else if(dir == DOWNp)
    {
        if(paddle[0].y < DISPLAY_HEIGHT - paddle[0].h)
            paddle[0].y += 1;
        else
            paddle[0].y = DISPLAY_HEIGHT - paddle[0].h;
    }

    draw_paddle(0);
}

//==========MOVE PADDLE PLAYER 2=============================================
static void move_paddle_second_player(paddle_direction_t dir)
{
    //TODO read from pong.c the button pressed then call this funct with appropriate parameter dir
    undraw_paddle(1);

        if(dir == DOWNp)
        {
            if(paddle[1].y > 0)
                paddle[1].y -= 1;
            else
                paddle[1].y = 0;
        }
        else if(dir == UPp)
        {
            if(paddle[1].y < DISPLAY_HEIGHT - paddle[1].h)
                paddle[1].y += 1;
            else
                paddle[1].y = DISPLAY_HEIGHT - paddle[1].h;
        }

        draw_paddle(1);

}

//==========MOVE PADDLE PLAYER CPU===========================================
static void move_paddle_ai()
{
    // Calculate the vertical center of the CPU paddle
    int paddle_center = paddle[1].y + paddle[1].h / 2;

    // Follow the ball: move the paddle towards the ball's y-position
    if(ball.y < paddle_center)
    {
        paddle[1].y -= 1; // Move up
    }
    else if(ball.y > paddle_center)
    {
        paddle[1].y += 1; // Move down
    }

    // Clamp the paddle position to stay within screen bounds
    if(paddle[1].y < 0)
    {
        paddle[1].y = 0;
    }
    else if(paddle[1].y + paddle[1].h > DISPLAY_HEIGHT)
    {
        paddle[1].y = DISPLAY_HEIGHT - paddle[1].h;
    }
}

//==========MOVE BALL========================================================
static void move_ball()
{
    ball.x += ball.dx;
    ball.y += ball.dy;

    //Check if a player scored a point and save it (Check if ball collides with screen edge on x axis)
    if(ball.x < 0)
    {
        score[1] +=1;       // update score
        clear_Display();    //clear display
        draw_score();       //show score
        delay_ms(1000);     //wait 1s
        clear_Display();    //clear display
        init();             //init the game
    }

    else if(ball.x > DISPLAY_WIDTH-10)
    {
        score[0] +=1;
        clear_Display();
        draw_score();
        delay_ms(1000);
        clear_Display();
        init();;
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

//==========BALL DIRECTION (normalized speed) ===============================
static void change_ball_vector(int k){
    // Always move horizontally at dx = ±1
    ball.dx = (ball.dx > 0) ? -1 : 1;

    // Calculate where the ball hit the paddle
    int hit_position = (paddle[k].y + paddle[k].h) - ball.y;

    // Map hit position to vertical direction (only -1 or 1)
    if (hit_position >= 0 && hit_position < 5) {
        ball.dy = 1;
    }
    else if (hit_position < 10) {
        ball.dy = 1;
    }
    else if (hit_position < 15) {
        ball.dy = 0;
    }
    else if (hit_position < 20) {
        ball.dy = 0;
    }
    else if (hit_position < 25) {
        ball.dy = -1;
    }
    else {
        ball.dy = -1;
    }

    // Prevent purely horizontal movement
    if (ball.dy == 0) {
        ball.dy = (rand() % 2 == 0) ? 1 : -1;
    }

    // Ensure ball stays within display bounds
    if (ball.dx > 0 && ball.x < 2) {
        ball.x = 2;
    } else if (ball.dx < 0 && ball.x > DISPLAY_WIDTH - ball.w - 2) {
        ball.x = DISPLAY_WIDTH - ball.w - 2;
    }
}




//================================================================================
//==========DRAWING SECTION=======================================================
//================================================================================

//==========DRAW BALL========================================================
static void draw_ball()
{
    //TODO draw the ball using the ball fields

    Graphics_Rectangle ball_rect = get_Rectangle(ball.x,ball.y);
    set_Foreground_Color(GRAPHICS_COLOR_RED);
    fill_Rectangle(&ball_rect);

    //Check if necessary to do collision check part here
}

//==========DRAW PADDLE======================================================
static void draw_paddle(int paddle_index)
{
    Graphics_Rectangle paddle_rect;
    paddle_rect.xMin = paddle[paddle_index].x;
    paddle_rect.xMax = paddle[paddle_index].x + paddle[paddle_index].w - 1;
    paddle_rect.yMin = paddle[paddle_index].y;
    paddle_rect.yMax = paddle[paddle_index].y + paddle[paddle_index].h - 1;

    set_Foreground_Color(GRAPHICS_COLOR_BLACK);
    fill_Rectangle(&paddle_rect);
}

//==========DRAW SCORE======================================================
void draw_score()
{
    // Builds the score string
    char score_str[10];
    sprintf(score_str, "%d - %d", score[0], score[1]);

    // Clears the screen
    Graphics_Rectangle full = {0, 0, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1};
    clean_rect(&full);

    // Set color and font
    uint32_t prev_color = get_Foreground_Color();
    const Graphics_Font *prev_font = get_Font();

    set_Foreground_Color(GRAPHICS_COLOR_BLACK);

    // Draw the centered score
    draw_String_Centered(score_str, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, false);

    // Restore the previous font and color
    set_Font(prev_font);
    set_Foreground_Color_Translated(prev_color);
}


//==========DRAW OPTIONS=====================================================
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

//==========DRAW MENU========================================================
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

    while(!gameState.buttonClicked)
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
            for(j = 0;j<400000;j++){;} // some busy waiting
        }

        draw_title_play_options();

        if(selected_curr != prev_sel)
        {
            clean_rect(&prevRect); // clear the selection rectangle
            prev_sel = selected_curr;
        }
        prevRect = draw_selection_rect(selected_curr, step); // draw new rectangle

        draw_pong_options(step);

        //joystick RIGHT (SELECT)
        if(gameState.joystickX > J_RIGHT_TRESH + 1000 )
        {
            gameState.buttonClicked = true;
            int j;
            for(j = 0; j < 400000; j++) {;}
        }
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

//==========DRAW TITLE=======================================================
void draw_title_play_options()
{
    uint32_t prev_color = get_Foreground_Color();
    set_Foreground_Color(GRAPHICS_COLOR_RED);
    int w = DISPLAY_WIDTH;

    const Graphics_Font *prev_font = get_Font();

    draw_String_Centered("SELECT GAMEMODE",w/2,22,false);
    set_Font(prev_font);
    set_Foreground_Color_Translated(prev_color);
}

//==========DRAW SELECTION===================================================
Graphics_Rectangle draw_selection_rect(const int sel, const int s)
{
    const int padding = 10;
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




//================================================================================
//==========GAME STATE MACHINE====================================================
//================================================================================
bool pong() {
    // Clear the display and initialize ball and paddles
    clear_Display();
    init();

    uint32_t previous_foregroundColor = get_Foreground_Color();
    int quit = 0;
    int state = 1;

    while(quit == 0)
    {
        // State 1: Show menu
        if(state == 1)
        {
            draw_pong_menu();

            // Clear menu before entering the game
            clear_Display();

            state = 2;
        }

        // State 2: Game running
        else if(state == 2)
        {
            // Clear previous frame
            undraw_ball();
            undraw_paddle(0);
            undraw_paddle(1);
            delay_ms(40); // for ~20 fps

            int s = score_check();

            if(s == 0) // No one has won yet
            {
                if(AI) // Player vs CPU
                {
                    readJoystickPosition();
                    move_paddle_ai();
                    move_ball();
                    draw_paddle(1);
                    draw_ball();

                    if(gameState.joystickY < J_DOWN_TRESH)
                        move_paddle_first_player(DOWNp);
                    else if(gameState.joystickY > J_UP_TRESH)
                        move_paddle_first_player(UPp);

                    draw_paddle(0);
                }
                else // Player vs Player
                {
                    readJoystickPosition();

                    if(isButtonUpPressed())
                    {

                        move_paddle_second_player(UPp);
                    }
                    if(isButtonDownPressed())
                    {
                        move_paddle_second_player(DOWNp);

                    }


                    move_ball();
                    draw_paddle(1);
                    draw_ball();

                    if(gameState.joystickY < J_DOWN_TRESH)
                        move_paddle_first_player(DOWNp);
                    else if(gameState.joystickY > J_UP_TRESH)
                        move_paddle_first_player(UPp);

                    draw_paddle(0);
                }
            }
            else // Someone has won -> go to state 3
            {
                state = 3;
            }
        }

        // State 3: End game screen
        else if(state == 3)
        {
            int winner = score_check(); // returns 1 if player 1 won, 2 if player 2 or CPU won

            if(AI) {
                // Single player mode: 1 = player won, 2 = CPU won
                show_end_game_screen(winner == 1, -1); // -1 means single player mode
            } else {
                // Multiplayer mode
                show_end_game_screen(true, winner);
            }

            // Wait until the player moves the joystick to the RIGHT to continue
            bool q= true;
            while(q)
            {
                readJoystickPosition();
                if(gameState.joystickX > J_RIGHT_TRESH + EXTRA_THRESHOLD)
                {
                    // Debounce: consume the input and exit loop
                    gameState.joystickX = J_RIGHT_TRESH - 1;
                    delay_ms(200); // optional debounce delay
                    q=false;
                    P2->OUT |= BIT2;
                }
                delay_ms(20);
            }

            quit = 1; // Exit main loop
        }
    }

    return score_check(); // Return the winner
}
