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

#ifndef MDC_C_OBJECT_INTEGER_OBJECT_H_
#define MDC_C_OBJECT_INTEGER_OBJECT_H_

#include "internal/integer_object/integer_object_declare_macros.h"
#include "internal/integer_object/integer_object_define_macros.h"
#include "internal/integer_object/integer_object_name_macros.h"
#include "internal/integer_object/integer_object_typedef.h"

#include "../../../dllexport_define.inc"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define MDC_DECLARE_SIGNED_INTEGER(T_IntT) \
    MDC_INTERNAL_DECLARE_SIGNED_INTEGER(T_IntT)

#define MDC_DEFINE_SIGNED_INTEGER(T_IntT) \
    MDC_INTERNAL_DEFINE_SIGNED_INTEGER_FUNCTIONS(T_IntT)

#define MDC_DECLARE_UNSIGNED_INTEGER(T_IntT) \
    MDC_INTERNAL_DECLARE_UNSIGNED_INTEGER(T_IntT)

#define MDC_DEFINE_UNSIGNED_INTEGER(T_IntT) \
    MDC_INTERNAL_DEFINE_UNSIGNED_INTEGER_FUNCTIONS(T_IntT)

MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_SChar)
MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_Short)
MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_Int)
MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_Long)

MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_UChar)
MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_UShort)
MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_UInt)
MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_ULong)

#if __cplusplus >= 201103L \
    || __STDC_VERSION__ >= 199901L \
    || _MSC_VER >= 1600

MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_LLong)
MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_ULLong)

#endif /* __cplusplus >= 201103L \
    || __STDC_VERSION__ >= 199901L \
    || _MSC_VER >= 1600 */

MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_Int8)
MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_Int16)
MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_Int32)
MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_Int64)

MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_IntLeast8)
MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_IntLeast16)
MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_IntLeast32)
MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_IntLeast64)

MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_IntMax)

MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_UInt8)
MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_UInt16)
MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_UInt32)
MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_UInt64)

MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_UIntLeast8)
MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_UIntLeast16)
MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_UIntLeast32)
MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_UIntLeast64)

MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_UIntMax)

MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_Intptr)
MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_UIntptr)

MDC_INTERNAL_DECLARE_DLLEXPORT_UNSIGNED_INTEGER(Mdc_Size)
MDC_INTERNAL_DECLARE_DLLEXPORT_SIGNED_INTEGER(Mdc_Ptrdiff)


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#include "../../../dllexport_undefine.inc"
#endif /* MDC_C_OBJECT_INTEGER_OBJECT_H_ */
