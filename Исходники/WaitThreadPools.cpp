void CWaitThreadPools::CloseWaitThread()
{
	if (NULL==m_pWait) return;

	WaitForThreadpoolWaitCallbacks(m_pWait, TRUE);

	CloseThreadpoolWait(m_pWait);

	m_pWait = NULL;
}