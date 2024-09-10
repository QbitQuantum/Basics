HRESULT AWinRunnable::StartRunning()
{
	if (m_hThread && !m_hThread.IsExit())
	{
		return AtlHresultFromWin32(ERROR_ALREADY_INITIALIZED);
	}

	m_hThread.Close();

	return m_hThread.Create(this);
}