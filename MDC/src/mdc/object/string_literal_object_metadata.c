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

#include "../../../include/mdc/object/string_literal_object.h"

#include "../../../include/mdc/std/threads.h"

#define MDC_DEFINE_STRING_LITERAL_OBJECT_METADATA(name, type) \
\
/**
 * Object initialization/deinitialization
 */ \
\
static void* name##_InitDefaultAsVoid(void* obj) { \
  return (void*) name##_InitDefault(obj); \
} \
\
static void* name##_InitCopyAsVoid(void* dest, const void* src) { \
  return (void*) name##_InitCopy(dest, src); \
} \
\
static void* name##_InitMoveAsVoid(void* dest, void* src) { \
  return (void*) name##_InitMove(dest, src); \
} \
\
static void name##_DeinitAsVoid(void* obj) { \
  name##_Deinit(obj); \
} \
\
/**
 * Object assignment functions
 */ \
\
static void* name##_AssignCopyAsVoid(void* dest, const void* src) { \
  return (void*) name##_AssignCopy(dest, src); \
} \
\
static void* name##_AssignMoveAsVoid(void* dest, void* src) { \
  return (void*) name##_AssignMove(dest, src); \
} \
\
/**
 * Object comparison operators
 */ \
\
static bool name##_EqualAsVoid(const void* op1, const void* op2) { \
  return name##_Equal(op1, op2); \
} \
\
static int name##_CompareAsVoid(const void* op1, const void* op2) { \
  return name##_Compare(op1, op2); \
} \
\
/**
 * Object etc. functions
 */ \
\
static void name##_SwapAsVoid(void* obj1, void* obj2) { \
  name##_Swap(obj1, obj2); \
} \
\
/**
 * Metadata
 */ \
\
static struct Mdc_ObjectMetadata name##global_metadata = \
    MDC_OBJECT_METADATA_UNINIT; \
static once_flag name##global_metadata_once_flag = ONCE_FLAG_INIT; \
\
static struct Mdc_ObjectMetadata* name##_InitObjectMetadata( \
    struct Mdc_ObjectMetadata* metadata \
) { \
  metadata->size = sizeof(const type*); \
\
  metadata->functions.init_default = &name##_InitDefaultAsVoid; \
  metadata->functions.init_copy = &name##_InitCopyAsVoid; \
  metadata->functions.init_move = &name##_InitMoveAsVoid; \
  metadata->functions.deinit = &name##_DeinitAsVoid; \
\
  metadata->functions.assign_copy = &name##_AssignCopyAsVoid; \
  metadata->functions.assign_move = &name##_AssignMoveAsVoid; \
\
  metadata->functions.equal = &name##_EqualAsVoid; \
  metadata->functions.compare = &name##_CompareAsVoid; \
\
  metadata->functions.swap = &name##_SwapAsVoid; \
\
  return metadata; \
} \
\
static void name##_InitGlobalObjectMetadata(void) { \
  name##_InitObjectMetadata(&name##global_metadata); \
} \
\
/**
 * Metadata
 */ \
\
const struct Mdc_ObjectMetadata* name##_GetObjectMetadata(void) { \
  call_once( \
      &name##global_metadata_once_flag, \
      &name##_InitGlobalObjectMetadata \
  ); \
\
  return &name##global_metadata; \
}

MDC_DEFINE_STRING_LITERAL_OBJECT_METADATA(Mdc_StringLiteral, char);
MDC_DEFINE_STRING_LITERAL_OBJECT_METADATA(Mdc_WStringLiteral, wchar_t);

#undef MDC_DEFINE_STRING_LITERAL_OBJECT_METADATA