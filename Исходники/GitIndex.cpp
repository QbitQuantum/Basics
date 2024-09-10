int CGitHeadFileList::ReadHeadHash(CString gitdir)
{
	CAutoWriteLock lock(m_SharedMutex);
	m_Gitdir = g_AdminDirMap.GetAdminDir(gitdir);

	m_HeadFile = m_Gitdir;
	m_HeadFile += _T("HEAD");

	if( g_Git.GetFileModifyTime(m_HeadFile, &m_LastModifyTimeHead))
		return -1;

	CAutoFile hfile = CreateFile(m_HeadFile,
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (!hfile)
		return -1;

	DWORD size = 0;
	unsigned char buffer[40];
	ReadFile(hfile, buffer, 4, &size, nullptr);
	if (size != 4)
		return -1;
	buffer[4] = 0;
	if (strcmp((const char*)buffer, "ref:") == 0)
	{
		m_HeadRefFile.Empty();
		DWORD filesize = GetFileSize(hfile, nullptr);
		if (filesize < 5)
			return -1;

		unsigned char *p = (unsigned char*)malloc(filesize - 4);
		if (!p)
			return -1;

		ReadFile(hfile, p, filesize - 4, &size, nullptr);
		CGit::StringAppend(&m_HeadRefFile, p, CP_UTF8, filesize - 4);
		free(p);

		CString ref = m_HeadRefFile.Trim();
		int start = 0;
		ref = ref.Tokenize(_T("\n"), start);
		m_HeadRefFile = m_Gitdir + m_HeadRefFile;
		m_HeadRefFile.Replace(_T('/'), _T('\\'));

		__int64 time;
		if (g_Git.GetFileModifyTime(m_HeadRefFile, &time, nullptr))
		{
			m_HeadRefFile.Empty();
			if (GetPackRef(gitdir))
				return -1;
			if (m_PackRefMap.find(ref) == m_PackRefMap.end())
				return -1;

			m_Head = m_PackRefMap[ref];
			return 0;
		}

		CAutoFile href = CreateFile(m_HeadRefFile,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE,
			nullptr,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			nullptr);

		if (!href)
		{
			m_HeadRefFile.Empty();

			if (GetPackRef(gitdir))
				return -1;

			if (m_PackRefMap.find(ref) == m_PackRefMap.end())
				return -1;

			m_Head = m_PackRefMap[ref];
			return 0;
		}

		ReadFile(href, buffer, 40, &size, nullptr);
		if (size != 40)
			return -1;

		m_Head.ConvertFromStrA((char*)buffer);

		m_LastModifyTimeRef = time;
	}
	else
	{
		ReadFile(hfile, buffer + 4, 40 - 4, &size, NULL);
		if (size != 36)
			return -1;

		m_HeadRefFile.Empty();

		m_Head.ConvertFromStrA((char*)buffer);
	}

	return 0;
}