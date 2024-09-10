static bool _recursive_delete_directory(WCHAR *directory)
{
	if (directory == NULL) {
		return false;
	}
	WCHAR find_pattern[MAX_PATH];
	wcsncpy(find_pattern, directory, MAX_PATH);
	wcsncat(find_pattern, L"\\*", MAX_PATH);
	WCHAR dir_path[MAX_PATH];
	wcsncpy(dir_path, directory, MAX_PATH);
	wcsncat(dir_path, L"\\", MAX_PATH);
	WCHAR file_path[MAX_PATH];
	wcsncpy(file_path, dir_path, MAX_PATH);
	DWORD err;

	WIN32_FIND_DATAW find_data;
	HANDLE find_handle = FindFirstFileW(find_pattern, &find_data);
	if (find_handle == INVALID_HANDLE_VALUE) {
		err = GetLastError();
		char *error_message = oscap_windows_error_message(err);
		oscap_seterr(OSCAP_EFAMILY_WINDOWS, "FindFirstFileW error: %s", error_message);
		free(error_message);
		return false;
	}

	do {
		if (wcscmp(find_data.cFileName, L".") != 0 && wcscmp(find_data.cFileName, L"..") != 0) {
			wcsncat(file_path, find_data.cFileName, MAX_PATH);
			if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (!_recursive_delete_directory(file_path)) {
					FindClose(find_handle);
					return false;
				}
			} else {
				if (!DeleteFileW(file_path)) {
					err = GetLastError();
					char *error_message = oscap_windows_error_message(err);
					oscap_seterr(OSCAP_EFAMILY_WINDOWS, "DeleteFileW Error: %s", error_message);
					free(error_message);
					FindClose(find_handle);
					return false;
				}
			}
			wcsncpy(file_path, dir_path, MAX_PATH);
		}
	} while (FindNextFileW(find_handle, &find_data) != 0);
	FindClose(find_handle);

	if (!RemoveDirectoryW(dir_path)) {
		err = GetLastError();
		char *error_message = oscap_windows_error_message(err);
		oscap_seterr(OSCAP_EFAMILY_WINDOWS, "RemoveDirectoryW error: %s", error_message);
		free(error_message);
		return false;
	}

	return true;
}