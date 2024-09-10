//-----------------------------------------------------------------------------
int ComPortThread::ReadCOMMBytes(void *pData, int length) 
{

	// Variables
	COMSTAT		ComStat;
	DWORD		dwLength;
	DWORD		dwErrorFlags;

	// Try to read length bytes
	ClearCommError(m_hComDev, &dwErrorFlags, &ComStat);
	ReadFile(m_hComDev, pData, ((DWORD) length), &dwLength, NULL);

	return dwLength;
} // end of ReadCOMMBytes