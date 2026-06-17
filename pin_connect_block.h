//pin_connect_block.h

#include "types.h"

/*
 * Configure a pin's function on the specified port.
 * 
 * Parameters:
 *  - portNo: Port number (e.g., 0)
 *  - pinNo: Pin number within the port (0–31)
 *  - pinFunc: Function selection value (0=GPIO, 1/2/3 = alternate functions)
 */
void cfgPortPin(u32 portNo, u32 pinNo, u32 pinFunc);
