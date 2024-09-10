void  CGameUpdate::UpdateAfter()
{
	//当真正更新了文件(索引在更新前己经被删除)，
	//以及版本号不相同（有可能不需要更新(版本号不相同索引也被删除)）时，
	//都需要写索引文件，以及动态还原。
	std::wstring idxfile = m_strCliPath + INDEX_FILE_NAMEW;
	if (!PathFileExistsW(idxfile.c_str()))
	{
		//write local idxfile.
		HANDLE hFile = CreateFileW(idxfile.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			DWORD dwWriteBytes = 0;
			::WriteFile(hFile, m_pIdxfile, m_nIdxfileSize, &dwWriteBytes, NULL);
			SetFileTime(hFile, NULL, NULL, &m_ftIdxfile);
			CloseHandle(hFile);
		}

		//write virtual device idxfile.
		if (_wcsicmp(m_strDevPath.c_str(), m_strCliPath.c_str()) != 0)
		{
			std::wstring devidxfile = m_strDevPath + INDEX_FILE_NAMEW;
			HANDLE hFile = CreateFileW(devidxfile.c_str(), GENERIC_WRITE, 0, NULL, 
				CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile != INVALID_HANDLE_VALUE)
			{
				DWORD dwWriteBytes = 0;
				::WriteFile(hFile, m_pIdxfile, m_nIdxfileSize, &dwWriteBytes, NULL);
				SetFileTime(hFile, NULL, NULL, &m_ftIdxfile);
				CloseHandle(hFile);
			}
		}

		//notify server game update finished.
		m_Server.ReportUpdateFinished(m_dwGid, m_dwSvrIdxVer, m_strCliPath.c_str());

		//hy dynamic execute update directory.
		hy_ExueteUpdateDir(m_strCliPath.c_str());
	}
}