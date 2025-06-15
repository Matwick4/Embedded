#include "end_game.h"
#include "state.h"
#include "HWdependent/display.h"
#include "HWdependent/joystick.h"   

void show_end_game_screen(bool won, int player) {
    // Clear the screen
    clear_Display();

    // Save current color and font settings
    uint32_t prev_color = get_Foreground_Color();
    const Graphics_Font *prev_font = get_Font();

    // Set black color for the text
    set_Foreground_Color(GRAPHICS_COLOR_BLACK);

    // Optional: set a larger font if available
    // set_Font(bigFont);

    const char* message;

    // Determine message based on game mode and result
    if (player == -1) {
        // Single player mode
        message = won ? "Congrats! You Won" : "Sorry! You Lost!";
    } else if (won) {
        // Multiplayer mode – someone won
        message = (player == 1) ? "Player 1 Won!" : "Player 2 Won!";
    } else {
        // Multiplayer mode – someone lost
        message = (player == 1) ? "Player 2 Lost!" : "Player 1 Lost!";
    }

    // Draw the main message centered on the screen
    draw_String_Centered(message, DISPLAY_WIDTH / 2, 20, false);

    // Draw the instruction to continue
    draw_String_Centered("Select RIGHT", DISPLAY_WIDTH / 2, 80, false);
    draw_String_Centered("to continue", DISPLAY_WIDTH / 2, 90, false);

    // Restore previous font and color
    set_Font(prev_font);
    set_Foreground_Color_Translated(prev_color);

    // busy waiting for the right on the joystick

    bool goToMainMenu=false;
    while (!goToMainMenu)
    {
        readJoystickPosition();
        //Horizontal movement
        int left = (gameState.joystickX < J_LEFT_TRESH) ? (J_LEFT_TRESH - gameState.joystickX) : 0;
        int right = (gameState.joystickX > J_RIGHT_TRESH) ? (gameState.joystickX - J_RIGHT_TRESH) : 0;
        //Vertical movement
        int down = (gameState.joystickY < J_DOWN_TRESH) ? (J_DOWN_TRESH - gameState.joystickY) : 0;
        int up = (gameState.joystickY > J_UP_TRESH) ? (gameState.joystickY - J_UP_TRESH) : 0;

        if( (right > up) & (right > down))
            gameState.game_selected= -1;

    }
    
}

