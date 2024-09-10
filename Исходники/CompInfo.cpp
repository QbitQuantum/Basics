void CCompInfo::HeapCompareDumpWithFile(BOOL bShowContent)
{
	PROCESS_HEAP_ENTRY pEntry;
	m_dwCurrentSize = 0;
	BOOL bIsPresent = FALSE, bResult = FALSE;
	HANDLE hFile;
	DWORD dwPlace = 0, dwSize = 0;
	DWORD dwIn[2], dwOut;

	GetHeaps();
	
	hFile = CreateFile(HEAP_DUMP_FILENAME, GENERIC_READ, 0, NULL, OPEN_EXISTING , FILE_ATTRIBUTE_READONLY , NULL );
	if ( INVALID_HANDLE_VALUE == hFile ) return;

	if (NULL != m_log)
	{
		if (bShowContent)
			m_log->print( "\n\n ----- E X T E N D E D  H E A P  D U M P ----- \n\n");
		else
			m_log->print("\n\n ----- B A S I C  H E A P  D U M P ----- \n\n");
	}

	for ( unsigned i=0; i < m_nHeaps; i++ )
	{
		pEntry.lpData = NULL;
		while (HeapWalk(m_aHeaps[i], &pEntry ))
		{
			if ((PROCESS_HEAP_ENTRY_BUSY & pEntry.wFlags) == PROCESS_HEAP_ENTRY_BUSY)
			{
				SetFilePointer (hFile, NULL , NULL, FILE_BEGIN) ; 
				bIsPresent = FALSE;
				memset( dwIn , 0 , sizeof(DWORD)*2 );
				dwOut = 0;
				while( 1 )
				{      
					bResult = ReadFile(hFile, &dwIn, sizeof(DWORD)*2 , &dwOut, NULL );
					if (bResult && dwOut == 0)  break;
					if ( dwIn[0] == (DWORD)pEntry.lpData && dwIn[1] == (DWORD)pEntry.cbData )
					{
						bIsPresent = TRUE;
						break;
					}
							
				}
				if (!bIsPresent)
				{
					if (NULL != m_log)
						m_log->print("block at [0x%x] size [%d]\n" , pEntry.lpData , pEntry.cbData );

					if (bShowContent)
					{
						char* pData = (char *)pEntry.lpData;
						for ( unsigned k = 0 ; k < pEntry.cbData; k++ )
						{
							if ( NULL != m_log )
								m_log->print( "%c" , pData[k] );
						}
						if ( NULL != m_log )
							m_log->print("\n\n");
					}
				}

			}
		}
	}

	CloseHandle(hFile);
}