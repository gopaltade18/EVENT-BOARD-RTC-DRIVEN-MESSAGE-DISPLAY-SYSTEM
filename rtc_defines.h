//rtc_defines.h

#ifndef _RTC_DEFINES_H
#define _RTC_DEFINES_H

// System clock and peripheral clock Macros

#define FOSC    12000000            // Main oscillator frequency (12 MHz)
#define CCLK    (FOSC * 5)          // CPU clock (FOSC multiplied by PLL factor)
#define PCLK    (CCLK / 4)          // Peripheral clock (derived from CCLK)

// RTC Prescaler Macros (used to generate 1-second tick from PCLK)

#define PREINT_VAL   (int)((PCLK / 32768) - 1)       // Integer part of RTC prescaler
#define PREFRAC_VAL  (PCLK - ((PREINT_VAL + 1) * 32768))  // Fractional part of prescaler

// RTC Control Macros

#define RTC_ENABLE   (1 << 0)       // Bit to enable RTC
#define RTC_RESET    (1 << 1)       // Bit to reset RTC
#define RTC_CLKSRC   (1 << 4)       // Selects external clock source (1 = RTCX1)

// Define target MCU (used in conditional compilation)
#define _LPC2148_

#endif
