bool IsConsoleHelper(LPCWSTR pszProcessName)
{
	if (IsTerminalServer(pszProcessName)
		|| IsGitBashHelper(pszProcessName))
		return true;
	return false;
}