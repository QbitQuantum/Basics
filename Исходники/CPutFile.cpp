void CPutFile::CheckExe(wstring installname, wstring name, int type)
{
	if(type == 2)//file
	{
		WCHAR path[MAX_PATH] = {0};
		ExpandEnvironmentStringsW(installname.c_str(), path, MAX_PATH);

		if(::PathFileExistsW(path) == TRUE)
			return;
	}
	else if(type == 1)//reg
	{
		HKEY rootkey;
		size_t nEndKeyName = installname.find_first_of(']', 1);
		std::wstring strKeyName = installname.substr(1, nEndKeyName - 1);

		size_t nEnd = strKeyName.find_first_of('\\');
		std::wstring strRootKey = strKeyName.substr(0, nEnd);

		if(strRootKey == L"HKEY_CURRENT_USER")
			rootkey = HKEY_CURRENT_USER;
		else if (strRootKey == _T("HKEY_LOCAL_MACHINE"))
			rootkey = HKEY_LOCAL_MACHINE;
		else if(strRootKey == _T("HKEY_CLASSES_ROOT"))
			rootkey = HKEY_CLASSES_ROOT;

		std::wstring strKey = strKeyName.substr(nEnd + 1, wstring::npos);

		HKEY hKey = NULL;                               // 操作键句柄

		if (ERROR_SUCCESS == ::RegOpenKeyExW(rootkey, strKey.c_str(), 0, KEY_READ, &hKey))   
		{   
			::RegCloseKey(hKey);
			return;
		} 
	}
	else
		return;

	wstring file = CResourceManager::_()->GetFilePath(m_pWebsiteData->GetWebsiteType(), m_pWebsiteData->GetID(), name.c_str());

	OSVERSIONINFO os = { sizeof(OSVERSIONINFO) };
	::GetVersionEx(&os);
	if(os.dwMajorVersion >= 6)
	{
		SHELLEXECUTEINFOW shExecInfo;
		shExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		shExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;//SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI; 
		shExecInfo.hwnd = NULL;
		shExecInfo.lpVerb = L"runas";
		shExecInfo.lpFile = LPWSTR(file.c_str());
		shExecInfo.lpParameters = NULL;
		shExecInfo.lpDirectory = NULL;
		shExecInfo.nShow = SW_SHOWNORMAL;
		shExecInfo.hInstApp = NULL;

		if (!ShellExecuteExW(&shExecInfo))
		{			
			int err = GetLastError();
			CRecordProgram::GetInstance()->FeedbackError(L"PutFile", err,
				CRecordProgram::GetInstance()->GetRecordInfo(L"CPutFile创建安装进程%s失败！", file.c_str()));
		}
		else
			WaitForSingleObject (shExecInfo.hProcess, INFINITE); 
	}
	else
	{
		STARTUPINFOW si;
		memset (&si, 0, sizeof (STARTUPINFOW));
		si.wShowWindow = SW_HIDE;
		si.cb = sizeof (STARTUPINFOW);
		PROCESS_INFORMATION pi;
		memset (&pi, 0, sizeof (PROCESS_INFORMATION));	

		if (!CreateProcess(NULL, LPWSTR(file.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			CRecordProgram::GetInstance()->FeedbackError(L"PutFile", 1200,
				CRecordProgram::GetInstance()->GetRecordInfo(L"CPutFile创建安装进程%s失败！", file.c_str()));
			return;
		}
		else
			WaitForSingleObject (pi.hProcess, INFINITE); 
		CloseHandle (pi.hThread);
		CloseHandle (pi.hProcess);
	}
	return;
}