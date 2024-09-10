void CFolderInfo::CalculateSize()
{
	std::list<CRawString> folderQueue;
	folderQueue.push_back(m_Path.c_str());

	WCHAR searchPattern[MAX_PATH + 10];
	WCHAR buffer[MAX_PATH];
	char utf8Buf[MAX_PATH * 3];
	WIN32_FIND_DATA findData;
	HANDLE findHandle;
	while (!folderQueue.empty())
	{
		const CRawString& ref = folderQueue.front();
		wsprintf(searchPattern, L"%s%s", ref.c_str(), L"\\*.*");

		findHandle = FindFirstFile(searchPattern, &findData);
		if (INVALID_HANDLE_VALUE == findHandle)
		{
			folderQueue.pop_front();
			continue;
		}

		do
		{
			// special case for "." and ".."
			if (wcscmp(findData.cFileName, L".") == 0 ||
				wcscmp(findData.cFileName, L"..") == 0)
			{
				continue;
			}

			bool isFolder = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0;

			if (!m_IncludeHiddenFiles && (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
			{
				continue;
			}
			else if (!m_IncludeSystemFiles && (findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
			{
				continue;
			}
			else if (!isFolder && m_RegExpFilter)
			{
				int utf8BufLen = WideCharToMultiByte(CP_UTF8, 0, findData.cFileName, wcslen(findData.cFileName) + 1, utf8Buf, MAX_PATH * 3, NULL, NULL);
				if (0 != pcre_exec(m_RegExpFilter, NULL, utf8Buf, utf8BufLen, 0, 0, NULL, 0))
				{
					continue;
				}
			}

			if (isFolder)
			{
				m_FolderCount++;
				if (m_IncludeSubFolders)
				{
					wsprintf(buffer, L"%s\\%s", ref.c_str(), findData.cFileName);
					folderQueue.push_back(buffer);
				}
			}
			else
			{
				m_FileCount++;
				m_Size += ((UINT64)findData.nFileSizeHigh << 32) + findData.nFileSizeLow;
			}
		}
		while (FindNextFile(findHandle, &findData));
		FindClose(findHandle);

		folderQueue.pop_front();
	}
}