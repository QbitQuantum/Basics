/****************************************************************************
Desc: Returns the requested file handle
****************************************************************************/
RCODE F_MultiFileHdl::getFileHdl(
	FLMUINT				uiFileNum,
	FLMBOOL				bGetForWrite,
	IF_FileHdl **		ppFileHdl)
{
	RCODE					rc	= NE_FLM_OK;
	IF_FileSystem *	pFileSystem = f_getFileSysPtr();
	FLMUINT				uiSlot;
	IF_FileHdl *		pTmpHdl;
	char					szPath[ F_PATH_MAX_SIZE];

	f_assert( m_bOpen);

	*ppFileHdl = NULL;

	uiSlot = uiFileNum % F_MULTI_FHDL_LIST_SIZE;
	pTmpHdl = m_pFileHdlList[ uiSlot].pFileHdl;

	if( pTmpHdl && m_pFileHdlList[ uiSlot].uiFileNum != uiFileNum)
	{
		if( RC_BAD( rc = pTmpHdl->flush()))
		{
			goto Exit;
		}

		pTmpHdl->closeFile();
		pTmpHdl->Release();
		pTmpHdl = NULL;

		f_memset( &m_pFileHdlList[ uiSlot], 0, sizeof( FH_INFO));
	}

	if( !pTmpHdl)
	{
		dataFilePath( uiFileNum, szPath);
		if( RC_BAD( rc = pFileSystem->openFile( szPath, 
			FLM_IO_RDWR, &pTmpHdl)))
		{
			if( rc == NE_FLM_IO_PATH_NOT_FOUND && bGetForWrite)
			{
				if( RC_BAD( rc = pFileSystem->createFile( szPath,
 					FLM_IO_RDWR, &pTmpHdl)))
				{
					goto Exit;
				}
			}
			else
			{
				goto Exit;
			}
		}

		m_pFileHdlList[ uiSlot].pFileHdl = pTmpHdl;
		m_pFileHdlList[ uiSlot].uiFileNum = uiFileNum;
		f_assert( !m_pFileHdlList[ uiSlot].bDirty);
	}

	*ppFileHdl = m_pFileHdlList[ uiSlot].pFileHdl;
	if( bGetForWrite)
	{
		m_pFileHdlList[ uiSlot].bDirty = TRUE;
	}

Exit:

	return( rc);
}