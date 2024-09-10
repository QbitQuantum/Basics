/****************************************************************************
Desc:
****************************************************************************/
RCODE createUnitTest(
	const char *		configPath, 
	const char *		buildNum, 
	const char *		environment,  
	const char *		user, 
	unitTestData *		uTD)
{
	RCODE					rc = FERR_OK;
	IF_FileHdl *		pConfigFileHdl = NULL;
	IF_FileHdl *		pCSVFileHdl = NULL;
	FLMBYTE				buffer[ MAX_BUFFER_SIZE] = "";
	FLMUINT				uiSize = MAX_BUFFER_SIZE;
	FLMUINT64			ui64Tmp;
	char *				strPos1 = NULL;
	char *				strPos2 = NULL;
	IF_FileSystem *	pFileSystem = NULL;

	if( !configPath || !buildNum || !environment || !uTD || !user)
	{
		flmAssert(0);
	}

	if( f_strlen(user) > MAX_SMALL_BUFFER_SIZE)
	{
		rc = RC_SET( FERR_CONV_DEST_OVERFLOW);
		goto Exit;
	}
	else
	{
		f_strcpy( uTD->userName, user);
	}

	if( f_strlen(environment) > MAX_SMALL_BUFFER_SIZE)
	{
		rc = RC_SET( FERR_CONV_DEST_OVERFLOW);
		goto Exit;
	}
	else
	{
		f_strcpy( uTD->environment, environment);
	}

	if( f_strlen( buildNum) > MAX_SMALL_BUFFER_SIZE)
	{
		rc = RC_SET( FERR_CONV_DEST_OVERFLOW);
		goto Exit;
	}
	else
	{
		f_strcpy( uTD->buildNumber, buildNum);
	}
	
	if( RC_BAD( rc = FlmGetFileSystem( &pFileSystem)))
	{
		goto Exit;
	}
	
	if( configPath[ 0])
	{
		if( RC_BAD( rc = pFileSystem->openFile(
			configPath, FLM_IO_RDONLY | FLM_IO_SH_DENYNONE, &pConfigFileHdl)))
		{
			goto Exit;
		}
	
		if( RC_BAD( rc = pConfigFileHdl->size( &ui64Tmp)))
		{
			goto Exit;
		}
		
		uiSize = (FLMUINT)ui64Tmp;
		
		if( RC_BAD( rc = pConfigFileHdl->read( 0, uiSize, buffer, &uiSize)))
		{
			goto Exit;
		}
	
		#ifdef FLM_WIN
		{
			char			szTemp[ MAX_BUFFER_SIZE];
			char *		pszTemp = szTemp;
			FLMUINT		uiNewSize = uiSize;
		
			for( unsigned int i = 0; i < uiSize; i++)
			{
				if( ((i + 1) < uiSize) 
					&& (buffer[i] == 0x0D && buffer[ i + 1] == 0x0A))
				{
					*pszTemp++ = 0x0A;
					i++;
					uiNewSize--;
				}
				else
				{
					*pszTemp++ = buffer[ i];
				}
			}
				
			f_memcpy( buffer, szTemp, uiNewSize);
			uiSize = uiNewSize;
		}
		#endif
		
		// Get the FOLDER
		
		strPos1 = f_strchr( (const char *)buffer, ':');
		strPos2 = f_strchr( (const char *)strPos1, '\n');
		
		if( !strPos1 || !strPos2)
		{
			rc = RC_SET( FERR_FAILURE);
			goto Exit;
		}

		for( strPos1++; *strPos1 == ' ' || *strPos1 == '\t'; strPos1++);
		
		if( strPos2-strPos1 > MAX_SMALL_BUFFER_SIZE)
		{
			rc = RC_SET( FERR_CONV_DEST_OVERFLOW);
			goto Exit;
		}
		
		f_strncpy( uTD->folder, strPos1, strPos2-strPos1);
		uTD->folder[ strPos2 - strPos1] = '\0';

		// Get the ATTRIBUTES
		
		strPos1 = f_strchr( (const char *)strPos1, ':');
		strPos2 = f_strchr( (const char *)strPos1, '\n');
		
		if( !strPos1 || !strPos2)
		{
			rc = RC_SET( FERR_FAILURE);
			goto Exit;
		}

		for( strPos1++;*strPos1 == ' ' || *strPos1 == '\t';strPos1++);
		
		if( strPos2-strPos1 > MAX_SMALL_BUFFER_SIZE)
		{
			rc = RC_SET( FERR_FAILURE);
			goto Exit;
		}
		
		f_strncpy( uTD->attrs, strPos1, strPos2-strPos1);
		uTD->attrs[strPos2-strPos1] = '\0';

		// Get the CSVFILE
		
		strPos1 = f_strchr( (const char *)strPos1, ':');
		strPos2 = f_strchr( (const char *)strPos1, '\n');
		
		// Allow for possible \r
		
		if( *( --strPos2) != '\r')
		{
			strPos2++;
		}

		if( !strPos1 || !strPos2)
		{
			rc = RC_SET( FERR_FAILURE);
			goto Exit;
		}

		for( strPos1++;*strPos1 == ' ' || *strPos1 == '\t';strPos1++);

		if( strPos2-strPos1 > MAX_SMALL_BUFFER_SIZE)
		{
			rc = RC_SET( FERR_FAILURE);
			goto Exit;
		}

		f_strncpy( uTD->csvFilename, strPos1, strPos2-strPos1);
		uTD->csvFilename[ strPos2 - strPos1] = '\0';

		if( RC_BAD( rc = pFileSystem->openFile( uTD->csvFilename,
			FLM_IO_RDWR | FLM_IO_SH_DENYNONE, &pCSVFileHdl)))
		{
			if ( rc == FERR_IO_PATH_NOT_FOUND)
			{
				// Create the file and write the header
				
				if( RC_BAD( rc = f_filecat( uTD->csvFilename, DATA_ORDER)))
				{
					goto Exit;
				}
			}
		}
		else
		{
			goto Exit;
		}
	}

Exit:

	if( pConfigFileHdl)
	{
		pConfigFileHdl->Release();
	}
	
	if( pCSVFileHdl)
	{
		pCSVFileHdl->Release();
	}
	
	if( pFileSystem)
	{
		pFileSystem->Release();
	}
	
	return( rc);
}