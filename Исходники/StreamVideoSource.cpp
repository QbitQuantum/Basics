BOOL CStreamVideoSource::GetRawImage(BYTE **pRawData, FILETIME *timestamp, DWORD *bEOF )
{

	// Lock the image here and don't unlock until we get the frame back
	EnterCriticalSection(&m_csBufLock);
	*bEOF = FALSE;

	if( m_bGotVideoFrame )
	{
		// Get the next frame
		*pRawData = m_pAlignedImg;

		// Need Time stamp
		GetSystemTimeAsFileTime(timestamp);
		FileTimeToLocalFileTime(timestamp, timestamp);

		m_bGotVideoFrame = FALSE;
		return TRUE;
	}
	else
	{
		// Nothing.. unlock
		LeaveCriticalSection(&m_csBufLock);

		// Check for process exit
		if( WAIT_OBJECT_0 == WaitForSingleObject( m_piStreamer.hProcess, 0 ) )
		{
			// Child process has disappeared (exited)
			*bEOF = TRUE;

			m_bRun = FALSE;
			CleanupChild();
		}
		return FALSE;
	}
}