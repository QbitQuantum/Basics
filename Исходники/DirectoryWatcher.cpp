bool CDirectoryWatcher::CDirWatchInfo::CloseDirectoryHandle()
{
	bool b = TRUE;
	if( m_hDir != INVALID_HANDLE_VALUE )
	{
		b = !!CloseHandle(m_hDir);
		m_hDir = INVALID_HANDLE_VALUE;
	}
	if (m_hDevNotify != INVALID_HANDLE_VALUE)
	{
		UnregisterDeviceNotification(m_hDevNotify);
	}
	return b;
}