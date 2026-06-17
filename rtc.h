#ifndef _RTC_H
#define _RTC_H

#include "types.h"

/*
 * Initialize the Real-Time Clock (RTC)
 */
void RTC_Init(void);

/*
 * Get current RTC time
 * Parameters: pointers to store hour, minute, and second (all signed 32-bit)
 */
void GetRTCTimeInfo(s32 *, s32 *, s32 *);

/*
 * Display the RTC time on LCD
 * Parameters: hour, minute, second (unsigned 32-bit)
 */
void DisplayRTCTime(u32, u32, u32);

/*
 * Get current RTC date
 * Parameters: pointers to store date, month, and year (all signed 32-bit)
 */
void GetRTCDateInfo(s32 *, s32 *, s32 *);

/*
 * Display the RTC date on LCD
 * Parameters: date, month, year (unsigned 32-bit)
 */
void DisplayRTCDate(u32, u32, u32);

/*
 * Set the RTC time
 * Parameters: hour, minute, second (unsigned 32-bit)
 */
void SetRTCTimeInfo(u32, u32, u32);

/*
 * Set the RTC date
 * Parameters: date, month, year (unsigned 32-bit)
 */
void SetRTCDateInfo(u32, u32, u32);

/*
 * Get the current day of the week
 * Parameter: pointer to store day of week (signed 32-bit)
 */
void GetRTCDay(s32 *);

/*
 * Display the current day of the week on LCD
 * Parameter: day of week (unsigned 32-bit)
 */
void DisplayRTCDay(u32);

/*
 * Set the day of the week in RTC
 * Parameter: day of week (unsigned 32-bit)
 */
void SetRTCDay(u32);

#endif
