//LCD defines.h

// LCD control/data pin mappings on port 0
#define LCD_DATA 8        // @p0.8 to p0.15 -> LCD data lines D0 to D7
#define LCD_RS 16         // @p0.16 -> Register Select (RS) pin
#define LCD_RW 17         // @p0.17 -> Read/Write (RW) pin
#define LCD_EN 18         // @p0.18 -> Enable (EN) pin

// Defines for HD44780 LCD controller commands

#define CLEAR_LCD 0x01            // Clear display and set DDRAM address to 0
#define RET_CUR_HOME 0x02         // Return cursor to home position (0,0)
#define SHIFT_CUR_RIGHT 0x06      // Move cursor right and increment DDRAM address
#define SHIFT_CUR_LEFT 0x07       // Move cursor left and decrement DDRAM address
#define DSP_OFF 0x08              // Display OFF, cursor OFF, blink OFF
#define DSP_ON_CUR_OFF 0x0C       // Display ON, cursor OFF
#define DSP_ON_CUR_ON  0x0E       // Display ON, cursor ON
#define DSP_ON_CUR_BLINK 0x0F     // Display ON, cursor ON, blink ON
#define SHIFT_DSP_LEFT 0x10       // Shift entire display to the left
#define SHIFT_DSP_RIGHT 0x14      // Shift entire display to the right

// LCD interface mode setup
#define MODE_4BIT_1LINE 0x20      // 4-bit interface, 1 line, 5x8 dots
#define MODE_4BIT_2LINE 0x28      // 4-bit interface, 2 lines, 5x8 dots
#define MODE_8BIT_1LINE 0x30      // 8-bit interface, 1 line, 5x8 dots
#define MODE_8BIT_2LINE 0x38      // 8-bit interface, 2 lines, 5x8 dots

// Set DDRAM address for beginning of each line
#define GOTO_LINE1_POS0 0x80      // Line 1, position 0
#define GOTO_LINE2_POS0 0xC0      // Line 2, position 0
#define GOTO_LINE3_POS0 0x94      // Line 3, position 0 (for 4-line displays)
#define GOTO_LINE4_POS0 0xD4      // Line 4, position 0 (for 4-line displays)

// Set CGRAM (Character Generator RAM) address
#define GOTO_CGRAM_START 0x40     // Set CGRAM address to 0 (for custom characters)
