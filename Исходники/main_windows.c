static int started_by_explorer(void) {
	int rc;
	int result = 0;
	PROCESSENTRY32 entry;
	DWORD process_id = GetCurrentProcessId();
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	char buffer[MAX_PATH];
	size_t length;

	if (handle == INVALID_HANDLE_VALUE) {
		rc = ERRNO_WINAPI_OFFSET + GetLastError();

		log_warn("Could not create process list snapshot: %s (%d)",
		         get_errno_name(rc), rc);

		return 0;
	}

	ZeroMemory(&entry, sizeof(entry));

	entry.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(handle, &entry)) {
		do {
			if (entry.th32ProcessID == process_id) {
				process_id = entry.th32ParentProcessID;

				if (Process32First(handle, &entry)) {
					do {
						if (entry.th32ProcessID == process_id) {
							if (get_process_image_name(entry, buffer,
							                           sizeof(buffer)) < 0) {
								break;
							}

							if (stricmp(buffer, "explorer.exe") == 0) {
								result = 1;
							} else {
								length = strlen(buffer);

								if (length > 13 /* = strlen("\\explorer.exe") */ &&
								    (stricmp(buffer + length - 13, "\\explorer.exe") == 0 ||
								     stricmp(buffer + length - 13, ":explorer.exe") == 0)) {
									result = 1;
								}
							}

							break;
						}
					} while (Process32Next(handle, &entry));
				}

				break;
			}
		} while (Process32Next(handle, &entry));
	}

	CloseHandle(handle);

	return result;
}