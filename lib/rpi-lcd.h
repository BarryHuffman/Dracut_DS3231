/* Copyright (C) 2019  Thorsten Kukuk

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License version 2.1 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */

#ifndef __RPI_LCD_H__
#define __RPI_LCD_H__

#include <stdint.h>

// commands
#define LCD_CLEARDISPLAY   0x01
#define LCD_RETURNHOME     0x02
#define LCD_ENTRYMODESET   0x04
#define LCD_CURSORSHIFT    0x10
#define LCD_FUNCTIONSET    0x20
#define LCD_SETCGRAMADDR   0x40
#define LCD_SETDDRAMADDR   0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT     0x00
#define LCD_ENTRYLEFT      0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON   0x0C
#define LCD_DISPLAYOFF 	0x08
#define LCD_CURSORON    0x0E
#define LCD_CURSOROFF   0x00
#define LCD_BLINKON     0x01
#define LCD_BLINKOFF    0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE  0x00
#define LCD_MOVERIGHT   0x04
#define LCD_MOVELEFT    0x00

// flags for function set
#define LCD_8BITMODE    0x10
#define LCD_4BITMODE    0x00
#define LCD_2LINE       0x08
#define LCD_1LINE       0x00
#define LCD_5x10DOTS    0x04
#define LCD_5x8DOTS     0x00

// flags for backlight control
#define LCD_BACKLIGHT   0x08
#define LCD_NOBACKLIGHT 0x00

/* opens a file handle to the LCD i2c device. busid is the
   i2c bus, on Rasperry Pi 2 and newer normally 1, and the
   address is normally "0x27". init is either 0 or 1, with
   1 the LCD device is initialized, with 0 the device get's
   only opened. Normally "1" is right argument. */
int lcdSetup (uint8_t address, uint8_t busid, int init);

/* Close the file handle to the device */
void lcdClose (int device);

/* Clear the device. The "cursor" is not moved. */
void lcdClear (int device);

/* Write a string to the LCD device. The line can be in the range
   from 0-4, 0 means the new text is written from the current position,
   1-4 means it's written in that row. '\n' is converted to the correct
   control sequence. */
void lcdWriteString (int device, int line, char *str);

void lcdDisplayOff (int device);
void lcdDisplayOn (int device);


#endif  /* __RPI_LCD_H__ */
