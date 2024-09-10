//------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------
bool CStringManager::LoadTypeTable( LANGUAGE_TYPE languageType, const char* pszFileName , int iStringType )
{
	int		i = 0;	

	// PY: modified code
	CFileSystem* pFileSystem;

	
	pFileSystem = (CVFSManager::GetSingleton()).GetNormalFileSystem(); //PY: forcing normal type file for only NPCs
	ClientLog(LOG_DEBUG,"CStringManager Loading normal file type for %s",pszFileName );

	//CFileSystem* pFileSystem = (CVFSManager::GetSingleton()).GetFileSystem();  //original code
	if( pFileSystem->OpenFile( pszFileName ) == false )	//PY: Try opening normal file first
	{			
		//assert( 0 && "File Not Found" );
		ClientLog(LOG_DEBUG,"%s could not be found. Loading from VFS instead",pszFileName );
		pFileSystem->CloseFile();
		pFileSystem = (CVFSManager::GetSingleton()).GetVFSFileSystem(); //Try opening the VFS version instead
		if( pFileSystem->OpenFile( pszFileName ) == false )	//kick out if it still fails
		{
			ClientLog(LOG_DEBUG,"%s could not be found in VFS either",pszFileName );
			return false;
		}
	}


	//--------------------------------------------------------
	// Get Table Type
	//--------------------------------------------------------
	int	 iTableType = 0;
	char strStlType[32];
	pFileSystem->ReadPascalString( strStlType, sizeof( strStlType ) );
	
	if( _strcmpi( strStlType, "ITST01" ) == 0 )
	{
		iTableType = ITEM_TYPE_ST;
	}else if( _strcmpi( strStlType, "NRST01" ) == 0 )
	{
		iTableType = NORMAL_TYPE_ST;
	}else if( _strcmpi( strStlType, "QEST01" ) == 0 )
	{
		iTableType = QUEST_TYPE_ST;
	}else
	{
		pFileSystem->CloseFile();
		(CVFSManager::GetSingleton()).ReturnToManager( pFileSystem );
		return false;
	}




	//--------------------------------------------------------
	// Read key data
	//--------------------------------------------------------
	int iKeyCount = 0;
	int iIndex = 0;
	pFileSystem->ReadInt32( &iKeyCount );


	/// µÚ¿¡¼­ Å° ½ÅÄö½º ÀÎµ¦½º¿¡ ´ëÀÀÇÏ´Â ¾ÆÀÌÅÛÅ¸ÀÔ°´Ã¼
	 stTypeTable** pTempTypeList = NULL;
	 try
	 {
		pTempTypeList = new stTypeTable*[ iKeyCount ];
	 }catch( ... )
	 {
		 MessageBox( NULL, "Not enough memory", "ERROR", MB_OK );

		 pFileSystem->CloseFile();
		(CVFSManager::GetSingleton()).ReturnToManager( pFileSystem );

		return false;
	 }
	 
	 LogString( LOG_NORMAL, "KeyCount [ %d ]\n", iKeyCount );

	/*switch( iTableType )
	{
		case ITEM_TYPE_ST: 
			m_ItemTypeTables[ iStringType ].reserve( iKeyCount );
			break;
		case NORMAL_TYPE_ST: 
			m_NormalTypeTables[ iStringType ].reserve( iKeyCount );
			break;
	}*/

	


	for( i = 0; i < iKeyCount ; i++ )
	{
		int iStrLen = pFileSystem->ReadPascalString( m_TempBuf, sizeof( m_TempBuf ) );
		(CLocalizing::GetSingleton()).UTF8ToMBCS( m_TempBuf, sizeof( m_TempBuf ) );
		pFileSystem->ReadInt32( &iIndex );		

		switch( iTableType )
		{
			case ITEM_TYPE_ST:
				{
					stItemTypeTable* itTable = m_ItemTypeTables[ iStringType ].GetObjectInstanceFromPool();
					//stItemTypeTable* itTable = new stItemTypeTable;
					itTable->strKey = m_TempBuf;
					itTable->iIndex = iIndex;
					m_ItemTypeTables[ iStringType ].AddObject( m_TempBuf, itTable );					

					pTempTypeList[ i ] = (stTypeTable*)itTable;
				}
				break;

			case NORMAL_TYPE_ST:
				{
					stNormalTypeTable* itTable = m_NormalTypeTables[ iStringType ].GetObjectInstanceFromPool();
					//stNormalTypeTable* itTable = new stNormalTypeTable;
					itTable->strKey = m_TempBuf;
					itTable->iIndex = iIndex;
					m_NormalTypeTables[ iStringType ].AddObject( m_TempBuf, itTable );					

					pTempTypeList[ i ] = (stTypeTable*)itTable;
				}
				break;
			case QUEST_TYPE_ST:
				{					
					stQuestTypeTable* itTable = m_QuestTypeTables[ iStringType ].GetObjectInstanceFromPool();
					//stQuestTypeTable* itTable = new stQuestTypeTable;
					itTable->strKey = m_TempBuf;
					itTable->iIndex = iIndex;
					m_QuestTypeTables[ iStringType ].AddObject( m_TempBuf, itTable );	

					pTempTypeList[ i ] = (stTypeTable*)itTable;
				}
				break;
		}
	}



	//--------------------------------------------------------
	// Language set offset
	//--------------------------------------------------------
	int iLanguageSetCnt = 0;
	pFileSystem->ReadInt32( &iLanguageSetCnt );	
	pFileSystem->Seek( languageType * sizeof( int ), FILE_POS_CUR );

	int iTargetLangPos = 0;
	pFileSystem->ReadInt32( &iTargetLangPos ); 

	/// ÇØ´ç ¾ð´õ ºí¶ôÀ¸·Î ÀÌµ¿..
	pFileSystem->Seek( iTargetLangPos, FILE_POS_SET );	


	//--------------------------------------------------------
	// Language set data
	//--------------------------------------------------------
	/// ½ºÆ®¸µÀ» ºí¶ôÀ¸·Î ÀÐ¾úÀ»¶§ ÂüÁ¶ÇÒ ¿É¼Â.
	for( i = 0; i < iKeyCount ; i++ )
	{
		int iDataOffset = 0;
		pFileSystem->ReadInt32( &iDataOffset );		
	}



	/// ½ÇÁ¦ ½ºÆ®¸µµé..
	for( i = 0; i < iKeyCount ; i++ )
	{		
		switch( iTableType )
		{
			case ITEM_TYPE_ST:
				{
					pFileSystem->ReadPascalString( m_TempBuf, sizeof( m_TempBuf ) );
					(CLocalizing::GetSingleton()).UTF8ToMBCS( m_TempBuf, sizeof( m_TempBuf ) );
					
					///stItemTypeTable* pItemTypeTable = m_ItemTypeTables[ iStringType ].GetObjectByName( m_IndexToKey[ i ].c_str() );
					stItemTypeTable* pItemTypeTable = (stItemTypeTable*)pTempTypeList[ i ];

					if( pItemTypeTable )
						pItemTypeTable->strName = m_TempBuf;

					pFileSystem->ReadPascalString( m_TempBuf, sizeof( m_TempBuf ) );
					(CLocalizing::GetSingleton()).UTF8ToMBCS( m_TempBuf, sizeof( m_TempBuf ) );					

					if( pItemTypeTable )
						pItemTypeTable->strDesc = m_TempBuf;					
				}
				break;

			case NORMAL_TYPE_ST:
				{
					pFileSystem->ReadPascalString( m_TempBuf, sizeof( m_TempBuf ) );
					(CLocalizing::GetSingleton()).UTF8ToMBCS( m_TempBuf, sizeof( m_TempBuf ) );
					///stNormalTypeTable* pNormalTypeTable = m_NormalTypeTables[ iStringType ].GetObjectByName( m_IndexToKey[ i ].c_str() );
					stNormalTypeTable* pNormalTypeTable = (stNormalTypeTable*)pTempTypeList[ i ];

					if( pNormalTypeTable )
						pNormalTypeTable->strString = m_TempBuf;					
				}
				break;
			case QUEST_TYPE_ST:
				{
					/// Name
					pFileSystem->ReadPascalString( m_TempBuf, sizeof( m_TempBuf ) );
					(CLocalizing::GetSingleton()).UTF8ToMBCS( m_TempBuf, sizeof( m_TempBuf ) );
					///stQuestTypeTable* pQuestTypeTable = m_QuestTypeTables[ iStringType ].GetObjectByName( m_IndexToKey[ i ].c_str() );
					stQuestTypeTable* pQuestTypeTable = (stQuestTypeTable*)pTempTypeList[ i ];

					if( pQuestTypeTable )
						pQuestTypeTable->strName = m_TempBuf;					

					/// Desc
					pFileSystem->ReadPascalString( m_TempBuf, sizeof( m_TempBuf ) );
					(CLocalizing::GetSingleton()).UTF8ToMBCS( m_TempBuf, sizeof( m_TempBuf ) );

					if( pQuestTypeTable )
						pQuestTypeTable->strDesc = m_TempBuf;
					
					/// Start msg
					pFileSystem->ReadPascalString( m_TempBuf, sizeof( m_TempBuf ) );
					(CLocalizing::GetSingleton()).UTF8ToMBCS( m_TempBuf, sizeof( m_TempBuf ) );

					if( pQuestTypeTable )
						pQuestTypeTable->strStartMsg = m_TempBuf;
					
					/// End msg
					pFileSystem->ReadPascalString( m_TempBuf, sizeof( m_TempBuf ) );
					(CLocalizing::GetSingleton()).UTF8ToMBCS( m_TempBuf, sizeof( m_TempBuf ) );

					if( pQuestTypeTable )
						pQuestTypeTable->strEndMsg = m_TempBuf;					
				}
				break;
		}		
	}
	
	delete[] pTempTypeList;
	
	pFileSystem->CloseFile();
	(CVFSManager::GetSingleton()).ReturnToManager( pFileSystem );
    
	return true;
}