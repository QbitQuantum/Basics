BOOL CDownloadGroups::Load()
{
	CString strFile = Settings.General.UserPath + _T("\\Data\\DownloadGroups.dat");

	CFile pFile;
	if ( pFile.Open( strFile, CFile::modeRead | CFile::shareDenyWrite | CFile::osSequentialScan ) )
	{
		try
		{
			CArchive ar( &pFile, CArchive::load );	// 4 KB buffer
			try
			{
				CQuickLock pTransfersLock( Transfers.m_pSection );
				CQuickLock pLock( m_pSection );

				Serialize( ar );

				ar.Close();
			}
			catch ( CException* pException )
			{
				ar.Abort();
				pFile.Abort();
				pException->Delete();
				theApp.Message( MSG_ERROR, _T("Failed to load download groups: %s"), strFile );
			}
			pFile.Close();
		}
		catch ( CException* pException )
		{
			pFile.Abort();
			pException->Delete();
			theApp.Message( MSG_ERROR, _T("Failed to load download groups: %s"), strFile );
		}
	}
	else
		theApp.Message( MSG_ERROR, _T("Failed to load download groups: %s"), strFile );

	m_nSaveCookie = m_nBaseCookie;

	return TRUE;
}