/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    STM32/pwm_lld.h
 * @brief   STM32 PWM subsystem low level driver header.
 *
 * @addtogroup PWM
 * @{
 */

#ifndef _PWM_LLD_H_
#define _PWM_LLD_H_

#if HAL_USE_PWM || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Number of PWM channels per PWM driver.
 */
#define PWM_CHANNELS                        4

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @brief   PWMD1 driver enable switch.
 * @details If set to @p TRUE the support for PWMD1 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_PWM_USE_TIM1) || defined(__DOXYGEN__)
#define STM32_PWM_USE_TIM1                  TRUE
#endif

/**
 * @brief   PWMD2 driver enable switch.
 * @details If set to @p TRUE the support for PWMD2 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_PWM_USE_TIM2) || defined(__DOXYGEN__)
#define STM32_PWM_USE_TIM2                  TRUE
#endif

/**
 * @brief   PWMD3 driver enable switch.
 * @details If set to @p TRUE the support for PWMD3 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_PWM_USE_TIM3) || defined(__DOXYGEN__)
#define STM32_PWM_USE_TIM3                  TRUE
#endif

/**
 * @brief   PWMD4 driver enable switch.
 * @details If set to @p TRUE the support for PWMD4 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_PWM_USE_TIM4) || defined(__DOXYGEN__)
#define STM32_PWM_USE_TIM4                  TRUE
#endif

/**
 * @brief   PWMD5 driver enable switch.
 * @details If set to @p TRUE the support for PWMD5 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_PWM_USE_TIM5) || defined(__DOXYGEN__)
#define STM32_PWM_USE_TIM5                  TRUE
#endif

/**
 * @brief   PWMD1 interrupt priority level setting.
 */
#if !defined(STM32_PWM_TIM1_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_PWM_TIM1_IRQ_PRIORITY         7
#endif

/**
 * @brief   PWMD2 interrupt priority level setting.
 */
#if !defined(STM32_PWM_TIM2_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_PWM_TIM2_IRQ_PRIORITY         7
#endif

/**
 * @brief   PWMD3 interrupt priority level setting.
 */
#if !defined(STM32_PWM_TIM3_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_PWM_TIM3_IRQ_PRIORITY         7
#endif

/**
 * @brief   PWMD4 interrupt priority level setting.
 */
#if !defined(STM32_PWM_TIM4_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_PWM_TIM4_IRQ_PRIORITY         7
#endif

/**
 * @brief   PWMD5 interrupt priority level setting.
 */
#if !defined(STM32_PWM_TIM5_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_PWM_TIM5_IRQ_PRIORITY         7
#endif

/*===========================================================================*/
/* Configuration checks.                                                     */
/*===========================================================================*/

#if STM32_PWM_USE_TIM1 && !STM32_HAS_TIM1
#error "TIM1 not present in the selected device"
#endif

#if STM32_PWM_USE_TIM2 && !STM32_HAS_TIM2
#error "TIM2 not present in the selected device"
#endif

#if STM32_PWM_USE_TIM3 && !STM32_HAS_TIM3
#error "TIM3 not present in the selected device"
#endif

#if STM32_PWM_USE_TIM4 && !STM32_HAS_TIM4
#error "TIM4 not present in the selected device"
#endif

#if STM32_PWM_USE_TIM5 && !STM32_HAS_TIM5
#error "TIM5 not present in the selected device"
#endif

#if !STM32_PWM_USE_TIM1 && !STM32_PWM_USE_TIM2 &&                           \
    !STM32_PWM_USE_TIM3 && !STM32_PWM_USE_TIM4 &&                           \
    !STM32_PWM_USE_TIM5
#error "PWM driver activated but no TIM peripheral assigned"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   PWM channel type.
 */
typedef uint8_t pwmchannel_t;

/**
 * @brief   PWM counter type.
 */
typedef uint16_t pwmcnt_t;

/**
 * @brief PWM logic mode.
 */
typedef enum {
  PWM_OUTPUT_DISABLED = 0,          /**< Output not driven, callback only.  */
  PWM_OUTPUT_ACTIVE_HIGH = 1,       /**< Idle is logic level 0.             */
  PWM_OUTPUT_ACTIVE_LOW = 2         /**< Idle is logic level 1.             */
} pwmmode_t;

/**
 * @brief   PWM driver channel configuration structure.
 */
typedef struct {
  /**
   * @brief Channel active logic level.
   */
  pwmmode_t                 mode;
  /**
   * @brief Channel callback pointer.
   * @note  This callback is invoked on the channel compare event. If set to
   *        @p NULL then the callback is disabled.
   */
  pwmcallback_t             callback;
  /* End of the mandatory fields.*/
} PWMChannelConfig;

/**
 * @brief   PWM driver configuration structure.
 */
typedef struct {
  /**
   * @brief   Timer clock in Hz.
   * @note    The low level can use assertions in order to catch invalid
   *          frequency specifications.
   */
  uint32_t                  frequency;
  /**
   * @brief   PWM period in ticks.
   * @note    The low level can use assertions in order to catch invalid
   *          period specifications.
   */
  pwmcnt_t                  period;
  /**
   * @brief Periodic callback pointer.
   * @note  This callback is invoked on PWM counter reset. If set to
   *        @p NULL then the callback is disabled.
   */
  pwmcallback_t             callback;
  /**
   * @brief Channels configurations.
   */
  PWMChannelConfig          channels[PWM_CHANNELS];
  /* End of the mandatory fields.*/
  /**
   * @brief TIM CR2 register initialization data.
   * @note  The value of this field should normally be equal to zero.
   */
  uint16_t                  cr2;
} PWMConfig;

/**
 * @brief   Structure representing a PWM driver.
 */
struct PWMDriver {
  /**
   * @brief Driver state.
   */
  pwmstate_t                state;
  /**
   * @brief Current driver configuration data.
   */
  const PWMConfig           *config;
  /**
   * @brief   Current PWM period in ticks.
   */
  pwmcnt_t                  period;
#if defined(PWM_DRIVER_EXT_FIELDS)
  PWM_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
  /**
   * @brief Bit mask of the enabled channels.
   */
  uint32_t                  enabled_channels;
  /**
   * @brief Pointer to the TIMx registers block.
   */
  TIM_TypeDef               *tim;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if STM32_PWM_USE_TIM1 && !defined(__DOXYGEN__)
extern PWMDriver PWMD1;
#endif

#if STM32_PWM_USE_TIM2 && !defined(__DOXYGEN__)
extern PWMDriver PWMD2;
#endif

#if STM32_PWM_USE_TIM3 && !defined(__DOXYGEN__)
extern PWMDriver PWMD3;
#endif

#if STM32_PWM_USE_TIM4 && !defined(__DOXYGEN__)
extern PWMDriver PWMD4;
#endif

#if STM32_PWM_USE_TIM5 && !defined(__DOXYGEN__)
extern PWMDriver PWMD5;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void pwm_lld_init(void);
  void pwm_lld_start(PWMDriver *pwmp);
  void pwm_lld_stop(PWMDriver *pwmp);
  void pwm_lld_change_period(PWMDriver *pwmp, pwmcnt_t period);
  void pwm_lld_enable_channel(PWMDriver *pwmp,
                              pwmchannel_t channel,
                              pwmcnt_t width);
  void pwm_lld_disable_channel(PWMDriver *pwmp, pwmchannel_t channel);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_PWM */

#endif /* _PWM_LLD_H_ */

/** @} */
