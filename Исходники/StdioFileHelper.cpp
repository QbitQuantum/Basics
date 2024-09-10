void StdioFileHelper::SetLockedFilePointer()
{
	CleanUp();

	HANDLE hFile = ::CreateFile(m_fileName.c_str(), GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, 
		OPEN_EXISTING, 0, 0);
	if(INVALID_HANDLE_VALUE == hFile)
	{
		char buffer[255];
		::sprintf_s(buffer, 255, "Failed to open [%s]", m_fileName);
		throw std::exception(buffer);
	}

	int fileNumber = _open_osfhandle((intptr_t)hFile, 1);
	if(-1 == fileNumber)
		throw std::exception("We failed to convert the File HANDLE to a C-Runtime descriptor.");

	FILE* pFile = _wfdopen(fileNumber, _T("rb"));
	if(0 == pFile)
		throw std::exception("We failed to associate the stream with the converted file descriptor.");

	m_pFile = pFile ;
}