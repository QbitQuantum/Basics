bool set_privilege(_In_z_ const wchar_t* privilege, _In_ bool enable)
{
	if (IsWindowsXPOrGreater())
	{
		HANDLE hToken;
		if (TRUE != OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, FALSE, &hToken))
		{
			if (GetLastError() == ERROR_NO_TOKEN)
			{
				if (ImpersonateSelf(SecurityImpersonation) != TRUE)
				{
					printf("ImpersonateSelf( ) failed. gle=0x%08x", GetLastError());
					return false;
				}

				if (TRUE != OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, FALSE, &hToken))
				{
					printf("OpenThreadToken() failed. gle=0x%08x", GetLastError());
					return false;
				}
			}
			else
			{
				printf("OpenThread() failed. gle=0x%08x", GetLastError());
				return false;
			}
		}

		TOKEN_PRIVILEGES tp = { 0 };
		LUID luid = { 0 };
		DWORD cb = sizeof(TOKEN_PRIVILEGES);
		if (!LookupPrivilegeValue(NULL, privilege, &luid))
		{
			printf("LookupPrivilegeValue() failed. gle=0x%08x", GetLastError());
			CloseHandle(hToken);
			return false;
		}
		tp.PrivilegeCount = 1;
		tp.Privileges[0].Luid = luid;
		if (enable)
		{
			tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		}
		else
		{
			tp.Privileges[0].Attributes = 0;
		}

		if (FALSE == AdjustTokenPrivileges(hToken, FALSE, &tp, cb, NULL, NULL))
		{
			DWORD gle = GetLastError();
			if (gle != ERROR_SUCCESS)
			{
				printf("AdjustTokenPrivileges() failed. gle=0x%08x", GetLastError());
				CloseHandle(hToken);
				return false;
			}
		}

		CloseHandle(hToken);
	}

	return true;
}