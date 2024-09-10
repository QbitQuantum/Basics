BOOL CLogFactory::CreateLogName(BSTR AppName, 
								BSTR Configue, 
								BSTR Section, 
								LONG FileType, 
								CString &strLogName)
{
	CString strError;
	CString strAppPath(AppName);
	CString strFileName(Configue);
	CString strSection(Section);

	if (!IsFileExisted(strAppPath))
	{
		strError.Format(_T("AppName:%s is not existed. CLogFactory::CreateLogName return FALSE."), strAppPath);
		LOGGER_WRITE(strError.GetBuffer());
		LogEvent(strError);
		return FALSE;
	}

	strError.Format(_T("AppName:%s"), strAppPath);
	LOGGER_WRITE(strError.GetBuffer());

	int iIndex = strAppPath.ReverseFind(_T('\\'));
	ATLASSERT(-1 != iIndex);
	strAppPath = strAppPath.Left(iIndex + 1);

	CParameter Parameter;
	CConfigReader Reader;
	Reader.Read(strAppPath, strFileName, strSection, FileType, Parameter);

	CHAR Buffer[MAX_PATH] = { 0 };
#pragma warning(push)
#pragma warning(disable: 4996)
	strcat(Buffer, Parameter.m_cFixFolder);
	strcat(Buffer, Parameter.m_cCycleFolder);
	strcat(Buffer, Parameter.m_cCycleName);
	strcat(Buffer, Parameter.m_cCreateTime);
	strcat(Buffer, Parameter.m_cSaveTime);
	strcat(Buffer, Parameter.m_cExeName);
#pragma warning(pop)
	strLogName = CString(Buffer);
	strLogName.Remove(_T('\\'));
	strLogName.Remove(_T(':'));
	strLogName.Remove(_T('.'));
	strLogName.Remove(_T(' '));

	LOGGER_WRITE2(_T("LogName:") << strLogName.GetBuffer() << _T(" FileType:") << FileType);

	return TRUE;
}