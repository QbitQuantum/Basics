uint32_t CMappedMemory::_SetSize(uint32_t Size)
{
	if (m_Base)
	{
		myFlushViewOfFile(m_Base, 0);
		myUnmapViewOfFile(m_Base);
	}
	if (m_FileMapping)
		CloseHandle(m_FileMapping);

	m_Base = NULL;
	m_FileMapping = NULL;

	if (INVALID_SET_FILE_POINTER == SetFilePointer(m_DirectFile, Size, NULL, FILE_BEGIN))
	{
		LOGSYS(logERROR, _T("SetFilePointer failed"));
		return 0;
	}

	if (!SetEndOfFile(m_DirectFile))
	{
		LOGSYS(logERROR, _T("Cannot set end of file"));
		return 0;
	}

	m_FileMapping = myCreateFileMappingA(m_DirectFile, NULL, PAGE_READWRITE, 0, Size, NULL);

	if (!m_FileMapping)
	{
		LOGSYS(logERROR, _T("CreateFileMapping failed"));
		return 0;
	}

	m_Base = (uint8_t*) myMapViewOfFile(m_FileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (!m_Base)
	{
		LOGSYS(logERROR, _T("MapViewOfFile failed"));
		return 0;
	}

	return Size;
}