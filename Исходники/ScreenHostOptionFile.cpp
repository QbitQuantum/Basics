void CScreenHostOptionFile::New(const wchar_t* pwsName )
{
	if( !LTFileOperations::DirectoryExists( GameModeMgr::Instance( ).GetOptionsFolder( )))
	{
		if( !LTFileOperations::CreateNewDirectory( GameModeMgr::Instance( ).GetOptionsFolder( )))
		{
			//TODO: error message
			return;
		}
	}

	// check if this name exists in the map file
	if( CHostOptionsMapMgr::Instance().IsFriendlyNameMapped(pwsName) )
	{
		MBCreate mb;
		mb.eType = LTMB_OK;
		g_pInterfaceMgr->ShowMessageBox("IDS_OPTIONFILE_EXISTS",&mb);
		return;
	}

	// create a new file name that is in ANSI
	char szFileTitle[64];
	char szPath[MAX_PATH*2];
	for(uint32 nFile=0;;++nFile)
	{
		LTSNPrintF( szFileTitle, LTARRAYSIZE(szFileTitle), "ServerOptions%.4d", nFile );
		GameModeMgr::Instance( ).GetOptionsFilePath( szFileTitle, szPath, LTARRAYSIZE( szPath ));
		if( !LTFileOperations::FileExists(szPath) && 
			!CHostOptionsMapMgr::Instance().IsFileNameMapped(szPath) )
			break;
	}

	// add this combination
	CHostOptionsMapMgr::Instance().Add( szFileTitle, pwsName );

	g_pProfileMgr->GetCurrentProfile()->m_sServerOptionsFile = szFileTitle;

	CreateFileList();
	Escape( );
}