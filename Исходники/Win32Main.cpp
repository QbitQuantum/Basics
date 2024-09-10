int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPWSTR szCmdLine, int iCmdShow)
{
#ifdef _WIN32
	if (fileno (stdout) != -1 &&
		_get_osfhandle (fileno (stdout)) != -1)
	{
		/* stdout is fine, presumably redirected to a file or pipe */
	}
    else
    {
		typedef BOOL (WINAPI * AttachConsole_t) (DWORD);

		AttachConsole_t p_AttachConsole =
			(AttachConsole_t) GetProcAddress (GetModuleHandleW(L"kernel32.dll"), "AttachConsole");

		if (p_AttachConsole != NULL && p_AttachConsole (ATTACH_PARENT_PROCESS))
		{
			_wfreopen (L"CONOUT$", L"w", stdout);
			dup2 (fileno (stdout), 1);
			_wfreopen (L"CONOUT$", L"w", stderr);
			dup2 (fileno (stderr), 2);

		}
	}
#endif

	// Dummy ANSI command line
	return AP_Win32App::WinMain("AbiWord", hInstance, hPrevInstance, "abiword.exe", iCmdShow);
}