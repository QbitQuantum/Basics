	KeziaResourceManager::KeziaResourceManager(ResourceManagerMode mode)
		:	m_Mode(mode),
			m_PreferredResourceManager(nullptr),
			m_SecondaryResourceManager(nullptr)
	{
		char tmp[255];
		GetCurrentDirectoryA(255, tmp);
		std::string currentDirectory(tmp);

		switch(m_Mode)
		{
		case PreferData:
			m_SecondaryResourceManager = new zlib_ResourceManager();
			m_SecondaryResourceManager->AddSourceDirectory(currentDirectory + "\\Data.zip");
		case DataOnly:
			m_PreferredResourceManager = new Windows_ResourceManager();
			m_PreferredResourceManager->AddSourceDirectory(currentDirectory + "\\Data");
			break;

		case PreferArchive:
			m_SecondaryResourceManager = new Windows_ResourceManager();
			m_SecondaryResourceManager->AddSourceDirectory(currentDirectory + "\\Data");
		case ArchiveOnly:
			m_PreferredResourceManager = new zlib_ResourceManager();
			m_PreferredResourceManager->AddSourceDirectory(currentDirectory + "\\Data.zip");
			break;
		}
	}