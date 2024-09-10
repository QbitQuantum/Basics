unsigned int SocketSender::GetSendResult()
{
	if (m_resultPending)
	{
		DWORD flags = 0;
		BOOL result = WSAGetOverlappedResult(m_s, &m_overlapped, &m_lastResult, false, &flags);
		m_s.CheckAndHandleError("WSAGetOverlappedResult", result);
		m_resultPending = false;
	}
	return m_lastResult;
}