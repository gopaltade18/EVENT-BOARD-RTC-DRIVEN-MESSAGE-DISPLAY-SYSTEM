//delay.c

// delay.c
#include "types.h"         // Include custom type definitions (e.g., u32 for unsigned int)

// Function to create a delay in microseconds
void delay_us(u32 dlyus)
{
    dlyus *= 12;           // Multiply input by 12 to adjust for processor speed (approximate)
    while (dlyus--);       // Loop until the delay count reaches 0 (busy wait)
}

// Function to create a delay in milliseconds
void delay_ms(u32 dlyms)
{
    dlyms *= 12000;        // Multiply by 12,000 for millisecond delay (approximate for 12MHz clock)
    while (dlyms--);       // Loop until delay count is over
}

// Function to create a delay in seconds
void delay_s(u32 dlys)
{
    dlys *= 12000000;      // Multiply by 12,000,000 for second delay (for 12MHz clock)
    while (dlys--);        // Loop until delay time completes
}
