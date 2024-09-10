unsigned int WindowsPipeSender::GetSendResult()
{
	if (m_resultPending)
	{
		const HANDLE h = GetHandle();
#if defined(USE_WINDOWS8_API)
		BOOL result = GetOverlappedResultEx(h, &m_overlapped, &m_lastResult, INFINITE, FALSE);
		CheckAndHandleError("GetOverlappedResultEx", result);
#else
		BOOL result = GetOverlappedResult(h, &m_overlapped, &m_lastResult, FALSE);
		CheckAndHandleError("GetOverlappedResult", result);
#endif
		m_resultPending = false;
	}
	return m_lastResult;
}