/***********************************************
Close
	Close data file
PARAM:
	none
RETURN:
	-1 if error
************************************************/
int	CUT_MapFileDataSource::Close() {
	int		rt = UTE_SUCCESS;

	m_lnSize = m_lnActualSize;

	// Flush file 
	if(m_lpMapAddress != NULL) 
		if(!FlushViewOfFile(m_lpMapAddress, 0))
			rt = -1;

	// Unmap
	if(m_lpMapAddress != NULL) {
		if(!UnmapViewOfFile(m_lpMapAddress))
			rt = -1;
		m_lpMapAddress = NULL;
		}

	// Close file mapping
	if(m_hMapFile != NULL) {
		if(!CloseHandle(m_hMapFile))
			rt = -1;
		m_hMapFile = NULL;
		}


	// Close file
	if(m_hFile != INVALID_HANDLE_VALUE) {
		// Set Actual file size
		if(SetFilePointer(m_hFile, m_lnActualSize.LowPart, (long *)&m_lnActualSize.HighPart, FILE_BEGIN ) == 0xFFFFFFFF && GetLastError() != NO_ERROR)
			return -1;
		if(!SetEndOfFile(m_hFile))
			return -1;

		// Close file
		if(!CloseHandle(m_hFile))
			rt = -1;
		m_hFile = INVALID_HANDLE_VALUE;
		}	

	return rt;
}