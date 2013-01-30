/*
 * osal_none.h
 *
 *  Created on: Jan 19, 2013
 *      Author: hathach
 */

/*
 * Software License Agreement (BSD License)
 * Copyright (c) 2013, hathach (tinyusb.net)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the tiny usb stack.
 */

/** \file
 *  \brief TBD
 *
 *  \note TBD
 */

/** \ingroup TBD
 *  \defgroup TBD
 *  \brief TBD
 *
 *  @{
 */

#ifndef _TUSB_OSAL_NONE_H_
#define _TUSB_OSAL_NONE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "osal_common.h"

typedef uint32_t osal_timeout_t;

//--------------------------------------------------------------------+
// TASK API
// NOTES: Each blocking OSAL_NONE services such as semaphore wait,
// queue receive embedded return statement, therefore local variable
// retain value before/after such services needed to declare as static
// OSAL_TASK_LOOP
// {
//   OSAL_TASK_LOOP_BEGIN
//
//   task body statements
//
//   OSAL_TASK_LOOP_ENG
// }
//--------------------------------------------------------------------+
#define osal_task_create(code, name, stack_depth, parameters, prio)

#define OSAL_TASK_LOOP  \
  static uint16_t state = 0;\
  switch(state)\

#define OSAL_TASK_LOOP_BEGIN \
  case 0:

#define OSAL_TASK_LOOP_END \
  default:\
    state = 0;
//--------------------------------------------------------------------+
// Semaphore API
//--------------------------------------------------------------------+
typedef uint8_t osal_semaphore_t;
typedef osal_semaphore_t * osal_semaphore_handle_t;

static inline osal_semaphore_handle_t osal_semaphore_create(osal_semaphore_t * const sem) ATTR_CONST ATTR_ALWAYS_INLINE;
static inline osal_semaphore_handle_t osal_semaphore_create(osal_semaphore_t * const sem)
{
  (*sem) = 0;
  return (osal_semaphore_handle_t) sem;
}

static inline  tusb_error_t osal_semaphore_post(osal_semaphore_handle_t const sem_hdl) ATTR_ALWAYS_INLINE;
static inline  tusb_error_t osal_semaphore_post(osal_semaphore_handle_t const sem_hdl)
{
  (*sem_hdl)++;

  return TUSB_ERROR_NONE;
}

#define osal_semaphore_wait(sem_hdl, msec) \
  do {\
    state = __LINE__; case __LINE__:\
    if( (*sem_hdl) == 0 ) \
      return;\
    else\
      (*sem_hdl)--;\
  }while(0)

//--------------------------------------------------------------------+
// QUEUE API
//--------------------------------------------------------------------+
typedef struct{
           uint8_t  *buf         ; ///< buffer pointer
           uint16_t size         ; ///< buffer size
  volatile uint16_t len          ; ///< bytes in fifo
  volatile uint16_t wr_ptr       ; ///< write pointer
  volatile uint16_t rd_ptr       ; ///< read pointer
} osal_queue_t;

typedef osal_queue_t * osal_queue_handle_t;

// queue_send, queue_receive
#define OSAL_DEF_QUEUE(name, size)\
  osal_queue_t name;\
  uint8_t buffer_##name[size]

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_OSAL_NONE_H_ */

/** @} */
