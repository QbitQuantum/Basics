void CXMemMapFile::UnMap()
{
	//Close any views which may be open
	Close();

	//unmap the view
	if (m_lpData != NULL)
	{
		FlushViewOfFile(m_lpData, 0);
		UnmapViewOfFile(m_lpData);
		m_lpData = NULL;
	}

	//remove the file mapping
	if (m_hMapping != NULL)
	{
		CloseHandle(m_hMapping);
		m_hMapping = NULL;
	}

	//close the file system file if its open
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}

	//Close the mutex we have been using
#if 0  // -----------------------------------------------------------
	if (m_hMutex != NULL)
	{
		CloseHandle(m_hMutex);
		m_hMutex = NULL;
	}
#endif // -----------------------------------------------------------

	//Reset the remaining member variables
	m_bReadOnly = TRUE;
	m_szMappingName[0] = _T('\0');
	m_dwLength = 0;
}