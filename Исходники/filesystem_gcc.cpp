	bool CFileSystem::removeDirectory(const char* szDirectoryPath)
	{
		return remove(szDirectoryPath) == 0;
	}