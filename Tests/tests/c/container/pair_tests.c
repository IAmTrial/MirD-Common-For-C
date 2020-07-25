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

#include "map_tests.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <c/container/map.h>
#include "string_int_pair/string_int_pair.h"

/**
 * External functions
 */

static const char* const kBasicExampleText[] = {
    "The", "quick", "brown", "fox", "jumped", "over", "the", "lazy",
    "dog."
};

static const char* const kRepeatingExampleText[] = {
    "sort", "the", "sort", "table", "the", "way", "to", "sort",
    "what", "the", "sort", "said"
};

enum FILE_SCOPE_CONSTANTS_08 {
  kBasicExampleTextCount = sizeof(kBasicExampleText)
      / sizeof(kBasicExampleText[0]),
  kRepeatingExampleTextCount = sizeof(kRepeatingExampleText)
      / sizeof(kRepeatingExampleText[0])
};

static void Mdc_Pair_AssertInitDeinit(void) {
  const char* const kFirstSrc = "Hello world";
  const int kSecondSrc = 42;

  struct Mdc_PairMetadata metadata;
  struct Mdc_PairMetadata* init_metadata;

  const struct Mdc_PairFirstFunctions* const first_functions =
      &metadata.functions.first_functions;
  const struct Mdc_PairSecondFunctions* const second_functions =
      &metadata.functions.second_functions;

  struct Mdc_Pair pair;
  struct Mdc_Pair* init_pair;

  init_metadata = Mdc_PairStringIntMetadata_Init(&metadata);

  assert(init_metadata == &metadata);

  char** first = malloc(sizeof(*first));
  assert(first != NULL);

  int* second = malloc(sizeof(*second));
  assert(second != NULL);

  *second = kSecondSrc;

  Mdc_String_InitCopy(first, &kFirstSrc);
  assert(*first != NULL);

  init_pair = Mdc_Pair_InitFirstSecond(
      &pair,
      &metadata,
      first,
      second
  );
  assert(init_pair == &pair);

  /* Check that the initialization completed correctly. */
  assert(memcmp(pair.metadata, &metadata, sizeof(*pair.metadata)) == 0);

  assert(pair.first != NULL);
  assert(first_functions->compare(pair.first, &kFirstSrc) == 0);

  assert(pair.second != NULL);
  assert(second_functions->compare(pair.second, &kSecondSrc) == 0);

  Mdc_Pair_Deinit(&pair);
}

static void Mdc_Pair_AssertInitCopyDeinit(void) {
  const char* const kFirstSrc = "Hello world";
  const int kSecondSrc = 42;

  struct Mdc_PairMetadata metadata;
  struct Mdc_PairMetadata* init_metadata;

  const struct Mdc_PairFirstFunctions* const first_functions =
      &metadata.functions.first_functions;
  const struct Mdc_PairSecondFunctions* const second_functions =
      &metadata.functions.second_functions;

  struct Mdc_Pair pair;
  struct Mdc_Pair* init_pair;

  init_metadata = Mdc_PairStringIntMetadata_Init(&metadata);
  assert(init_metadata == &metadata);

  init_pair = Mdc_Pair_InitFirstCopySecondCopy(
      &pair,
      &metadata,
      &kFirstSrc,
      &kSecondSrc
  );
  assert(init_pair == &pair);

  /* Check that the initialization completed correctly. */
  assert(memcmp(pair.metadata, &metadata, sizeof(*pair.metadata)) == 0);

  assert(pair.first != NULL);
  assert(first_functions->compare(pair.first, &kFirstSrc) == 0);

  assert(pair.second != NULL);
  assert(second_functions->compare(pair.second, &kSecondSrc) == 0);

  Mdc_Pair_Deinit(&pair);
}

static void Mdc_Pair_AssertCompareFirst(void) {
  const char* const kFirstSrc1 = "Hello world";
  const int kSecondSrc = 42;

  const char* const kFirstSrc2 = "Hello world!";

  struct Mdc_PairMetadata metadata;

  const struct Mdc_PairFirstFunctions* const first_functions =
      &metadata.functions.first_functions;
  const struct Mdc_PairSecondFunctions* const second_functions =
      &metadata.functions.second_functions;

  struct Mdc_Pair pair1;
  struct Mdc_Pair pair2;

  struct Mdc_Pair* init_pair1;
  struct Mdc_Pair* init_pair2;

  Mdc_PairStringIntMetadata_Init(&metadata);

  Mdc_Pair_InitFirstCopySecondCopy(
      &pair1,
      &metadata,
      &kFirstSrc1,
      &kSecondSrc
  );

  Mdc_Pair_InitFirstCopySecondCopy(
      &pair2,
      &metadata,
      &kFirstSrc2,
      &kSecondSrc
  );

  assert(Mdc_Pair_Compare(&pair1, &pair2) < 0);
  assert(Mdc_Pair_Compare(&pair2, &pair1) > 0);
  assert(Mdc_Pair_Compare(&pair1, &pair1) == 0);
  assert(second_functions->compare(pair1.second, pair2.second) == 0);

  /* Check that the initialization completed correctly. */
  assert(memcmp(pair1.metadata, &metadata, sizeof(*pair1.metadata)) == 0);

  assert(pair1.first != NULL);
  assert(first_functions->compare(pair1.first, &kFirstSrc1) == 0);

  assert(pair1.second != NULL);
  assert(second_functions->compare(pair1.second, &kSecondSrc) == 0);

  assert(memcmp(pair2.metadata, &metadata, sizeof(*pair2.metadata)) == 0);

  assert(pair2.first != NULL);
  assert(first_functions->compare(pair2.first, &kFirstSrc2) == 0);

  assert(pair2.second != NULL);
  assert(second_functions->compare(pair2.second, &kSecondSrc) == 0);

  Mdc_Pair_Deinit(&pair2);
  Mdc_Pair_Deinit(&pair1);
}

static void Mdc_Pair_AssertCompareSecond(void) {
  const char* const kFirstSrc = "Hello world";
  const int kSecondSrc1 = 42;

  const int kSecondSrc2 = 43;

  struct Mdc_PairMetadata metadata;

  const struct Mdc_PairFirstFunctions* const first_functions =
      &metadata.functions.first_functions;
  const struct Mdc_PairSecondFunctions* const second_functions =
      &metadata.functions.second_functions;

  struct Mdc_Pair pair1;
  struct Mdc_Pair pair2;

  struct Mdc_Pair* init_pair1;
  struct Mdc_Pair* init_pair2;

  Mdc_PairStringIntMetadata_Init(&metadata);

  Mdc_Pair_InitFirstCopySecondCopy(
      &pair1,
      &metadata,
      &kFirstSrc,
      &kSecondSrc1
  );

  Mdc_Pair_InitFirstCopySecondCopy(
      &pair2,
      &metadata,
      &kFirstSrc,
      &kSecondSrc2
  );

  assert(Mdc_Pair_Compare(&pair1, &pair2) < 0);
  assert(Mdc_Pair_Compare(&pair2, &pair1) > 0);
  assert(Mdc_Pair_Compare(&pair1, &pair1) == 0);
  assert(first_functions->compare(pair1.first, pair2.first) == 0);

  /* Check that the initialization completed correctly. */
  assert(memcmp(pair1.metadata, &metadata, sizeof(*pair1.metadata)) == 0);

  assert(pair1.first != NULL);
  assert(first_functions->compare(pair1.first, &kFirstSrc) == 0);

  assert(pair1.second != NULL);
  assert(second_functions->compare(pair1.second, &kSecondSrc1) == 0);

  assert(memcmp(pair2.metadata, &metadata, sizeof(*pair2.metadata)) == 0);

  assert(pair2.first != NULL);
  assert(first_functions->compare(pair2.first, &kFirstSrc) == 0);

  assert(pair2.second != NULL);
  assert(second_functions->compare(pair2.second, &kSecondSrc2) == 0);

  Mdc_Pair_Deinit(&pair2);
  Mdc_Pair_Deinit(&pair1);
}

void Mdc_Pair_RunTests(void) {
  Mdc_Pair_AssertInitDeinit();
  Mdc_Pair_AssertInitCopyDeinit();
  Mdc_Pair_AssertCompareFirst();
  Mdc_Pair_AssertCompareSecond();
}
