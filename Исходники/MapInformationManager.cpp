//-----------------------------------------------------------------------------
BOOL CMapInformationManager::LoadPropMapComboBoxData( void )
{
	CScript script;
	if( script.Load( _T( "propMapComboBoxData.inc" ) ) == FALSE )
	{
		return FALSE;
	}

	DWORD dwMapComboBoxDataID = script.GetNumber(); // ID;
	while( script.tok != FINISHED )
	{
		script.GetToken(); // {
		CMapComboBoxData::Category eMapComboBoxCategory = static_cast< CMapComboBoxData::Category >( MCC_MAP_CATEGORY );
		CString strMapComboBoxTitle = _T( "" );
		CString strMapPictureFileName = _T( "" );
		CRect rectRealPosition( 0, 0, 0, 0 );
		CPoint pointNPCPosition( -1, -1 );
		CString strMapMonsterInformationFileName = _T( "" );
		BYTE byLocationID = CONT_NODATA;
		DWORD dwMapComboBoxDataParentID = MCD_NONE;
		int nBlock = 1;
		while( nBlock > 0 && script.tok != FINISHED )
		{
			script.GetToken();
			if( script.Token == _T( "{" ) )
			{
				++nBlock;
			}
			else if( script.Token == _T( "}" ) )
			{
				--nBlock;
			}
			else if( script.Token == _T( "SetCategory" ) )
			{
				script.GetToken(); // (
				eMapComboBoxCategory = static_cast< CMapComboBoxData::Category >( script.GetNumber() );
				script.GetToken(); // )
				script.GetToken(); // ;
			}
			else if( script.Token == _T( "SetTitle" ) )
			{
				script.GetToken(); // (
				strMapComboBoxTitle = prj.GetLangScript( script );
			}
			else if( script.Token == _T( "SetPictureFile" ) )
			{
				script.GetToken(); // (
				strMapPictureFileName = prj.GetLangScript( script );
			}
			else if( script.Token == _T( "SetRealPositionRect" ) )
			{
				script.GetToken(); // (
				rectRealPosition.left = script.GetNumber();
				script.GetToken(); // ,
				rectRealPosition.top = script.GetNumber();
				script.GetToken(); // ,
				rectRealPosition.right = script.GetNumber();
				script.GetToken(); // ,
				rectRealPosition.bottom = script.GetNumber();
				script.GetToken(); // )
				script.GetToken(); // ;
			}
			else if( script.Token == _T( "SetMonsterInformationFile" ) )
			{
				script.GetToken(); // (
				strMapMonsterInformationFileName = prj.GetLangScript( script );
			}
			else if( script.Token == _T( "SetLocationID" ) )
			{
				script.GetToken(); // (
				byLocationID = static_cast< BYTE >( script.GetNumber() );
				script.GetToken(); // )
				script.GetToken(); // ;
			}
			else if( script.Token == _T( "SetNPCPosition" ) )
			{
				script.GetToken(); // (
				pointNPCPosition.x = script.GetNumber();
				script.GetToken(); // ,
				pointNPCPosition.y = script.GetNumber();
				script.GetToken(); // )
				script.GetToken(); // ;
			}
			else if( script.Token == _T( "SetParentID" ) )
			{
				script.GetToken(); // (
				dwMapComboBoxDataParentID = script.GetNumber();
				script.GetToken(); // )
				script.GetToken(); // ;
			}
		}

		CMapComboBoxData* pMapComboBoxData = new CMapComboBoxData( dwMapComboBoxDataID, eMapComboBoxCategory, strMapComboBoxTitle );
		pMapComboBoxData->SetPictureFileName( strMapPictureFileName );
		/*if( strMapPictureFileName != _T( "" ) )
		{
			CTexture* pMapTexture = CWndBase::m_textureMng.AddTexture( g_Neuz.m_pd3dDevice, MakePath( _T( "Theme\\" ), ::GetLanguage(), strMapPictureFileName ), 0xffffffff );
			pMapComboBoxData->SetMapTexture( pMapTexture );
		}*/
		if( eMapComboBoxCategory == MCC_MAP_NAME )
		{
			CRect* pRealPositionRect = new CRect( rectRealPosition );
			m_RealPositionRectMap[ byLocationID ] = pRealPositionRect;
		}
		pMapComboBoxData->SetMapMonsterInformationFileName( strMapMonsterInformationFileName );
		pMapComboBoxData->SetLocationID( byLocationID );
		pMapComboBoxData->SetNPCPosition( pointNPCPosition );
		pMapComboBoxData->SetParentID( dwMapComboBoxDataParentID );

		switch( eMapComboBoxCategory )
		{
		case MCC_MAP_CATEGORY:
			{
				m_MapCategoryVector.push_back( pMapComboBoxData );
				break;
			}
		case MCC_MAP_NAME:
			{
				m_MapNameVector.push_back( pMapComboBoxData );
				break;
			}
		case MCC_NPC_NAME:
			{
				m_NPCNameVector.push_back( pMapComboBoxData );
				break;
			}
		}
		dwMapComboBoxDataID = script.GetNumber(); // ID
	}
	return TRUE;
}