#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdbool.h>
#include <stdint.h>
#include "../../LcdDriver/Crystalfontz128x128_ST7735.h"
#include <ti/grlib/grlib.h>

#define DISPLAY_WIDTH LCD_HORIZONTAL_MAX
#define DISPLAY_HEIGHT LCD_VERTICAL_MAX

//Clear display by filling it with background color
void clear_Display();

//Returns foreground color currently used
uint32_t get_Foreground_Color();

//Returns background color currently used
uint32_t get_Background_Color();

//Returns font height currently being used
uint16_t get_Font_Height();

//Returns font currently used
Graphics_Font *get_Font();

//Sets font to be used
void set_Font(const Graphics_Font *font);

//Sets foreground color
//note: color must already have been translated for this display
void set_Foreground_Color_Translated(uint32_t);

//Sets background color
//note: color must already have been translated for this display
void set_Background_Color_Translated(uint32_t);

//Translates the color to one that is right for the display,
//then sets it as foreground
void set_Foreground_Color(uint32_t);

//Translates the color to one that is right for the display,
//then sets it as background
void set_Background_Color(uint32_t);

//Paints rectangle on the screen (only the border)
void draw_Rectangle(const Graphics_Rectangle *rectangle);

Graphics_Rectangle getBallRectangle(int16_t,int16_t);
Graphics_Rectangle get_Rectangle(int16_t,int16_t);
Graphics_Rectangle getPaddleRectangle(int16_t,int16_t);
Graphics_Rectangle get_Rectangle_decoration(int16_t,int16_t);
//Paints rectanlge on the screen (filled with fg color)
void fill_Rectangle(const Graphics_Rectangle *rectangle);
void clean_rect(const Graphics_Rectangle *r);

//Draws filled circle on screen
void fill_Circle(int,int,int);

//Draws string on display, starting from given point
void draw_String(const char *string, uint32_t x, uint32_t y, bool redrawBackground);

//Draws  string on display, centered on given point
void draw_String_Centered(const char *string, uint32_t x, uint32_t y, bool redrawBackground);

//Detects if two rectangles overlap each other by checking the coordinates of their top-right and bottom-left corners
bool is_Overlapping(const Graphics_Rectangle *rect1, const Graphics_Rectangle *rect2);

//Detects if point is inside the rectangle
bool is_Point_Within_Rectangle(const Graphics_Rectangle *rect, uint16_t x, uint16_t y);


#endif
