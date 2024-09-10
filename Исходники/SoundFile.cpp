bool CSoundFile::OpenWaveFile()
{
	// code taken from Visual C++ Multimedia -- Aitken and Jarol p 122
	
	// check if file is already open
	if(m_hFile) 
		return FALSE; 
	
	m_hFile = mmioOpen(m_szFileName,NULL,MMIO_READ);
	if(m_hFile == NULL) 
	{
		m_Mode = FILE_ERROR;
		return FALSE;
	}

	m_MMCKInfoParent.fccType = mmioFOURCC('W','A','V','E');
	MMRESULT mmResult = ::mmioDescend(m_hFile, &m_MMCKInfoParent,NULL,MMIO_FINDRIFF);
	if(mmResult)
	{
		//CString tstr;
		//tstr.LoadString(IDS_STRING_ERRDESCENT);		
		//AfxMessageBox(tstr);
		
		AfxMessageBox("Error descending into file");
		mmioClose(m_hFile,0);
		m_hFile = NULL;
		m_Mode = FILE_ERROR;
		return FALSE;
	}
	m_MMCKInfoChild.ckid = mmioFOURCC('f','m','t',' ');
	mmResult = mmioDescend(m_hFile,&m_MMCKInfoChild,&m_MMCKInfoParent,MMIO_FINDCHUNK);
	if(mmResult)
	{
		AfxMessageBox("Error descending in wave file");
		mmioClose(m_hFile,0);
		m_Mode = FILE_ERROR;
		m_hFile = NULL;
		return FALSE;
	}
	DWORD bytesRead = mmioRead(m_hFile,(LPSTR)&m_Format,m_MMCKInfoChild.cksize);
	if(bytesRead < 0)
	{
		AfxMessageBox("Error reading PCM wave format record");
		mmioClose(m_hFile,0);
		m_Mode = FILE_ERROR;
		return FALSE;
	}
	
	// open output sound file
	mmResult = mmioAscend(m_hFile,&m_MMCKInfoChild,0);
	if(mmResult)
	{
		AfxMessageBox("Error ascending in File");
		mmioClose(m_hFile,0);
		m_hFile = NULL;
		m_Mode = FILE_ERROR;
		return FALSE;
	}
	m_MMCKInfoChild.ckid = mmioFOURCC('d','a','t','a');
	mmResult = mmioDescend(m_hFile,&m_MMCKInfoChild,
		&m_MMCKInfoParent,MMIO_FINDCHUNK);
	if(mmResult)
	{
		AfxMessageBox("error reading data chunk");
		mmioClose(m_hFile,0);
		m_hFile = NULL;
		m_Mode = FILE_ERROR;
		return FALSE;
	}

	return TRUE;
}