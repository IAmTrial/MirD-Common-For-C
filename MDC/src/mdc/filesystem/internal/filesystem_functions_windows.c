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

#include "../../../../include/mdc/filesystem/internal/filesystem_functions.h"

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>
#include <shlwapi.h>

#include "../../../../include/mdc/malloc/malloc.h"

struct Mdc_Fs_Path Mdc_Fs_AbsoluteFromPath(
    const struct Mdc_Fs_Path* path
) {
  struct Mdc_Fs_Path absolute_path;
  Mdc_Fs_Path_ValueType* absolute_path_cstr;

  const Mdc_Fs_Path_ValueType* path_cstr;

  path_cstr = Mdc_Fs_Path_CStr(path);

  absolute_path_cstr = _wfullpath(NULL, path_cstr, 0);
  if (absolute_path_cstr == NULL) {
    goto return_bad;
  }

  absolute_path = Mdc_Fs_Path_InitFromCWStr(
      absolute_path_cstr
  );

  free(absolute_path_cstr);

  return absolute_path;

free_absolute_path_cstr:
  free(absolute_path_cstr);

return_bad:
  ;
}

/*
* TODO (Mir Drualga): Delete this function implementation when
* Mdc_Fs_StatusFromPath is complete.
*/
bool Mdc_Fs_ExistsFromPath(
    const struct Mdc_Fs_Path* path
) {
  return PathFileExistsW(Mdc_Fs_Path_CStr(path));
}

struct Mdc_Fs_Path Mdc_Fs_GetCurrentPath(void) {
  struct Mdc_Fs_Path current_path;

  DWORD current_path_cap;
  DWORD get_current_directory_result;

  wchar_t* current_path_cstr;

  /* Alloc space for the current path. */
  current_path_cap = GetCurrentDirectoryW(0, NULL);

  current_path_cstr = Mdc_malloc(
      current_path_cap * sizeof(current_path_cstr[0])
  );

  if (current_path_cstr == NULL) {
    goto return_bad;
  }

  /* Get the current path and init the Path object. */
  get_current_directory_result = GetCurrentDirectoryW(
      current_path_cap,
      current_path_cstr
  );

  if (get_current_directory_result == 0) {
    goto free_current_path_cstr;
  }

  current_path = Mdc_Fs_Path_InitFromCWStr(current_path_cstr);

  Mdc_free(current_path_cstr);

  return current_path;

free_current_path_cstr:
  Mdc_free(current_path_cstr);

return_bad:
  ;
}

void Mdc_Fs_SetCurrentPath(
    const struct Mdc_Fs_Path* current_path
) {
  const Mdc_Fs_Path_ValueType* current_path_cstr;

  BOOL is_set_current_directory_success;

  current_path_cstr = Mdc_Fs_Path_CStr(current_path);
  is_set_current_directory_success = SetCurrentDirectoryW(current_path_cstr);
}

struct Mdc_Fs_FileStatus Mdc_Fs_StatusFromPath(
    const struct Mdc_Fs_Path* path
) {
  /* TODO (Mir Drualga): Complete this function. */
  struct Mdc_Fs_FileStatus file_status;

  const wchar_t* path_cstr;
  DWORD file_attributes;
  DWORD binary_type;

  enum Mdc_Fs_FileType file_type;
  enum Mdc_Fs_Perms permissions;

  HANDLE file_handle;

  permissions = Mdc_Fs_Perms_kOwnerRead
      | Mdc_Fs_Perms_kGroupRead
      | Mdc_Fs_Perms_kOthersRead;

  path_cstr = Mdc_Fs_Path_CStr(path);

  /* Check if file exists. */
  if (!PathFileExistsW(path_cstr)) {
    if (GetLastError() == ERROR_FILE_NOT_FOUND) {
      file_type = Mdc_Fs_FileType_kNotFound;
    } else {
      file_type = Mdc_Fs_FileType_kNone;
    }

    file_status = Mdc_Fs_FileStatus_InitFromType(
        file_type
    );

    return file_status;
  }

  file_attributes = GetFileAttributesW(path_cstr);
  if (file_attributes == -1) {
    file_status = Mdc_Fs_FileStatus_InitFromType(
        Mdc_Fs_FileType_kUnknown
    );

    return file_status;
  }

  /* Determine exec and write permissions. */
  if (GetBinaryTypeW(path_cstr, &binary_type)) {
    permissions |= Mdc_Fs_Perms_kOwnerExec
        | Mdc_Fs_Perms_kGroupExec
        | Mdc_Fs_Perms_kOthersExec;
  } else if ((file_attributes & FILE_ATTRIBUTE_READONLY) == 0) {
    permissions = permissions | Mdc_Fs_Perms_kOwnerWrite;
  }

  /* Determine file type. */
  file_handle = CreateFileW(
      path_cstr,
      0,
      0,
      NULL,
      OPEN_EXISTING,
      file_attributes,
      NULL
  );

  if (file_handle == INVALID_HANDLE_VALUE) {
    goto return_bad;
  }

  if ((file_attributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
    file_status = Mdc_Fs_FileStatus_InitFromType(
        Mdc_Fs_FileType_kDirectory
    );

    return file_status;
  }

return_bad:
  ;
}

struct Mdc_Fs_SpaceInfo* Mdc_Fs_SpaceFromPath(
    struct Mdc_Fs_SpaceInfo* space_info,
    const struct Mdc_Fs_Path* path
) {
  BOOL is_get_disk_free_space_ex_success;

  ULARGE_INTEGER available_space;
  ULARGE_INTEGER total_space;
  ULARGE_INTEGER free_space;

  struct Mdc_Fs_Path parent_path;

  const Mdc_Fs_Path_ValueType* parent_path_cstr;

  if (!Mdc_Fs_ExistsFromPath(path)) {
    goto return_bad;
  }

  parent_path = Mdc_Fs_Path_ParentPath(path);

  parent_path_cstr = Mdc_Fs_Path_CStr(&parent_path);

  is_get_disk_free_space_ex_success = GetDiskFreeSpaceExW(
      parent_path_cstr,
      &available_space,
      &total_space,
      &free_space
  );

  space_info->available = available_space.QuadPart;
  space_info->capacity = total_space.QuadPart;
  space_info->free = free_space.QuadPart;

  Mdc_Fs_Path_Deinit(&parent_path);

  return space_info;

return_bad:
  return NULL;
}

struct Mdc_Fs_Path Mdc_Fs_TempDirectoryPath(void) {
  void* realloc_result;

  struct Mdc_Fs_Path temp_directory_path;
  DWORD temp_directory_path_cap;
  DWORD get_temp_path_result;

  wchar_t* temp_directory_path_cstr;

  /* Alloc space for the temp directory path. */
  temp_directory_path_cstr = Mdc_malloc(sizeof(wchar_t));
  if (temp_directory_path_cstr == NULL) {
    goto return_bad;
  }

  temp_directory_path_cap = GetTempPathW(0, temp_directory_path_cstr);

  realloc_result = Mdc_realloc(
      temp_directory_path_cstr,
      temp_directory_path_cap
  );

  if (realloc_result == NULL) {
    goto free_temp_directory_path_cstr;
  }

  temp_directory_path_cstr = realloc_result;

  /* Get the temp directory path and init the Path object. */
  get_temp_path_result = GetTempPathW(
      temp_directory_path_cap,
      temp_directory_path_cstr
  );

  if (get_temp_path_result == 0) {
    goto free_temp_directory_path_cstr;
  }

  temp_directory_path = Mdc_Fs_Path_InitFromCWStr(
      temp_directory_path_cstr
  );

  Mdc_free(temp_directory_path_cstr);

  return temp_directory_path;

free_temp_directory_path_cstr:
  Mdc_free(temp_directory_path_cstr);

return_bad:
  ;
}

#endif /* defined(_WIN32) || defined(_WIN64) */
