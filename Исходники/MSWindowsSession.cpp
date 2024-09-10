HANDLE 
MSWindowsSession::getUserToken(LPSECURITY_ATTRIBUTES security)
{
	HANDLE sourceToken;
	if (!WTSQueryUserToken(m_activeSessionId, &sourceToken)) {
		LOG((CLOG_ERR "could not get token from session %d", m_activeSessionId));
		throw XArch(new XArchEvalWindows);
	}
	
	HANDLE newToken;
	if (!DuplicateTokenEx(
		sourceToken, TOKEN_ASSIGN_PRIMARY | TOKEN_ALL_ACCESS, security,
		SecurityImpersonation, TokenPrimary, &newToken)) {

		LOG((CLOG_ERR "could not duplicate token"));
		throw XArch(new XArchEvalWindows);
	}
	
	LOG((CLOG_DEBUG "duplicated, new token: %i", newToken));
	return newToken;
}