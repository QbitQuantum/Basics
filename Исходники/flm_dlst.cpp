/****************************************************************************
Desc:
*****************************************************************************/
RCODE F_DynamicList::dumpToFile()
{
	RCODE					rc = NE_FLM_OK;
	DLIST_NODE *		pTmp;
	FLMUINT				uiLoop;
	IF_FileHdl *		pFileHdl = NULL;
#define DLST_RESP_SIZE 256
	char					szResponse[ DLST_RESP_SIZE];
	FLMUINT				uiTermChar;
	FTX_SCREEN *		pScreen;
	IF_FileSystem *	pFileSystem = NULL;
	
	if( RC_BAD( rc = FlmGetFileSystem( &pFileSystem)))
	{
		goto Exit;
	}

	f_strcpy( szResponse, (const char *)DLIST_DUMPFILE_PATH);

	FTXWinGetScreen( m_pListWin, &pScreen);
	FTXGetInput(
		pScreen,
 		"enter filename to dump to",
		szResponse,
		DLST_RESP_SIZE-1,
		&uiTermChar);

	if ( uiTermChar != FKB_ENTER)
	{
		goto Exit;
	}

	if (RC_BAD( rc = pFileSystem->doesFileExist( szResponse)))
	{
		//create file if it doesn't already exist
		if ( rc == NE_FLM_IO_PATH_NOT_FOUND)
		{
			rc = pFileSystem->createFile( szResponse, FLM_IO_RDWR, &pFileHdl);
		}
		else
		{
			goto Exit_local;
		}
	}
	else
	{
		rc = pFileSystem->openFile( szResponse, FLM_IO_RDWR, &pFileHdl);
	}

	TEST_RC_LOCAL( rc);

	{
		FLMUINT64	ui64FileSize = 0;
		FLMUINT		uiBytesWritten = 0;

		//figure out size of file currently, so you can append to it
		
		pFileHdl->size( &ui64FileSize);
		pTmp = m_pFirst;

		uiLoop = 0;
		while( pTmp)
		{
			FLMBYTE * pszNextLine = (FLMBYTE*)(pTmp->pvData);

			TEST_RC_LOCAL( rc = pFileHdl->write(
				ui64FileSize,					//offset to current file size
				f_strlen( (const char *)pszNextLine),
				pszNextLine,
				&uiBytesWritten));

			ui64FileSize += uiBytesWritten;

			TEST_RC_LOCAL( rc = pFileHdl->write(
				ui64FileSize,					//add in newline
				1,
				(FLMBYTE*)"\n",
				&uiBytesWritten));

			ui64FileSize += uiBytesWritten;
			pTmp = pTmp->pNext;
		}

		(void)pFileHdl->closeFile();

	}

Exit_local:
	{//give success/fail message

		char				szMessage[ 256];
		FLMUINT			uiChar;

		FTXWinGetScreen( m_pListWin, &pScreen);
		if ( RC_OK( rc))
		{
			f_sprintf( szMessage,
				"contents of focused list appended to %s", DLIST_DUMPFILE_PATH);
		}
		else
		{
			f_sprintf( szMessage, "error rc=%u dumping to file %s",
				(unsigned)rc, DLIST_DUMPFILE_PATH);
		}
		FTXDisplayMessage( pScreen, FLM_RED, FLM_WHITE, szMessage,
			"press ESC or ENTER to close dialog", &uiChar);
	}


Exit:

	if (pFileHdl)
	{
		pFileHdl->Release();
		pFileHdl = NULL;
	}
	
	if( pFileSystem)
	{
		pFileSystem->Release();
	}
	
	return rc;
}