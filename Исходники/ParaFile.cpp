bool ParaEngine::CParaFile::GetFileInfo(const char* sfilename, CParaFileInfo& fileInfo, uint32 dwWhereToOpen /*= FILE_ON_DISK | FILE_ON_ZIP_ARCHIVE | FILE_ON_SEARCH_PATH*/)
{
	int32 dwFoundPlace = FILE_NOT_FOUND;
	if (!GetDevDirectory().empty() && dwWhereToOpen != FILE_ON_ZIP_ARCHIVE && ((dwWhereToOpen & FILE_ON_ZIP_ARCHIVE) > 0))
	{
		// in development version, find in current directory and search path and then zip archive
		dwWhereToOpen &= (~((uint32)FILE_ON_ZIP_ARCHIVE));
		return GetFileInfo(sfilename, fileInfo, dwWhereToOpen) ||
			GetFileInfo(fileInfo.m_sFullpath.empty() ? sfilename : fileInfo.m_sFullpath.c_str(), fileInfo, FILE_ON_ZIP_ARCHIVE);
	}

	if ((dwWhereToOpen & FILE_ON_SEARCH_PATH) > 0)
	{
		dwWhereToOpen &= (~((uint32)FILE_ON_SEARCH_PATH));

		std::list<SearchPath>& searchPaths = CFileManager::GetInstance()->GetSearchPaths();

		if (searchPaths.size() == 0 || (sfilename[0] == '/') || (sfilename[0] == '\\'))
		{
			if (dwWhereToOpen != 0)
				return GetFileInfo(sfilename, fileInfo, dwWhereToOpen);
			return false;
		}
		else
		{
			// find in current directory and zip file, and then in search path
			bool bFound = (dwWhereToOpen != 0) && GetFileInfo(sfilename, fileInfo, dwWhereToOpen);
			if (!bFound)
			{
				if (!fileInfo.m_sFullpath.empty())
					sfilename = fileInfo.m_sFullpath.c_str();
				list<SearchPath>::iterator itCurCP, itEndCP = searchPaths.end();
				for (itCurCP = searchPaths.begin(); !bFound && itCurCP != itEndCP; ++itCurCP)
				{
					auto fullpath = (*itCurCP).GetPath() + sfilename;
					bFound = GetFileInfo(fullpath.c_str(), fileInfo, FILE_ON_DISK);
				}
			}
			return bFound;
		}
	}
	char filename[MAX_PATH];

	int i = 0;
	int j = 0;
#ifdef WIN32
	// remove the heading slash
	if ((sfilename[0] == '/') || (sfilename[0] == '\\'))
		i++;
#endif

	// replace '\\' with '/'
	for (; sfilename[i] != '\0' && j < (MAX_PATH - 1); i++, j++)
	{
		if (sfilename[i] == '\\')
			filename[j] = '/';
		else
			filename[j] = sfilename[i];
	}
	filename[j] = '\0';

	if (fileInfo.m_sFullpath.empty())
		fileInfo.m_sFullpath = filename;

	if (CFileReplaceMap::GetSingleton().ReplaceFile(fileInfo.m_sFullpath))
	{
		strcpy(filename, fileInfo.m_sFullpath.c_str());
	}

	if ((dwWhereToOpen & FILE_ON_DISK)>0 && GetDiskFilePriority() >= 0)
	{
		if (CFileUtils::GetFileInfo(filename, fileInfo))
			return true;
	}

	if ((dwWhereToOpen & FILE_ON_ZIP_ARCHIVE) > 0)
	{
		CFileManager* pFileManager = CFileManager::GetInstance();
		/// load from Zip files, if the file does not exist on disk
		FileHandle fileHandle;
		if (pFileManager->OpenFile(filename, fileHandle))
		{
			fileInfo.m_mode = CParaFileInfo::ModeFileInZip;
			fileInfo.m_dwFileSize = pFileManager->GetFileSize(fileHandle);
			if (fileHandle.m_pArchive){
				fileInfo.m_sFullpath = std::string("zip://") + fileHandle.m_pArchive->GetArchiveName() + "/" + filename;
			}
			pFileManager->CloseFile(fileHandle);
			return true;
		}
	}

	if (GetDiskFilePriority() < 0 && (dwWhereToOpen & FILE_ON_DISK) > 0)
	{
		if (CFileUtils::GetFileInfo(filename, fileInfo))
			return true;
	}
	return false;
}