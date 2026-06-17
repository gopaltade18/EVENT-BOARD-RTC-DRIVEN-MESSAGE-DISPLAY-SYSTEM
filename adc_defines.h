//adc_defines.h
#define FOSC 12000000            // Main oscillator frequency (12 MHz)
#define CCLK (FOSC * 5)          // CPU clock frequency after PLL multiplier
#define PCLK (CCLK / 4)          // Peripheral clock frequency (CCLK divided by 4)
#define ADCCLK 3000000           // Desired ADC clock frequency (3 MHz)
#define CLKDIV ((PCLK / ADCCLK) - 1)  // Clock divider to get ADC clock from PCLK

// Defines for ADCR (ADC Control Register) bit positions
#define CLKDIV_BITS 8            // Bit position of CLKDIV field in ADCR (bits 15:8)
#define PDN_BIT 21               // Power-down enable bit for ADC (1 = ADC enabled)
#define ADC_START_BIT 24         // Start bit for ADC conversion

// Defines for ADDR (ADC Data Register) bit positions
#define RESULT_BITS 6            // Starting bit of the 10-bit result in ADDR
#define DONE_BIT 31              // Conversion done flag bit in ADDR

// Pin function defines for configuring pins (for ADC input pins)
#define PIN_FUNC2 1              // Function 2 for pin select (e.g., analog input)
#define AN0_INPUT_PIN PIN_FUNC2  // Pin function for analog input AN0
