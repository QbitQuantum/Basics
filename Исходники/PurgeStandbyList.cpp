BOOL GetPrivilege(HANDLE TokenHandle, LPCSTR lpName, int flags)
{
	BOOL bResult;
	DWORD dwBufferLength;
	LUID luid;
	TOKEN_PRIVILEGES tpPreviousState;
	TOKEN_PRIVILEGES tpNewState;

	dwBufferLength = 16;
	bResult = LookupPrivilegeValueA(0, lpName, &luid);
	if (bResult)
	{
		tpNewState.PrivilegeCount = 1;
		tpNewState.Privileges[0].Luid = luid;
		tpNewState.Privileges[0].Attributes = 0;
		bResult = AdjustTokenPrivileges(TokenHandle, 0, &tpNewState, (LPBYTE)&(tpNewState.Privileges[1]) - (LPBYTE)&tpNewState, &tpPreviousState, &dwBufferLength);
		if (bResult)
		{
			tpPreviousState.PrivilegeCount = 1;
			tpPreviousState.Privileges[0].Luid = luid;
			tpPreviousState.Privileges[0].Attributes = flags != 0 ? 2 : 0;
			bResult = AdjustTokenPrivileges(TokenHandle, 0, &tpPreviousState, dwBufferLength, 0, 0);
		}
	}
	return bResult;
}