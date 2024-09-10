__inline
void CFileBase::AdjustFileName(const SYSTEMTIME &Time,
							   BOOL bAllFile /*= TRUE*/)
{
	if (-1 != m_iBkCount)
	{
		ATLASSERT(m_strFileName.GetLength() != 0);
		CString strValue;
		strValue.Format(_T("%ld_"), m_iBkCount++);
		CString strFileName = m_strFileName;
		int Index = strFileName.ReverseFind(_T('\\'));
		strFileName.Insert(Index + 1, strValue);
		_wrename(m_strFileName, strFileName);
		return;
	}

	static CFileSearcher Searcher;
	CAtlArray<BACKUPFILE> arrFileNames;
	Searcher.Search(this, Time, arrFileNames);
	CString strNewName, strValue, strPath;
	m_iBkCount = (LONG)arrFileNames.GetCount();

	for (long i = 0; i < m_iBkCount; i++)
	{
		strValue = arrFileNames[i].strFileName;
		int iIndex = strValue.Find(_T('_'));
		if (-1 != iIndex)
			strValue.Delete(0, iIndex + 1);
		else if (!bAllFile)
			continue;

		strPath = arrFileNames[i].strFolder;
		strNewName.Format(_T("%d_%s"), i, strValue);
		if (strNewName != arrFileNames[i].strFileName)
			_wrename(strPath + arrFileNames[i].strFileName, 
			strPath + strNewName);
	}
}