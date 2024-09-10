/* Returns non-zero on error, otherwise zero is returned. */
static int
run_win_executable_as_evaluated(const char full_path[])
{
	wchar_t *utf16_path;
	SHELLEXECUTEINFOW sei;

	utf16_path = utf8_to_utf16(full_path);

	memset(&sei, 0, sizeof(sei));
	sei.cbSize = sizeof(sei);
	sei.fMask = SEE_MASK_FLAG_NO_UI | SEE_MASK_NOCLOSEPROCESS;
	sei.lpVerb = L"runas";
	sei.lpFile = utf16_path;
	sei.lpParameters = NULL;
	sei.nShow = SW_SHOWNORMAL;

	if(!ShellExecuteExW(&sei))
	{
		const DWORD last_error = GetLastError();
		free(utf16_path);
		LOG_WERROR(last_error);
		return last_error != ERROR_CANCELLED;
	}

	free(utf16_path);
	CloseHandle(sei.hProcess);
	return 0;
}