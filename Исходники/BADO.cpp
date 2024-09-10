BOOL CBADO::OnInitADOConn()
{
	CString StrTips;
	HANDLE hFind;//
	WIN32_FIND_DATA wfd;//
	hFind = FindFirstFile(m_dbfilepath, &wfd);//
	if (hFind == INVALID_HANDLE_VALUE)//说明当前目录下无t3000.mdb
	{
		// 	StrTips.Format(_T("%s\n The datebase file disappeared.T3000 help you create a default datebase of your current building."),m_dbfilepath);
		// 	AfxMessageBox(StrTips);
		CStringArray ArrayFileName;
		SplitCStringA(ArrayFileName, m_dbfilepath, L"\\");
		CString filename = L"";
		for (int i = 0; i < ArrayFileName.GetSize() - 1; i++)
		{
			filename += ArrayFileName[i];
			filename += L"\\";
		}
		CreateDirectory(filename,NULL);
		m_dbImgeFolder = filename + _T("image");
		CreateDirectory(m_dbImgeFolder,NULL);

		hFind = FindFirstFile(m_dbfilepath, &wfd);//
		if (hFind == INVALID_HANDLE_VALUE)//说明当前目录下没有building数据库的话，就创建一个
		{
#if 0
		HRSRC hrSrc = FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_BUILDING_DB2), _T("BUILDING_DB"));   
		HGLOBAL hGlobal = LoadResource(AfxGetResourceHandle(), hrSrc);   


		LPVOID lpExe = LockResource(hGlobal);   
		CFile file;
		if(file.Open(m_dbfilepath, CFile::modeCreate | CFile::modeWrite))    
			file.Write(lpExe, (UINT)SizeofResource(AfxGetResourceHandle(), hrSrc));    
		file.Close();    
		::UnlockResource(hGlobal);   
		::FreeResource(hGlobal);
#endif
		}//
		FindClose(hFind);

		//return FALSE;
	}
	::CoInitialize(NULL);
	try
	{
		////////////////////////////////////////////////////////////////////////////////////////////


		m_ConnectString = (CString)FOR_DATABASE_CONNECT + m_dbfilepath;

		// 		CStringArray  ArrayFileName;
		// 		SplitCStringA(ArrayFileName,m_dbfilepath,L"\\");
		// 		CString filename=L"";
		// 		for (int i=0;i<ArrayFileName.GetSize()-1;i++)
		// 		{
		// 			filename+=ArrayFileName[i];
		// 			filename+=L"\\";
		// 		}
		// 		m_dbImgeFolder=filename+_T("image");
		// 		CreateDirectory(m_dbImgeFolder,NULL);

		/////////////////////////////////////////////////////////////////////////////////////////////////
		//连接数据库


		m_pConnection.CreateInstance("ADODB.Connection");

		m_pConnection->Open(m_ConnectString.GetString(), "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		//AfxMessageBox(e.Description());
		return FALSE;
	}

	return TRUE;
}