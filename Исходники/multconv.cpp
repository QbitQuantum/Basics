BOOL CConverter::Open(LPCTSTR pszFileName, UINT nOpenFlags,
	CFileException* pException)
{
	USES_CONVERSION;
	// we convert to oem and back because of the following case
	// test(c).txt becomes testc.txt in OEM and stays testc.txt to Ansi
	char buf[_MAX_PATH];
	strcpy(buf, T2CA(pszFileName));
	CharToOemA(buf, buf);
	OemToCharA(buf, buf);

	LPTSTR lpszFileNameT = A2T(buf);

	// let's make sure we could do what is wanted directly even though we aren't
	m_bCloseOnDelete = FALSE;
#if _MSC_VER >= 1400
	m_hFile = hFileNull;
#else
	m_hFile = (UINT)hFileNull;
#endif

	BOOL bOpen = CFile::Open(lpszFileNameT, nOpenFlags, pException);
	CFile::Close();
	if (!bOpen)
		return FALSE;

	m_bForeignToRtf = !(nOpenFlags & (CFile::modeReadWrite | CFile::modeWrite));

	// check for reading empty file
	if (m_bForeignToRtf)
	{
		CFileStatus stat;
		if (CFile::GetStatus(lpszFileNameT, stat) && stat.m_size == 0)
			return TRUE;
	}

	//set security attributes to inherit handle
	SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
	//create the events
	m_hEventFile = CreateEvent(&sa, TRUE, FALSE, NULL);
	m_hEventConv = CreateEvent(&sa, TRUE, FALSE, NULL);
	//create the converter thread and create the events

	CharToOemA(buf, buf);
	ASSERT(m_hFileName == NULL);
	m_hFileName = StringToHGLOBAL(buf);

	m_pThis = this;
	m_bDone = FALSE;
	m_hBuff = GlobalAlloc(GHND, BUFFSIZE);
	ASSERT(m_hBuff != NULL);

	AfxBeginThread(ConverterThread, this, THREAD_PRIORITY_NORMAL, 0, 0, &sa);

	return TRUE;
}