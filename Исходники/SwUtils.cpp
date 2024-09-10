TStatus GetUnElevatedToken(CAutoHandle& hToken)
{
	HWND hShellWnd = GetShellWindow();
	if(hShellWnd == NULL)
	{
		SW_TSTATUS_RET(SW_ERR_WND_NOT_FOUND, L"GetShellWindow() return NULL");
	}
	DWORD dwShellPID = 0;
	GetWindowThreadProcessId(hShellWnd, &dwShellPID);
	SW_WINBOOL_RET(dwShellPID != 0);

	CAutoHandle hShellProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwShellPID);
	SW_WINBOOL_RET(hShellProcess.IsValid());

	CAutoHandle hShellProcessToken;

	SW_WINBOOL_RET(OpenProcessToken(hShellProcess, TOKEN_DUPLICATE, &hShellProcessToken));

	const DWORD dwTokenRights = TOKEN_QUERY | TOKEN_ASSIGN_PRIMARY | TOKEN_DUPLICATE | TOKEN_ADJUST_DEFAULT | TOKEN_ADJUST_SESSIONID;
	SW_WINBOOL_RET(DuplicateTokenEx(hShellProcessToken, dwTokenRights, NULL, SecurityImpersonation, TokenPrimary, &hToken));

	SW_RETURN_SUCCESS;
}