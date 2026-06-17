//lcd.c

#include <LPC21xx.h>       // Header for LPC21xx microcontroller register definitions
#include "types.h"         // Custom type definitions (u8, u32, etc.)
#include "delay.h"         // Delay functions
#include "defines.h"       // Bit manipulation macros
#include "lcd_defines.h"   // LCD pin definitions and command macros
#include "lcd.h"           // LCD function prototypes

// Function to write a byte (data or command) to the LCD
void WriteLCD(u8 byte)
{
  // Put the byte on LCD data pins (P0.8 to P0.15)
  WRITEBYTE(IOPIN0, LCD_DATA, byte);

  // Select write operation (RW = 0)
  IOCLR0 = 1 << LCD_RW;

  // Pulse the enable pin (EN = 1 -> short delay -> EN = 0)
  IOSET0 = 1 << LCD_EN;
  delay_us(1);
  IOCLR0 = 1 << LCD_EN;

  // Wait for LCD to process the data
  delay_ms(2);   
}

// Function to send a command to the LCD
void CmdLCD(u8 cmd)
{
  // Select command register (RS = 0)
  IOCLR0 = 1 << LCD_RS;

  // Write command byte to LCD
  WriteLCD(cmd);
}

// Function to initialize the LCD
void InitLCD(void)
{
  // Initial power-on delay for LCD
  delay_ms(15);
 
  // Configure P0.8 to P0.15 (data lines D0–D7) as GPIO output
  WRITEBYTE(IODIR0, LCD_DATA, 0xFF);

  // Configure control lines (P0.16 = RS, P0.17 = RW, P0.18 = EN) as GPIO output
  WRITENIBBLE(IODIR0, LCD_RS, 7);  // sets 3 bits starting at LCD_RS

  // LCD initialization sequence (as per HD44780 datasheet)
  CmdLCD(0x30);
  delay_ms(4);
  delay_us(100);
  CmdLCD(0x30);
  delay_us(100);
  CmdLCD(0x30);

  // Set LCD mode: 8-bit, 2-line
  CmdLCD(MODE_8BIT_2LINE);

  // Turn on display, cursor off
  CmdLCD(DSP_ON_CUR_OFF);

  // Clear LCD screen
  CmdLCD(CLEAR_LCD);

  // Set cursor movement to right
  CmdLCD(SHIFT_CUR_RIGHT);    	
}

// Function to display a single ASCII character on the LCD
void CharLCD(u8 asciiVal)
{
   // Select data register (RS = 1)
   IOSET0 = 1 << LCD_RS;

   // Send character to DDRAM (LCD display)
   WriteLCD(asciiVal);
}

// Function to display a null-terminated string on the LCD
void StrLCD(s8 *p)
{
  // Loop through each character in the string
  while(*p)
    CharLCD(*p++);
}

// Function to display a signed 32-bit integer on the LCD
void S32LCD(s32 n)
{
  if(n < 0)
  {
    // If number is negative, print '-' and make it positive
    CharLCD('-');
    n = -n;
  } 

  // Display the absolute value as unsigned
  U32LCD(n);
}

// Function to display an unsigned 32-bit integer on the LCD
void U32LCD(u32 n)
{
  u8 a[10];       // Array to hold decimal digits
  s32 i = 0;      // Index

  if(n == 0)
  {
    // Special case for 0
    CharLCD('0');
  }
  else
  {
    // Extract digits from least significant to most
    while(n)
    {
      a[i] = (n % 10) + 48; // Convert digit to ASCII ('0' = 48)
      n /= 10;
      i++;
    }

    // Print digits in reverse order
    for(--i; i >= 0; i--)
    {
      CharLCD(a[i]);
    }
  }
}
