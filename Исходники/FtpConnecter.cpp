FtpConnecter::~FtpConnecter(void)
{
	if (m_FtpInfo._hWaitableTimer != NULL)
	{
		CancelWaitableTimer(m_FtpInfo._hWaitableTimer);
		CloseHandle(m_FtpInfo._hWaitableTimer);
	}
	if (m_hWorkThread)
		CloseHandle(m_hWorkThread);
}