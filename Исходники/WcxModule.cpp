bool WcxArchive::pExtract( const char *lpDestPath )
{
	int nProcessed = 0;
	int nResult = 0;
	
	m_files.clear();
	while ( nResult == 0 )
	{
		tHeaderData HeaderData;
		memset (&HeaderData, 0, sizeof (HeaderData));

		nResult = m_pModule->m_pfnReadHeader (m_hArchive, &HeaderData);
		if( nResult!=0 )
			continue;
		
		char szDestPath[MAX_PATH] = {0};
		strcpy(szDestPath, lpDestPath);
		PathAppendA(szDestPath, HeaderData.FileName);
				
		int nProcessResult = 0;
		if ( (HeaderData.FileAttr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY )
		{
			CreateDirEx (szDestPath);
			nProcessResult = m_pModule->m_pfnProcessFile (m_hArchive, PK_SKIP, NULL, NULL);
			ATLASSERT(FALSE);
		}
		else
		{
			CreateDirs( szDestPath );

			SetFileApisToANSI();
			nProcessResult = m_pModule->m_pfnProcessFile (m_hArchive, PK_EXTRACT, NULL, szDestPath);
			SetFileApisToOEM();
			
			if(!nProcessResult)
				m_files.push_back( szDestPath );
		}
		
		if ( !nProcessResult  )
			nProcessed++;
	}
	return nProcessed!=0;
}