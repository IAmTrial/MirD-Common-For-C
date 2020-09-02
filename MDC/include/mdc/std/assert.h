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
 *
 *  This file includes source code pasted from the following location:
 *  https://stackoverflow.com/questions/3385515/static-assert-in-c
 */

#ifndef MDC_C_STD_ASSERT_H_
#define MDC_C_STD_ASSERT_H_

#include <assert.h>

#if __STDC_VERSION__ < 201112L && !defined(static_assert)

/* Delivers an error if the assertion fails. The message isn't usable though. */
#define MDC_UNDERLYING_STATIC_ASSERT_03(COND, MSG) \
    typedef struct { char a; } error_##MSG[(!!(COND))*2-1]

#define MDC_UNDERLYING_STATIC_ASSERT_02(expression, counter, line) \
    MDC_UNDERLYING_STATIC_ASSERT_03(expression, static_assertion_##counter##_at_line_##line)

#define MDC_UNDERLYING_STATIC_ASSERT_01(expression, counter, line) \
    MDC_UNDERLYING_STATIC_ASSERT_02(expression, counter, line)

#define static_assert(expression, message) \
    MDC_UNDERLYING_STATIC_ASSERT_01(expression, __COUNTER__, __LINE__)

#endif /* __STDC_VERSION__ >= 201112L && !defined(static_assert) */

#endif /* MDC_C_STD_ASSERT_H_ */
