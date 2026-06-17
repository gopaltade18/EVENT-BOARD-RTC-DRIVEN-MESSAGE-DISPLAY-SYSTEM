#include "types.h"               // Include user-defined types like u8, u32, f32 etc.
#include "pin_connect_block.h"   // Include pin configuration functions
#include "delay.h"               // Include delay functions for timing
#include "adc_defines.h"         // Include ADC-related macros and constants
#include <LPC21XX.h>             // Include LPC2148 MCU specific definitions

// Function to initialize the ADC peripheral
void Init_ADC(void)
{
  // Configure pin P0.28 as analog input AN0 pin
  cfgPortPin(0, 28, AN0_INPUT_PIN);

  // Configure ADCR (ADC Control Register)
  // Set PDN (Power Down) bit to power on ADC
  // Set CLKDIV to configure ADC clock based on PCLK and desired ADCCLK
  ADCR = (1 << PDN_BIT) | (CLKDIV << CLKDIV_BITS);
}

// Function to start ADC conversion on a specific channel, read digital and analog results
void Read_ADC(u8 chNo, f32 *eAR, u32 *dVal)
{
  // Clear previous channel selections, keep other bits intact by masking lower 8 bits
  ADCR &= 0xFFFFFF00;

  // Start ADC conversion by setting START bit and select channel chNo
  ADCR |= (1 << ADC_START_BIT) | (1 << chNo);

  // Small delay for conversion time (~3 microseconds)
  delay_us(3);

  // Wait in a blocking loop until conversion is complete (DONE bit in ADDR register is set)
  while (((ADDR >> DONE_BIT) & 1) == 0);

  // Stop ADC conversion by clearing START bit
  ADCR &= ~(1 << ADC_START_BIT);

  // Read the 10-bit ADC result from ADDR register by shifting and masking relevant bits
  *dVal = ((ADDR >> RESULT_BITS) & 1023);

  // Convert digital value to voltage (floating point), assuming 3.3V reference and 10-bit ADC
  *eAR = (*dVal * (3.3 / 1023));
}

// Function to read temperature from LM35 sensor connected to ADC channel 1
u32 Read_LM35()
{
  f32 eAR;        // Variable to store analog voltage reading
  u32 dVal;       // Variable to store digital ADC value
  u32 tdegC;      // Variable to store temperature in degree Celsius (integer)
  static u32 flag;  // Static flag to ensure ADC is initialized only once

  if(flag == 0)       // If ADC not initialized yet
  {
    Init_ADC();       // Initialize ADC hardware
    flag = 1;         // Set flag to avoid re-initializing
  }

  Read_ADC(1, &eAR, &dVal);  // Read ADC channel 1 (LM35 output voltage)
  
  tdegC = eAR * 100;          // Convert voltage to temperature in Celsius (10mV per degree, LM35 output)

  return tdegC;               // Return temperature as integer value
}
