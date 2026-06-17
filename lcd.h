//LCD.h

#include "types.h"  // Include user-defined type definitions (e.g., u8, u32, f32, etc.)

// Writes a raw byte (command or data) to the LCD
void WriteLCD(u8 byte);

// Sends a command byte to the LCD (e.g., clear display, set cursor)
void CmdLCD(u8 cmd);

// Initializes the LCD in the desired mode (typically 4-bit, 2-line, etc.)
void InitLCD(void);

// Displays a single ASCII character on the LCD
void CharLCD(u8 asciival);

// Displays a null-terminated string on the LCD
void StrLCD(s8 *str);

// Displays an unsigned 32-bit integer on the LCD
void U32LCD(u32 num);

// Displays a signed 32-bit integer on the LCD
void S32LCD(s32 num);

// Displays a floating-point number on the LCD with a specified number of decimal places
void F32LCD(f32 num, u32 precision);

// Loads a custom character pattern into CGRAM (Character Generator RAM)
// 'p' points to pattern data (5x8 format), 'nbytes' is number of bytes to write
void BuildCGRAM(u8 *p, u8 nbytes);
