#include "display.h"
#include "../state.h"

void clear_Display(){
    GrClearDisplay(&gameState.gContext);
}

uint32_t get_Foreground_Color(){
    return gameState.gContext.foreground;
}

uint32_t get_Background_Color(){
    return gameState.gContext.background;
}

uint16_t get_Font_Height(){
    return gameState.gContext.font->height;
}

Graphics_Font *get_Font(){
    return gameState.gContext.font;
}

void set_Font(const Graphics_Font *font){
    GrContextFontSet(&gameState.gContext, font);
}

void set_Foreground_Color_Translated(uint32_t color){
    gameState.gContext.foreground = color;
}

void set_Background_Color_Translated(uint32_t color){
    gameState.gContext.background = color;
}

void set_Foreground_Color(uint32_t color){
    Graphics_setForegroundColor(&gameState.gContext, color);
}

void set_Background_Color(uint32_t color){
    Graphics_setBackgroundColor(&gameState.gContext, color);
}

void draw_Rectangle(const Graphics_Rectangle *rectangle){
    Graphics_drawRectangle(&gameState.gContext, rectangle);
}

Graphics_Rectangle getBallRectangle(int x, int y)
{
    Graphics_Rectangle ball;
    ball.xMin = x;
    ball.xMax = x+6;
    ball.yMin = y;
    ball.yMin = y-6;

    return ball;
}

Graphics_Rectangle get_Rectangle(int x, int y)
{
    Graphics_Rectangle r;
    rect.yMin = y-2;
    rect.yMax = y+2;
    rect.xMax = x+2;
    rect.xMin = x-2;
    return r;
}

Graphics_Rectangle getPaddleRectangle(int x, int y)
{
    Graphics_Rectangle paddle;
    ball.xMin = x;
    ball.xMax = x+10;
    ball.yMin = y;
    ball.yMax = y+30;

    return paddle;
}

Graphics_Rectangle get_Rectangle_decoration(int x, int y)
{
    Graphics_Rectangle r;
    rect.yMin = y-1;
    rect.yMax = y+1;
    rect.xMax = x+1;
    rect.xMin = x-1;
    return r;
}

void fill_Rectangle(const Graphics_Rectangle *rectangle){
    Graphics_fillRectangle(&gameState.gContext, rectangle);
}

void fill_Circle(int x, int y, int radius){
    Graphics_fillCircle(&gameState.gContext, x, y, radius);
}

void draw_String(const char *string, uint32_t x, uint32_t y, bool redrawBackground){
    Graphics_drawString(
        &gameState.gContext,
        (int8_t *)string,
        AUTO_STRING_LENGTH,
        x,
        y,
        redrawBackground);
}

void draw_String_Centered(const char *string, uint32_t x, uint32_t y, bool redrawBackground){
    Graphics_drawStringCentered(
        &gameState.gContext,
        (int8_t *)string,
        AUTO_STRING_LENGTH,
        x,
        y,
        redrawBackground);
}

bool is_Overlapping(const Graphics_Rectangle *rect1, const Graphics_Rectangle *rect2){
    
    if (rect1->xMax >= rect2->xMin && rect1->xMax <= rect2->xMax && rect1->yMax >= rect2->yMin && rect1->yMax <= rect2->yMax){
        return true;
    }
    else if (rect1->xMin >= rect2->xMin && rect1->xMin <= rect2->xMax &&
        rect1->yMax >= rect2->yMin && rect1->yMax <= rect2->yMax){
        return true;
    }
    else if (rect1->xMin >= rect2->xMin && rect1->xMin <= rect2->xMax &&
        rect1->yMin >= rect2->yMin && rect1->yMin <= rect2->yMax){
        return true;
    }
    else if (rect1->xMax >= rect2->xMin && rect1->xMax <= rect2->xMax && rect1->yMin >= rect2->yMin && rect1->yMin <= rect2->yMax){
        return true;
    }
    
    return false;
}

bool is_Point_Within_Rectangle(const Graphics_Rectangle *rect, uint16_t x, uint16_t y){
    return Graphics_isPointWithinRectangle(rect, x, y);
}
