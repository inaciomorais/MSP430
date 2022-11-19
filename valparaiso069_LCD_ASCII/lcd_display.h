/*
 * lcd_display.h
 *
 * 11/2022
 *
 * A. Inácio Morais
 * anderson.morais@protonmail.com - inacio.morais@protonmail.com
 * +55 35 99161-9878
 *
 * LCD Display interface based on the PICDEM 2 Plus Demo Board LCD library provided by Microchip:
 * https://www.microchip.com/en-us/development-tool/DM163022-1
 * https://ww1.microchip.com/downloads/en/DeviceDoc/PICDEM2pluscode.zip
 *
 */


//***** Header Files **********************************************************
#include <msp430.h>
#include "delay_xs.h"

#ifndef LCD_DISPLAY_H_
#define LCD_DISPLAY_H_


//***** Prototypes ************************************************************
// Function to write a specified nibble to the LCD
void LCDWriteNibble(unsigned char ch, unsigned char rs);

// Send an ASCII command to the LCD in instruction mode
void LCDPutCmd(unsigned char ch);

// This routine initializes the LCD driver
// This routine must be called before any other LCD routine is called
// MHz: System Clock [MHz]
void LCD_Initialize(unsigned char MHz);

// Writes character to LCD at current cursor position
void LCDPutChar(unsigned char ch);

// This routine writes string to LCD at current cursor position
void LCDPutStr(const char *str);

// This function positions the cursor at the specified Line and column
void LCDGoto(unsigned char pos,unsigned char ln);


//***** Defines ***************************************************************
// set up the timing for the LCD delays
#define LCD_delay           1     // ~1mS
#define LCD_Startup         15    // ~15mS

// Command set for the LCD display controller (HITACHI HD44780U or WINSTAR WH1602C)
#define LCD_CLEAR           0x01
#define LCD_HOME            0x02
#define LCD_CURSOR_BACK     0x10
#define LCD_CURSOR_FWD      0x14
#define LCD_PAN_LEFT        0x18
#define LCD_PAN_RIGHT       0x1C
#define LCD_CURSOR_OFF      0x0C
#define LCD_CURSOR_ON       0x0E
#define LCD_CURSOR_BLINK    0x0F
#define LCD_CURSOR_LINE2    0xC0
#define LCD_CGRAM           0x40            // Initial CGRAM address

// display controller setup commands from page 46 of Hitachi HD44780U datasheet or page 17 of Winstar WH1602C comprehensive datasheet (Ex.: WH1602B-TMI-ET#)
#define FUNCTION_SET        0x28            // 4 bit interface, 2 lines, 5x8 font
#define ENTRY_MODE          0x06            // increment mode
#define DISPLAY_SETUP       0x0C            // display on, cursor off, blink off


// single bit for selecting command register or data register
#define instr       0
#define data        1

/* These #defines create the pin connections to the LCD Display
 *
 * LCD VSS pin (1) to ground
 * LCD VCC pin (2) to +5Vcc (MSP430G2553 Value Line Launchpad: from Test Pin 1 - TP1)
 * LCD Register Select line - RS (4) P2.4
 * LCD R/W pin (5) to ground
 * LCD Enable - E (6) P2.5
 * LCD D4 (11) P2.0
 * LCD D5 (12) P2.1
 * LCD D6 (13) P2.2
 * LCD D7 (11) P2.3
 */
#define LCD_PORT        P2OUT                  
#define LCD_DIR         P2DIR
#define LCD_ENABLE      LCD_PORT |=  BIT5      // LCD Enable - E (6)
#define LCD_DISABLE     LCD_PORT &= ~BIT5
#define LCD_DATA        LCD_PORT |=  BIT4      // LCD Register Select line - RS (4)
#define LCD_INSTR       LCD_PORT &= ~BIT4

#define NB_LINES    2                        // Number of display lines
#define NB_COL      16                       // Number of characters per line


//***** Global Variables ******************************************************


#endif /* LCD_DISPLAY_H_ */
