// increases the send buffer to a bigger size
bool CEMSocket::UseBigSendBuffer()
{
#define BIGSIZE 128 * 1024
	if (m_bUsesBigSendBuffers)
		return true;
	m_bUsesBigSendBuffers = true;
    int val = BIGSIZE;
    int vallen = sizeof(int);
	int oldval = 0;
	GetSockOpt(SO_SNDBUF, &oldval, &vallen);
	if (val > oldval)
		SetSockOpt(SO_SNDBUF, &val, sizeof(int));
	val = 0;
	vallen = sizeof(int);
	GetSockOpt(SO_SNDBUF, &val, &vallen);
#if defined(_DEBUG) || defined(_BETA)
	if (val == BIGSIZE)
		theApp.QueueDebugLogLine(false, _T("Increased Sendbuffer for uploading socket from %uKB to %uKB"), oldval/1024, val/1024);
	else
		theApp.QueueDebugLogLine(false, _T("Failed to increase Sendbuffer for uploading socket, stays at %uKB"), oldval/1024);
#endif
	return val == BIGSIZE;
}