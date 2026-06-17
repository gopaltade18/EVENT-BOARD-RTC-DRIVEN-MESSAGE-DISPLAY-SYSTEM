//pin_connect_block.c

#include "types.h"        // Custom type definitions (e.g., u32)
#include <LPC21XX.h>      // LPC21xx MCU register definitions

/*
 * Configure pin function using PINSEL0 or PINSEL1
 * 
 * Parameters:
 *  - portNo: GPIO port number (currently only port 0 is handled)
 *  - pinNo: Pin number (0–31 for port 0)
 *  - pinFunc: Function to assign (0 = GPIO, 1/2/3 = alternate functions)
 */
void cfgPortPin(u32 portNo, u32 pinNo, u32 pinFunc)
{
    // Only Port 0 is supported
    if(portNo == 0)
    {
        // For pin numbers 0 to 15 -> use PINSEL0
        if(pinNo <= 15)
        {
            // Clear existing function bits (2 bits per pin)
            // Then set new function bits for the specified pin
            PINSEL0 = (PINSEL0 & ~(3 << (pinNo * 2))) | (pinFunc << (pinNo * 2));
        }
        // For pin numbers 16 to 31 -> use PINSEL1
        else if(pinNo >= 16 && pinNo <= 31)
        {
            // Similar logic as above, adjusted for PINSEL1 and offset by 16 pins
            PINSEL1 = (PINSEL1 & ~(3 << ((pinNo - 16) * 2))) | (pinFunc << ((pinNo - 16) * 2));
        }
    }
}
