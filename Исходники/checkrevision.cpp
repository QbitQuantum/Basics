MEXP(int) getExeInfo(const char* file_name, char* exe_info,
					 size_t exe_info_size, uint32_t* version, int platform)
{
	const char* base = (char*) 0;
	unsigned long file_size;
	FILE* f = (FILE*) 0;
	int ret;
#ifdef MOS_WINDOWS
	HANDLE hFile;
	FILETIME ft;
	SYSTEMTIME st;
	LPBYTE buf;
	VS_FIXEDFILEINFO* ffi;
	DWORD infoSize, bytesRead;
#else
	cm_pe_t pe;
	cm_pe_resdir_t* root;
	cm_pe_resdir_t* dir;
	cm_pe_version_t ffi;
	size_t i;
	struct stat st;
	struct tm* time;
#endif
	
	if (!file_name || !exe_info || !exe_info_size || !version)
		return 0;

	base = get_basename(file_name);

	switch (platform) {
		case BNCSUTIL_PLATFORM_X86:
#ifdef MOS_WINDOWS				
                        infoSize = GetFileVersionInfoSizeA(file_name, &bytesRead);
			if (infoSize == 0)
				return 0;
			buf = (LPBYTE) VirtualAlloc(NULL, infoSize, MEM_COMMIT,
										PAGE_READWRITE);
			if (buf == NULL)
				return 0;
                        if (GetFileVersionInfoA(file_name, NULL, infoSize, buf) == FALSE)
				return 0;
                        if (!VerQueryValueA(buf, "\\", (LPVOID*) &ffi, (PUINT) &infoSize))
				return 0;
			
			*version =
				((HIWORD(ffi->dwProductVersionMS) & 0xFF) << 24) |
				((LOWORD(ffi->dwProductVersionMS) & 0xFF) << 16) |
				((HIWORD(ffi->dwProductVersionLS) & 0xFF) << 8) | 
				(LOWORD(ffi->dwProductVersionLS) & 0xFF);
#if DEBUG
			bncsutil_debug_message_a("%s version = %d.%d.%d.%d (0x%08X)",
				base, (HIWORD(ffi->dwProductVersionMS) & 0xFF),
				(LOWORD(ffi->dwProductVersionMS) & 0xFF),
				(HIWORD(ffi->dwProductVersionLS) & 0xFF),
				(LOWORD(ffi->dwProductVersionLS) & 0xFF),
				*version);
#endif
			VirtualFree(buf, 0lu, MEM_RELEASE);
#else
			pe = cm_pe_load(file_name);
			if (!pe)
				return 0;
			root = cm_pe_load_resources(pe);
			if (!root) {
				cm_pe_unload(pe);
				return 0;
			}
				
			for (i = 0; i < root->subdir_count; i++) {
				dir = (root->subdirs + i);
				if (dir->name == 16) {
					if (!cm_pe_fixed_version(pe, dir->subdirs->resources,
											 &ffi))
					{
						cm_pe_unload_resources(root);
						cm_pe_unload(pe);
						return 0;
					}
					break;
				}
			}
			*version =
				((HIWORD(ffi.dwProductVersionMS) & 0xFF) << 24) |
				((LOWORD(ffi.dwProductVersionMS) & 0xFF) << 16) |
				((HIWORD(ffi.dwProductVersionLS) & 0xFF) << 8) | 
				(LOWORD(ffi.dwProductVersionLS) & 0xFF);
#if DEBUG
			bncsutil_debug_message_a("%s version = %d.%d.%d.%d (0x%08X)",
				base, (HIWORD(ffi.dwProductVersionMS) & 0xFF),
				(LOWORD(ffi.dwProductVersionMS) & 0xFF),
				(HIWORD(ffi.dwProductVersionLS) & 0xFF),
				(LOWORD(ffi.dwProductVersionLS) & 0xFF),
				*version);
#endif
			
			cm_pe_unload_resources(root);
			cm_pe_unload(pe);
#endif
			break;
		case BNCSUTIL_PLATFORM_MAC:
		case BNCSUTIL_PLATFORM_OSX:
			f = fopen(file_name, "r");
			if (!f)
				return 0;
			if (fseek(f, -4, SEEK_END) != 0) {
				fclose(f);
				return 0;
			}
			if (fread(version, 4, 1, f) != 1) {
				fclose(f);
				return 0;
			}
#ifdef MOS_WINDOWS
			fclose(f);
#endif
	}
	
#ifdef MOS_WINDOWS
        hFile = CreateFileA(file_name, GENERIC_READ, FILE_SHARE_READ, NULL,
					   OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return 0;
	file_size = GetFileSize(hFile, NULL);
	if (!GetFileTime(hFile, &ft, NULL, NULL)) {
		CloseHandle(hFile);
		return 0;
	}
	
	if (!FileTimeToSystemTime(&ft, &st)) {
		CloseHandle(hFile);
		return 0;
	}
	CloseHandle(hFile);
	
	ret = snprintf(exe_info, exe_info_size,
				   "%s %02u/%02u/%02u %02u:%02u:%02u %lu", base, st.wMonth,
				   st.wDay, (st.wYear % 100), st.wHour, st.wMinute, st.wSecond,
				   file_size);

#else
	if (!f)
		f = fopen(file_name, "r");
	if (!f)
		return 0;
	if (fseek(f, 0, SEEK_END) == -1) {
		fclose(f);
		return 0;
	}
	file_size = ftell(f);
	fclose(f);
	
	if (stat(file_name, &st) != 0)
		return 0;
	
	time = gmtime(&st.st_mtime);
	if (!time)
		return 0;
	
	switch (platform) {
		case BNCSUTIL_PLATFORM_MAC:
		case BNCSUTIL_PLATFORM_OSX:
			if (time->tm_year >= 100) // y2k
				time->tm_year -= 100;
			break;
	}
	
	ret = (int) snprintf(exe_info, exe_info_size,
						"%s %02u/%02u/%02u %02u:%02u:%02u %lu", base, 
						(time->tm_mon+1), time->tm_mday, time->tm_year,
						time->tm_hour, time->tm_min, time->tm_sec, file_size);
#endif

#if DEBUG
	bncsutil_debug_message(exe_info);
#endif

	return ret;
}