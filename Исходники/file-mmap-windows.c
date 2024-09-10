static void*
open_handle (void *handle, const gunichar2 *mapName, gint mapName_length, int mode, gint64 *capacity, int access, int options, int *ioerror, MonoError *error)
{
	g_assert (handle != NULL);

	// INVALID_HANDLE_VALUE (-1) is valid, to make named shared memory,
	// backed by physical memory / pagefile.

	if (handle == INVALID_HANDLE_VALUE) {
		if (*capacity <= 0 && mode != FILE_MODE_OPEN) {
			*ioerror = CAPACITY_MUST_BE_POSITIVE;
			return NULL;
		}
#if SIZEOF_VOID_P == 4
		if (*capacity > UINT32_MAX) {
			*ioerror = CAPACITY_LARGER_THAN_LOGICAL_ADDRESS_SPACE;
			return NULL;
		}
#endif
		if (!(mode == FILE_MODE_CREATE_NEW || mode == FILE_MODE_OPEN_OR_CREATE || mode == FILE_MODE_OPEN)) {
			*ioerror = INVALID_FILE_MODE;
			return NULL;
		}
	} else {
		FILE_STANDARD_INFO info;
		if (!GetFileInformationByHandleEx (handle, FileStandardInfo, &info, sizeof (FILE_STANDARD_INFO))) {
			*ioerror = convert_win32_error (GetLastError (), COULD_NOT_OPEN);
			return NULL;
		}
		if (*capacity == 0) {
			if (info.EndOfFile.QuadPart == 0) {
				*ioerror = CAPACITY_SMALLER_THAN_FILE_SIZE;
				return NULL;
			}
		} else if (*capacity < info.EndOfFile.QuadPart) {
			*ioerror = CAPACITY_SMALLER_THAN_FILE_SIZE;
			return NULL;
		}
	}

	HANDLE result = NULL;

	if (mode == FILE_MODE_CREATE_NEW || handle != INVALID_HANDLE_VALUE) {
		result = CreateFileMappingW (handle, NULL, get_page_access (access) | options, (DWORD)(((guint64)*capacity) >> 32), (DWORD)*capacity, mapName);
		if (result && GetLastError () == ERROR_ALREADY_EXISTS) {
			CloseHandle (result);
			result = NULL;
			*ioerror = FILE_ALREADY_EXISTS;
		} else if (!result && GetLastError () != NO_ERROR) {
			*ioerror = convert_win32_error (GetLastError (), COULD_NOT_OPEN);
		}
	} else if (mode == FILE_MODE_OPEN || mode == FILE_MODE_OPEN_OR_CREATE && access == MMAP_FILE_ACCESS_WRITE) {