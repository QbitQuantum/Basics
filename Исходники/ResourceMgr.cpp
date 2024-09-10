int CResourceMgr::GetImageNID( int iModuleID, const char* szSID )
{
	TABLE_MODULE_ITER	iterModule;
	TABLE_IMAGE_ID_ITER iterImageID;

	iterModule = m_ResourceTable.find( iModuleID );
	if( iterModule == m_ResourceTable.end() )
		return -1;

//	char* pszSID = NULL;
	char szBuff[256] = {0};
	
	int iSize = (int)strlen( szSID );

	memcpy( szBuff, szSID, iSize);

	_strupr( szBuff );

	iterImageID = iterModule->second.find( szBuff );
	if( iterImageID == iterModule->second.end() )
	{
#ifdef _DEBUG		
		if( strlen( szSID ) )
		{
			printf(szBuff, "Module:%d에서 %s를 찾을수 없습니다.", iModuleID, szSID );
			MessageBox( NULL, szBuff, "Error", MB_OK );
		}		
#endif		
		return -1;
	}
	
	return iterImageID->second;
}