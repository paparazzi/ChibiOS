/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    sandbox/hal_sio_lld.h
 * @brief   Sandbox SIO subsystem low level driver header.
 *
 * @addtogroup SIO
 * @{
 */

#ifndef HAL_SIO_LLD_H
#define HAL_SIO_LLD_H

#if (HAL_USE_SIO == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    VSIO configuration options
 * @{
 */
/**
 * @brief   SIO driver 1 enable switch.
 * @details If set to @p TRUE the support for VUART1 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SB_SIO_USE_VUART1) || defined(__DOXYGEN__)
#define SB_SIO_USE_VUART1                   FALSE
#endif

/**
 * @brief   SIO driver 2 enable switch.
 * @details If set to @p TRUE the support for VUART2 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SB_SIO_USE_VUART2) || defined(__DOXYGEN__)
#define SB_SIO_USE_VUART2                   FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if !SB_SIO_USE_VUART1 && !SB_SIO_USE_VUART2
#error "SIO driver activated but no VUART peripheral assigned"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Type of a SIO events mask.
 */
typedef uint32_t sio_events_mask_t;

/**
 * @brief   Low level fields of the SIO driver structure.
 */
#define sio_lld_driver_fields                                               \
  /* Number of the associated VUART.*/                                      \
  uint32_t                  nvuart

/**
 * @brief   Low level fields of the SIO configuration structure.
 */
#define sio_lld_config_fields                                               \
  /* Predefined configuration index.*/
  uint32_t                  ncfg

/**
 * @brief   Determines the state of the RX FIFO.
 *
 * @param[in] siop      pointer to the @p SIODriver object
 * @return              The RX FIFO state.
 * @retval false        if RX FIFO is not empty
 * @retval true         if RX FIFO is empty
 *
 * @notapi
 */
#define sio_lld_is_rx_empty(siop) true

/**
 * @brief   Determines the state of the TX FIFO.
 *
 * @param[in] siop      pointer to the @p SIODriver object
 * @return              The TX FIFO state.
 * @retval false        if TX FIFO is not full
 * @retval true         if TX FIFO is full
 *
 * @notapi
 */
#define sio_lld_is_tx_full(siop) true

/**
 * @brief   Determines the transmission state.
 *
 * @param[in] siop      pointer to the @p SIODriver object
 * @return              The TX FIFO state.
 * @retval false        if transmission is idle
 * @retval true         if transmission is ongoing
 *
 * @notapi
 */
#define sio_lld_is_tx_ongoing(siop) true

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if (SB_SIO_USE_VUART1 == TRUE) && !defined(__DOXYGEN__)
extern SIODriver SIOD1;
#endif

#if (SB_SIO_USE_VUART2 == TRUE) && !defined(__DOXYGEN__)
extern SIODriver SIOD2;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void sio_lld_init(void);
  msg_t  sio_lld_start(SIODriver *siop);
  void sio_lld_stop(SIODriver *siop);
  void sio_lld_start_operation(SIODriver *siop);
  void sio_lld_stop_operation(SIODriver *siop);
  sio_events_mask_t sio_lld_get_and_clear_events(SIODriver *siop);
  size_t sio_lld_read(SIODriver *siop, uint8_t *buffer, size_t n);
  size_t sio_lld_write(SIODriver *siop, const uint8_t *buffer, size_t n);
  msg_t sio_lld_get(SIODriver *siop);
  void sio_lld_put(SIODriver *siop, uint_fast16_t data);
  msg_t sio_lld_control(SIODriver *siop, unsigned int operation, void *arg);
  void sio_lld_serve_interrupt(SIODriver *siop);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_SIO == TRUE */

#endif /* HAL_SIO_LLD_H */

/** @} */
