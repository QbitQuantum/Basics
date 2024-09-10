int CLDEditTxtFile::WriteItemsToFile(CString strFile, CSimpleArray<CString> arrItems)
{
	int nRet = -1;
	USES_CONVERSION;

	CBkProcPrivilege privilege;

	if (!privilege.EnableShutdown())
		return -1;

	char pszFilePath[MAX_PATH] = {0};
	CString strDesFile = strFile;
	StringCbPrintfA(pszFilePath, sizeof(pszFilePath), "%s_tmp", W2A(strFile));
	
	DWORD dwFileAttr = ::GetFileAttributes(strFile);
//	dwFileAttr &= ~FILE_ATTRIBUTE_READONLY;
	::SetFileAttributes(strFile, FILE_ATTRIBUTE_NORMAL);
	FILE* pFile = NULL;
	//open file
	fopen_s(&pFile, const_cast<char*>(pszFilePath), "w+b");
	if (NULL == pFile)
	{
		::SetFileAttributes(strFile, dwFileAttr);
		return nRet;
	}
	//write file
	int nCount = arrItems.GetSize();
	for (int i = 0; i < nCount; i++)
	{
		if (NULL != m_pStop && TRUE == *m_pStop)
			break;

		CString strValue = arrItems[i];
		if (TRUE == strValue.IsEmpty())
			continue;
		fputs(CW2A(strValue.GetBuffer(-1)), pFile);
		if (strValue.Right(1) != "\n")
			fputs("\r\n", pFile);
		strValue.ReleaseBuffer(-1);
	}
	if (NULL != pFile)
		fclose(pFile);
	pFile = NULL;

	MoveFileEx(CString(pszFilePath), strDesFile, MOVEFILE_REPLACE_EXISTING);
	::SetFileAttributes(strDesFile, dwFileAttr);
	nRet = 0;

	return nRet;
}