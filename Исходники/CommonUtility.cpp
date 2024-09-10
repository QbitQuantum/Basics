std::wstring CommonUtility::GetPythonPath()
{
	// This function does four things(!) : 1) Executes which.exe python.exe
	// to find the full path of python executable using CreateProcess. 
	// 2) Opens a pipe to read from the standard output of the CreateProcess.
	// 3) Sets the locale to utf-8 and read the standard output to a wstring.
	// 4) Converts each of \ with \\ so that it is directly useful for CreateProcess.
	static std::wstring output;
	if (!output.empty())
		return output;

	HANDLE hChildStd_OUT_Rd = NULL;
	HANDLE hChildStd_OUT_Wr = NULL;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	if (!CreatePipe(&hChildStd_OUT_Rd, &hChildStd_OUT_Wr, &sa, 0) ||
		!SetHandleInformation(hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
		return L"";

	PROCESS_INFORMATION piProcInfo;
	TCHAR systemPath[MAX_PATH];
	GetSystemDirectory(systemPath, MAX_PATH);
	const TCHAR pythonQuery[] = L"\\where.exe python.exe";
	std::wstring python = std::wstring(systemPath) + pythonQuery;
	STARTUPINFO siStartInfo;
	bool bSuccess = FALSE;

	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdOutput = hChildStd_OUT_Wr;
	siStartInfo.dwFlags |= (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
	siStartInfo.wShowWindow = SW_HIDE;

	CreateProcess(NULL,
		const_cast<wchar_t*>(python.c_str()),
		NULL, NULL, TRUE, 0, NULL, NULL,
		&siStartInfo, &piProcInfo);

	CloseHandle(hChildStd_OUT_Wr);

	int fd = _open_osfhandle((intptr_t)hChildStd_OUT_Rd, 0);
	if (-1 == fd)
		return L"";
	FILE* file = _wfdopen(fd, L"rb");
	if (NULL == file)
		return L"";
	
	std::wifstream stream(file);

	const std::locale empty_locale = std::locale::empty();
	typedef std::codecvt_utf8<wchar_t> converter_type;
	const std::codecvt_utf8<wchar_t>* converter = new std::codecvt_utf8 < wchar_t > ;
	const std::locale utf8_locale(empty_locale, converter);

	stream.imbue(utf8_locale);
	stream >> output;
	stream.close();

	std::wstringstream canonical;
	std::wstring::iterator it(output.begin());
	while (it != output.end())
	{
		if (*it == '\\')
			canonical << "\\\\";
		else
			canonical << *it;
		++it;
	}
	return canonical.str();
}