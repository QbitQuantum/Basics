int WINAPI w32u_init(void)
{
	// Initialize the Win32 Unicode Translation Layer.
	if (init_counter++ != 0)
	{
		// The Win32 Unicode Translation Layer is already initialized.
		return ERR_W32U_SUCCESS;
	}
	
	// Check for UTF-8 compatibility.
	if (w32u_check_UTF8() != 0)
	{
		// System doesn't support UTF-8.
		return -ERR_W32U_UTF8_NOT_SUPPORTED;
	}
	
	// Check if the system supports Unicode.
	if (GetModuleHandleW(NULL) != NULL)
	{
		// GetModuleHandleW() returned gens.exe's module handle.
		// This means the system supports Unicode.
		
		// Check if ANSI mode is forced on the command line.
		const char *lpCmdLine = GetCommandLineA();
		if (!strstr(lpCmdLine, " --ansi"))
		{
			// ANSI mode is not forced. Enable Unicode.
			w32u_is_unicode = 1;
		}
		else
		{
			// ANSI mode is forced. Disable Unicode.
			w32u_is_unicode = 0;
		}
	}
	else
	{
		// GetModuleHandleW(NULL) returned NULL.
		// This means the system doesn't support Unicode.
		w32u_is_unicode = 0;
	}
	
	// Get DLL version numbers.
	comctl32_dll_version = GetDllVersionNumber("comctl32.dll");
	shell32_dll_version = GetDllVersionNumber("shell32.dll");
	
	// Initialize the Unicode modules.
	w32u_windows_init();
	w32u_windowsx_init();
	w32u_commctrl_init();
	w32u_shellapi_init();
	w32u_libc_init();
	w32u_commdlg_init();
	w32u_shlobj_init();
	w32u_winnls_init();
	
	// Win32 Unicode Translation Layer initialized successfully.
	return ERR_W32U_SUCCESS;
}