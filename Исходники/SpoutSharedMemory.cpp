bool SpoutSharedMemory::Open(const char* name)
{
	// Don't call open twice on the same object without a Close()
	assert(name);

	if (m_hMap)
	{
		assert(strcmp(name, m_pName) == 0);
		assert(m_pBuffer && m_hMutex);
		return true;
	}

	m_hMap = OpenFileMappingA ( FILE_MAP_ALL_ACCESS,
									FALSE,
									(LPCSTR)name);

	if (m_hMap == NULL)
	{
		return false;
	}


	DWORD err = GetLastError();

	if (err == ERROR_ALREADY_EXISTS)
	{
		// We should ensure the already existing mapping is at least
		// the size we expect
	}

	m_pBuffer = (char*)MapViewOfFile(m_hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);


	if (!m_pBuffer)
	{
		Close();
		return false;
	}

	std::string	mutexName;
	mutexName = name;
	mutexName += "_mutex";

	m_hMutex = CreateMutexA(NULL, FALSE, mutexName.c_str());

	if (!m_hMutex)
	{
		Close();
		return false;
	}

	// m_pName = strdup(name);
	m_pName = _strdup(name);
	m_size = 0;

	return true;

}