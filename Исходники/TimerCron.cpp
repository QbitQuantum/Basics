void DoShutdown()
{
	{
		Sleep(1000);
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;
		// Get a token for this process.
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		{
			AfxMessageBox("OpenProcessToken Error!");
			return;
		}
		// Get the LUID for the shutdown privilege.
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
		tkp.PrivilegeCount = 1; // one privilege to set
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, NULL);
		if (GetLastError() != ERROR_SUCCESS)
		{
			AfxMessageBox("重启失败");
			return;
		}
		// Shut down the system and force all applications to close.
		ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0);
		
	}
}