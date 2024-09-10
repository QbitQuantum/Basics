	BOOL GetSessionUserToken(ULONG SessionId, LPHANDLE lphUserToken) {
		BOOL   bResult = FALSE;
		HANDLE hImpersonationToken = INVALID_HANDLE_VALUE;
		if (lphUserToken != NULL) {
			if (_WTSQueryUserToken (SessionId, &hImpersonationToken)) {
				bResult = DuplicateTokenEx(hImpersonationToken, 0, NULL, SecurityImpersonation, TokenPrimary, lphUserToken);
				CloseHandle(hImpersonationToken);
			}            
		}
		return bResult;
	}