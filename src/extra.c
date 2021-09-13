//
// Created by Andrew Pullin on 9/11/21.
//

#include "extra.h"

#include "stm32l4xx_hal.h"

#include "cmsis_gcc.h"

void HAL_RCC_RNG_CLK_ENABLE()
{
  do {
    __IO uint32_t tmpreg;
    SET_BIT( RCC->AHB2ENR, RCC_AHB2ENR_RNGEN); /* Delay after an RCC peripheral clock enabling */
    tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);
    UNUSED(tmpreg);
  } while (0);
}
