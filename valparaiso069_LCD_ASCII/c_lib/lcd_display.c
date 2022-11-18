/*
 * lcd_display.c
 *
 * 11/2022
 *
 * A. Inácio Morais
 * anderson.morais@protonmail.com - inacio.morais@protonmail.com
 * +55 35 99161-9878
 *
 */


// ***** Header Files *********************************************************
#include "lcd_display.h"


// ***** Global Variables *****************************************************
unsigned char _MHz;


// ***** Functions ************************************************************
void LCDWriteNibble(unsigned char ch, unsigned char rs)
{
    // always send the upper nibble
    ch = (ch >> 4);

    // mask off the nibble to be transmitted
    ch = (ch & 0x0F);

    // clear the lower half of LCD_PORT
    LCD_PORT = (LCD_PORT & 0xF0);

    // move the nibble onto LCD_PORT
    LCD_PORT = (LCD_PORT | ch);

    //set data/instr bit to 0 = instructions; 1 = data
    if (rs == 0) LCD_INSTR;
    else LCD_DATA;

    // set up enable before writing nibble
    LCD_ENABLE;

    delay_ms(1, _MHz);

    // turn off enable after write of nibble
    LCD_DISABLE;
}

void LCDPutCmd(unsigned char ch) {
    delay_ms(LCD_delay, 16);

    //Send the higher nibble
    LCDWriteNibble(ch, instr);

    //get the lower nibble
    ch = (ch << 4);

    delay_ms(1, _MHz);

    //Now send the lower nibble
    LCDWriteNibble(ch, instr);
}

void LCD_Initialize(unsigned char MHz) {
    _MHz = MHz;

    LCD_DIR = 0xFF;

    // required by display controller to allow power to stabilize
    delay_ms(LCD_Startup, MHz);

    // required by display initialization
    LCDPutCmd(0x32);

    // set interface size, # of lines and font
    LCDPutCmd(FUNCTION_SET);

    // turn on display and sets up cursor
    LCDPutCmd(DISPLAY_SETUP);

    LCDPutCmd(LCD_CLEAR);

    // set cursor movement direction
    LCDPutCmd(ENTRY_MODE);
}

void LCDPutChar(unsigned char ch) {
    delay_ms(LCD_delay, _MHz);

    //Send higher nibble first
    LCDWriteNibble(ch, data);

    //get the lower nibble
    ch = (ch << 4);

    // Now send the low nibble
    LCDWriteNibble(ch, data);
}

void LCDPutStr(const char *str) {
    unsigned char i = 0;

    // While string has not been fully traversed
    while (str[i])
    {
        // Go display current char
        LCDPutChar(str[i++]);
    }
}

void LCDGoto(unsigned char pos,unsigned char ln) {
    // if incorrect line or column
    if ((ln > (NB_LINES-1)) || (pos > (NB_COL-1)))
    {
        // Just do nothing
        return;
    }

    // LCD_Goto command
    LCDPutCmd((ln == 1) ? (0xC0 | pos) : (0x80 | pos));

    // Wait for the LCD to finish
    delay_ms(LCD_delay, _MHz);
}