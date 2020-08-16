/**
 * Mir Drualga Common For C
 * Copyright (C) 2020  Mir Drualga
 *
 * This file is part of Mir Drualga Common For C.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Additional permissions under GNU Affero General Public License version 3
 *  section 7
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any program (or a modified version of that program and its
 *  libraries), containing parts covered by the terms of an incompatible
 *  license, the licensors of this Program grant you additional permission
 *  to convey the resulting work.
 */

#ifndef MDC_C_STD_THREADS_H_
#define MDC_C_STD_THREADS_H_

#if __STDC_VERSION__ >= 201112L && !defined(__STDC_NO_THREADS__)

#include <threads.h>

#else

#include <windows.h>

/**
 * Threads
 */

enum {
  thrd_success,
  thrd_nomem,
  thrd_timedout,
  thrd_busy,
  thrd_error
};

typedef int (*thrd_start_t)(void*);

typedef HANDLE thrd_t;

int thrd_create(thrd_t* thr, thrd_start_t func, void* arg);
int thrd_equal(thrd_t lhs, thrd_t rhs);
thrd_t thrd_current(void);
void thrd_yield(void);
void thrd_exit(int res);
int thrd_detach(thrd_t thr);
int thrd_join(thrd_t thr, int *res);

/**
 * Mutual exclusion
 */

enum {
  mtx_plain = 0x1,
  mtx_recursive = 0x4,
  mtx_timed = 0x3
};

typedef struct {
  HANDLE mutex_;
  int type_;

  BOOL is_owned_;
} mtx_t;

int mtx_init(mtx_t* mutex, int type);
void mtx_destroy(mtx_t* mutex);
int mtx_lock(mtx_t* mutex);
int mtx_trylock(mtx_t *mutex);
int mtx_unlock(mtx_t *mutex);

typedef struct {
  LONG has_active_thread_;

  BOOL is_event_init_;
  BOOL is_finished_;

  HANDLE passive_thread_event_;

  CRITICAL_SECTION critical_section_;
} once_flag;

#define ONCE_FLAG_INIT { 0 }

void call_once(once_flag* flag, void (*func)(void));

/**
 * Conditional variables
 */

typedef struct {
  HANDLE waiter_event_;

  BOOL is_broadcast;
  LONG has_signal_pass;
} cnd_t;

int cnd_init(cnd_t* cond);
void cnd_destroy(cnd_t* cond);
int cnd_signal(cnd_t* cond);
int cnd_broadcast(cnd_t* cond);
int cnd_wait(cnd_t* cond, mtx_t* mutex);

#endif

#endif /* MDC_C_STD_THREADS_H_ */