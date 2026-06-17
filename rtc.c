//rtc.c
#include <LPC214X.H>              // Header for LPC214x MCU register definitions

#include "lcd_defines.h"          // LCD command and pin macros
#include "lcd.h"                  // LCD interface functions
#include "rtc_defines.h"          // RTC register macros and constants

// Array to hold names of days of the week (3-letter abbreviations)
char week[][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};


/*
 * Initialize the Real-Time Clock (RTC)
 * Disables RTC, sets prescaler, then enables it
 */
void RTC_Init(void) 
{
  // Disable and reset the RTC
  CCR = RTC_RESET;

  // Set prescaler for RTC clock (used for 32.768 kHz crystal)
  PREINT = PREINT_VAL;     // Integer part of divider
  PREFRAC = PREFRAC_VAL;   // Fractional part of divider

  // Enable RTC and (on LPC2148) select external clock source
  #ifndef _LPC2148_
    CCR = RTC_ENABLE;
  #else
    CCR = RTC_ENABLE | RTC_CLKSRC;
  #endif
}


/*
 * Get the current time from RTC
 * Parameters:
 *  - hour: pointer to store current hour (0–23)
 *  - minute: pointer to store current minute (0–59)
 *  - second: pointer to store current second (0–59)
 */
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
  *hour = HOUR;
  *minute = MIN;
  *second = SEC;
}


/*
 * Display current time on LCD in hh:mm:ss format
 * Parameters:
 *  - hour: value (0–23)
 *  - minute: value (0–59)
 *  - second: value (0–59)
 */
void DisplayRTCTime(u32 hour, u32 minute, u32 second)
{
  // Display hours
  CharLCD((hour / 10) + 48);
  CharLCD((hour % 10) + 48);

  // Separator
  CharLCD(':');

  // Display minutes
  CharLCD((minute / 10) + 48);
  CharLCD((minute % 10) + 48);

  // Separator
  CharLCD(':');

  // Display seconds
  CharLCD((second / 10) + 48);
  CharLCD((second % 10) + 48);
}


/*
 * Get the current date from RTC
 * Parameters:
 *  - date: pointer to store day of month (1–31)
 *  - month: pointer to store month (1–12)
 *  - year: pointer to store year (e.g., 2025)
 */
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
  *date = DOM;
  *month = MONTH;
  *year = YEAR;
}


/*
 * Display current date on LCD in dd/mm/yyyy format
 * Parameters:
 *  - date: value (1–31)
 *  - month: value (1–12)
 *  - year: full year (e.g., 2025)
 */
void DisplayRTCDate(u32 date, u32 month, u32 year)
{
  CmdLCD(GOTO_LINE2_POS0);

  // Display day
  CharLCD((date / 10) + 48);
  CharLCD((date % 10) + 48);
  CharLCD('/');

  // Display month
  CharLCD((month / 10) + 48);
  CharLCD((month % 10) + 48);
  CharLCD('/');

  // Display year
  U32LCD(year);
}


/*
 * Set RTC time manually
 * Parameters:
 *  - hour: value to set (0–23)
 *  - minute: value to set (0–59)
 *  - second: value to set (0–59)
 */
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
{
  HOUR = hour;
  MIN = minute;
  SEC = second;
}


/*
 * Set RTC date manually
 * Parameters:
 *  - date: value to set (1–31)
 *  - month: value to set (1–12)
 *  - year: value to set (e.g., 2025)
 */
void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
  DOM = date;
  MONTH = month;
  YEAR = year;
}


/*
 * Get current day of the week from RTC
 * Parameters:
 *  - day: pointer to store Day of Week (0=Sunday to 6=Saturday)
 */
void GetRTCDay(s32 *day)
{
  *day = DOW;
}


/*
 * Display current day of the week on LCD (right side of line 1)
 * Parameters:
 *  - day: value from 0 (Sunday) to 6 (Saturday)
 */
void DisplayRTCDay(u32 day)
{
  // Move to column 10 of line 1 and display 3-letter day name
  CmdLCD(GOTO_LINE1_POS0 + 10);
  StrLCD(week[day]);  
}


/*
 * Set day of the week in RTC
 * Parameters:
 *  - day: value to set (0=Sunday to 6=Saturday)
 */
void SetRTCDay(u32 day)
{
  DOW = day;
}
