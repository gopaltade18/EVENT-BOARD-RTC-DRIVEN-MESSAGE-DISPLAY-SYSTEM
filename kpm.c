// kpm.c

#include<lpc21xx.h>         // Include LPC21xx microcontroller definitions
#include "types.h"          // Custom type definitions
#include "kpm_defines.h"    // Keypad-related pin definitions/macros
#include "defines.h"        // General definitions used throughout the project
#include "lcd_defines.h"    // LCD pin and command definitions
#include "lcd.h"            // LCD control functions
#include "delay.h"          // Delay functions

// Lookup table representing the keys on the 4x4 matrix keypad
u32 kpmLUT[4][4] = {
    {'1','2','3','/'},
    {'4','5','6','*'},
    {'7','8','9','-'},
    {'C','0','=','+'}
};

// Initialize the keypad
void InitKPM(void)
{
    // Configure keypad rows (ROW0 to ROW3) as output
    WRITENIBBLE(IODIR1, ROW0, 15);  // Set 4 row lines as output
    // Columns remain as input by default
}

// Check if any key is pressed in any column
u32 Colscan(void)
{
    u32 t;
    t = READNIBBLE(IOPIN1, COL0);  // Read column inputs
    return (t < 15) ? 0 : 1;       // If any bit is low, key is pressed (return 0)
}

// Find the row where a key is pressed
u32 Rowcheck(void)
{
    u32 r;
    for (r = 0; r <= 3; r++)       // Check each row
    {
        // Ground one row at a time (set low)
        WRITENIBBLE(IOPIN1, ROW0, ~(1 << r));
        // If any key is pressed in this row
        if (Colscan() == 0)
        {
            break;                 // Found the row
        }
    }
    // Re-initialize rows
    WRITENIBBLE(IOPIN1, ROW0, 0);
    return r;                      // Return row number
}

// Find the column where a key is pressed
u32 Colcheck(void)
{
    u32 c;
    for (c = 0; c <= 3; c++)       // Check each column
    {
        if (READBIT(IOPIN1, COL0 + c) == 0) // If line is low, key is pressed
            break;
    }
    return c;                      // Return column number
}

// Get the key value from the keypad
u32 Keyscan(void)
{
    u32 r, c, keyv;

    while (Colscan());            // Wait for key press

    // Get row number where key is pressed
    r = Rowcheck();

    // Get column number where key is pressed
    c = Colcheck();

    // Get the actual key character from lookup table
    keyv = kpmLUT[r][c];

    while (Colscan() == 0);       // Wait for key release
    return keyv;
}

/*
This function was likely used for entering a number using the keypad.
It is commented out now.

u32 ReadNum(void)
{
    u32 sum = 0;
    u32 num = 0;
    u32 count = 10;
    u32 test_count = 0;

    while (1)
    {
        if (test_count <= count)
        {
            num = Keyscan();                   // Read key
            while (Colscan() == 0);            // Wait for key release

            if (num >= '0' && num <= '9')      // If it's a digit
            {
                sum = (sum * 10) + (num - '0');// Update the number
                CmdLCD(GOTO_LINE2_POS0);       
                U32LCD(sum);                   // Display number
            }
            else if (num == '=')               // End input
            {
                break;
            }
            else if (num == 'C')               // Clear input
            {
                sum = 0;
                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("     ");               // Clear LCD
            }
            else if (num == '-')               // Backspace/delete
            {
                if (sum > 0)
                {
                    sum = sum / 10;
                    CmdLCD(GOTO_LINE2_POS0);
                    U32LCD(sum);
                    StrLCD("        ");
                }
            }
            test_count++;
        }
        else if (test_count > 10)
        {
            return 0;
        }
    }
    return sum;
}
*/

// Function to read a password input with masked characters
u32 ReadPSW(void)
{
    u32 sum = 0;
    s8 key;
    u32 count = 0;

    while (1)
    {
        key = Keyscan();  // Read key from keypad

        if ((key >= '0') && (key <= '9')) // If digit
        {
            sum = (sum * 10) + (key - '0'); // Add to password
            CmdLCD(GOTO_LINE2_POS0 + count);
            CharLCD('*');                  // Display '*' instead of digit
            count++;
            while (Colscan() == 0);        // Wait for key release
        }
        else if (key == '-')               // Backspace
        {
            if (count > 0)
            {
                sum = sum / 10;            // Remove last digit
                count--;
                CmdLCD(GOTO_LINE2_POS0 + count);
                CharLCD(' ');              // Erase '*'
                CmdLCD(GOTO_LINE2_POS0 + count);
            }
            while (Colscan() == 0);
        }
        else if (key == 'C')               // Clear all
        {
            sum = 0;
            CmdLCD(GOTO_LINE2_POS0);
            StrLCD("    ");                // Clear LCD
            count = 0;
        }
        else if (key == '=')               // Enter/OK
        {
            while (Colscan() == 0);
            break;
        }
    }

    return sum; // Return password number
}

// Function to read number with character limit, optional masking
s32 ReadNum2(u32 n)
{
    u32 sum = 0;
    s8 key;
    u32 count = 0, char_cnt = 0;

    while (1)
    {
        key = Keyscan(); // Get key from keypad

        if ((key >= '0') && (key <= '9')) // If digit
        {
            if (n == 10)
            {
                sum = (sum * 10) + (key - '0');
                CmdLCD(GOTO_LINE2_POS0 + count);
                CharLCD('*');           // Show '*' for password-like input
                count++;
            }
            else
            {
                sum = (sum * 10) + (key - '0');
                CmdLCD(GOTO_LINE2_POS0);
                U32LCD(sum);           // Show number normally
                count++;
            }

            char_cnt++; // Track number of digits entered

            // If max allowed characters exceeded, return -1 (error)
            if ((n == 10 || n == 2 || n == 4) && char_cnt > n)
            {
                return -1;
            }

            while (Colscan() == 0);
        }
        else if (key == '-')          // Backspace
        {
            if (count > 0)
            {
                sum = sum / 10;
                count--;
                char_cnt--;
                CmdLCD(GOTO_LINE2_POS0 + count);
                CharLCD(' ');         // Clear last char
                CmdLCD(GOTO_LINE2_POS0 + count);
            }
            while (Colscan() == 0);
        }
        else if (key == 'C')          // Clear
        {
            sum = 0;
            CmdLCD(GOTO_LINE2_POS0);
            StrLCD("    ");           // Clear LCD
            count = 0;
            char_cnt = 0;
        }
        else if (key == '=' && count > 0) // Enter/OK
        {
            while (Colscan() == 0);
            break;
        }
    }

    return sum; // Return the entered number
}
