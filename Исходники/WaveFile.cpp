BOOL CWaveFile::StartRecord(LPCTSTR lpszFilePath, WAVEFORMATEX wfx)
{
	CString strErr;
	MMRESULT mmResult = 0;
	
	if(m_hWaveFileRec)
	{
		return TRUE;
	}

	// Truncate file first
	mmioOpen((LPTSTR)lpszFilePath, NULL, MMIO_DELETE); 

	m_hWaveFileRec = mmioOpen((LPTSTR)lpszFilePath, 
	                          NULL, 
							  MMIO_CREATE | MMIO_WRITE | MMIO_EXCLUSIVE | MMIO_ALLOCBUF);
	if(!m_hWaveFileRec) 
	{
		MyMessageBox(_T("mmioOpen failed"), eERR_ERROR);
		return FALSE;
	}
	
	// Create 'WAVE' chunk
	ZeroMemory(&m_mmckinfoParent, sizeof(MMCKINFO));
	m_mmckinfoParent.fccType = mmioFOURCC('W','A','V','E');
	mmResult = mmioCreateChunk(m_hWaveFileRec, &m_mmckinfoParent, MMIO_CREATERIFF);
	if(mmResult)
	{
		MyMessageBox(_T("Create 'WAVE' chunk failed"), eERR_ERROR);
		return FALSE;
	}
	
	// Create 'fmt ' chunk
	ZeroMemory(&m_mmckinfoSubChunk, sizeof(MMCKINFO));
	m_mmckinfoSubChunk.ckid = mmioFOURCC('f','m','t',' ');
	m_mmckinfoSubChunk.cksize = sizeof(WAVEFORMATEX) + wfx.cbSize;
	mmResult = mmioCreateChunk(m_hWaveFileRec, &m_mmckinfoSubChunk, 0);
	if(mmResult)
	{
		MyMessageBox(_T("Create 'fmt' chunk failed"), eERR_ERROR);
		return FALSE;
	}

	// Write format chunk
	long lSize = mmioWrite(m_hWaveFileRec, (char*)&wfx, sizeof(WAVEFORMATEX) + wfx.cbSize); 
	if(lSize <= 0)
	{
		MyMessageBox(_T("Create format chunk failed"), eERR_ERROR);
		return FALSE;
	}
	
	mmResult = mmioAscend(m_hWaveFileRec, &m_mmckinfoSubChunk, 0);
	if(mmResult)
	{
		MyMessageBox(_T("mmioAscend failed"), eERR_ERROR);
		return FALSE;
	}
	
	// Crate 'data' chunk
	m_mmckinfoSubChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmResult = mmioCreateChunk(m_hWaveFileRec, &m_mmckinfoSubChunk, 0);
	if(mmResult)
	{
		MyMessageBox(_T("Create 'data' chunk failed"), eERR_ERROR);
		return FALSE;
	}

	return TRUE;
}