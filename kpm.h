// kpm.h
// Header file for Keypad Module (KPM) functions

#include "types.h"    // Include standard type definitions (u8, u32, s32, etc.)

// Initializes the keypad hardware (configures pins and ports)
void InitKPM(void);

// Scans and returns the active column number detected on the keypad
u32 Colscan(void);

// Checks and returns the active row number detected on the keypad
u32 Rowcheck(void);

// Duplicate declaration of Rowcheck; likely should be removed or renamed
// u32 Rowcheck(void);

// Scans the keypad and returns the key value pressed (scan both rows and columns)
u32 Keyscan(void);

// Reads a multi-digit number input from the keypad, returns the numeric value
u32 ReadNum(void);

// Reads a password input from the keypad (possibly multi-digit), returns password value
u32 ReadPSW(void);

// Reads a signed number input from the keypad with a maximum number of digits specified by the parameter
// The parameter specifies maximum digits allowed for input
s32 ReadNum2(u32 maxDigits);
