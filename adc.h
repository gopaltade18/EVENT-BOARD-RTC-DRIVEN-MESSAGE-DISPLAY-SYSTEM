//adc.h

#include "types.h"

/*
 * Initialize the ADC hardware and configure necessary pins
 */
void Init_ADC(void);

/*
 * Read the ADC value from specified channel
 * Parameters:
 *   chNo - ADC channel number to read from
 *   eAR  - pointer to store the equivalent analog voltage reading (float)
 *   dVal - pointer to store the raw digital ADC value (unsigned int)
 */
void Read_ADC(u8 chNo, f32 *eAR, u32 *dVal);

/*
 * Read temperature value from LM35 sensor connected to ADC
 * Returns temperature in degrees Celsius as unsigned 32-bit integer
 */
u32 Read_LM35(void);
