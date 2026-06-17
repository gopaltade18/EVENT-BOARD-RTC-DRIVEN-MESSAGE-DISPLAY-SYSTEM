//settings.h

#include "types.h"

/*
 * Main settings menu function
 */
void settings(void);

/*
 * Edit the time (hour, minute, second)
 */
void Edit_time(void);

/*
 * Edit the date (day, month, year)
 */
void Edit_date(void);

/*
 * Edit the day of the week
 * Returns signed 8-bit updated day value
 */
s8 Edit_day(void);

/*
 * Edit hour value
 * Returns signed 8-bit updated hour
 */
s8 Edit_hour(void);

/*
 * Edit minute value
 * Returns signed 8-bit updated minute
 */
s8 Edit_min(void);

/*
 * Edit second value
 * Returns signed 8-bit updated second
 */
s8 Edit_sec(void);

/*
 * Edit day of the month (date)
 * Returns signed 8-bit updated date
 */
s8 Edit_Ndate(void);

/*
 * Edit month value
 * Returns signed 8-bit updated month
 */
s8 Edit_month(void);

/*
 * Edit year value
 * Returns signed 32-bit updated year
 */
s32 Edit_year(void);

/*
 * Display a message on LCD or interface
 */
void MsgDisp(void);

/*
 * Enable message display or related feature
 */
void MsgEnable(void);

/*
 * Disable message display or related feature
 */
void MsgDisable(void);
