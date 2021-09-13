 /**
  ******************************************************************************
  * @file    stm32l4r9i_eval_idd.h
  * @author  MCD Application Team
  * @brief   Header file for stm32l4r9i_eval_idd.c module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L4R9I_EVAL_IDD_H
#define __STM32L4R9I_EVAL_IDD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4r9i_eval.h"
/* Include Idd measurement component driver */
#include "../Components/mfxstm32l152/mfxstm32l152.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32L4R9I_EVAL
  * @{
  */

/** @addtogroup STM32L4R9I_EVAL_IDD
  * @{
  */

/** @defgroup STM32L4R9I_EVAL_IDD_Exported_Defines  Exported Defines
  * @{
  */
/**
  * @brief  IDD Status values
  */
typedef enum
{
  IDD_OK = 0,
  IDD_TIMEOUT = 1,
  IDD_ZERO_VALUE = 2,
  IDD_ERROR = 0xFF
}
IDD_StatusTypeDef;

/**
  * @brief  Shunt values on evaluation board in milli ohms
  */
#define EVAL_IDD_SHUNT0_VALUE                  ((uint16_t) 1000)     /*!< value in milliohm */
#define EVAL_IDD_SHUNT1_VALUE                  ((uint16_t) 24)       /*!< value in ohm */
#define EVAL_IDD_SHUNT2_VALUE                  ((uint16_t) 620)      /*!< value in ohm */
#define EVAL_IDD_SHUNT4_VALUE                  ((uint16_t) 10000)    /*!< value in ohm */

/**
  * @brief  Shunt stabilization delay on evaluation board in milli ohms
  */
#define EVAL_IDD_SHUNT0_STABDELAY              ((uint8_t) 149)       /*!< value in millisec */
#define EVAL_IDD_SHUNT1_STABDELAY              ((uint8_t) 149)       /*!< value in millisec */
#define EVAL_IDD_SHUNT2_STABDELAY              ((uint8_t) 149)       /*!< value in millisec */
#define EVAL_IDD_SHUNT4_STABDELAY              ((uint8_t) 255)       /*!< value in millisec */

/**
  * @brief  IDD Ampli Gain on evaluation board
  */
#define EVAL_IDD_AMPLI_GAIN                    ((uint16_t) 4967)     /*!< value is gain * 100 */

/**
  * @brief  IDD Vdd Min on evaluation board
  */
#define EVAL_IDD_VDD_MIN                       ((uint16_t) 1710)     /*!< value in millivolt */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup STM32L4R9I_EVAL_IDD_Exported_Functions  Exported Functions
  * @{
  */
uint8_t   BSP_IDD_Init(void);
void      BSP_IDD_DeInit(void);
void      BSP_IDD_Reset(void);
void      BSP_IDD_LowPower(void);
void      BSP_IDD_WakeUp(void);
void      BSP_IDD_StartMeasure(void);
void      BSP_IDD_Config(IDD_ConfigTypeDef IddConfig);
void      BSP_IDD_GetValue(uint32_t *IddValue);
void      BSP_IDD_EnableIT(void);
void      BSP_IDD_ClearIT(void);
uint8_t   BSP_IDD_GetITStatus(void);
void      BSP_IDD_DisableIT(void);
uint8_t   BSP_IDD_ErrorGetCode(void);
void      BSP_IDD_ErrorEnableIT(void);
void      BSP_IDD_ErrorClearIT(void);
uint8_t   BSP_IDD_ErrorGetITStatus(void);
void      BSP_IDD_ErrorDisableIT(void);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32L4R9I_EVAL_IDD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
