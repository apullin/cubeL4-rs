//
// Created by Andrew Pullin on 9/11/21.
//

#include "stm32l4xx_hal.h"

/* This was introduces to test the trivial C-function wrapping of a
 * function-like macro that was not picked up by bindgen.
 * This need has been worked around by moving the MSP callbacks to a C file
 * the application, which will need to be compiled with cc there.
 */
void HAL_RCC_RNG_CLK_ENABLE( void );