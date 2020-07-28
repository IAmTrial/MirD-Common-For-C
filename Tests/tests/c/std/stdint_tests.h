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

#ifndef MDC_TESTS_C_STD_STDINT_H_
#define MDC_TESTS_C_STD_STDINT_H_

void Mdc_Std_AssertInt8Size(void);
void Mdc_Std_AssertInt16Size(void);
void Mdc_Std_AssertInt32Size(void);

void Mdc_Std_AssertUInt8Size(void);
void Mdc_Std_AssertUInt16Size(void);
void Mdc_Std_AssertUInt32Size(void);

void Mdc_Std_AssertIntptrSize(void);
void Mdc_Std_AssertUintptrSize(void);

#endif /* MDC_TESTS_C_STD_STDINT_H_ */