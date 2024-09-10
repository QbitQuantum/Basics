int main ( int argc, char* argv[] )
{
	char		szProjectFilePath	[_MAX_PATH	+1];
	char		szSourceFilePath	[_MAX_PATH	+1];
	char		szDrive						[_MAX_DRIVE	+1];
	char		szDir							[_MAX_DIR		+1];
	char		szExt							[_MAX_EXT		+1];
	char		szFname						[_MAX_PATH	+1];
	char		szOldDirectory		[_MAX_PATH	+1];
	int			i;
	_OPTIONS	*pOptTarget		= sOptions,
						*pOptPlatform	= sOptions,
						*pOptOS				= sOptions,
						*pOptFile			= sOptions,
						*pOptOpt			= sOptions;

	szProjectFilePath	[0] = '\0';
	szSourceFilePath	[0] = '\0';

	BOOL		flagPrint = TRUE;
	if ( argc < 2 )
		return 0;

	for ( i=2; i< argc; i++ )
		{
		 if ( i < argc )
			 *(argv[i]-1) = ' ';
		}
	ParseOptions( argv[1], sOptions, sOptionsSubst );
	GetCurrentDirectory( MAX_PATH, szOldDirectory );
	_splitpath( argv[1], szDrive, szDir, szFname, szExt );
	_makepath( szProjectFilePath, szDrive, szDir, szFname, szExt );
	ChangeSlash( szProjectFilePath );

	if( szProjectFilePath && ! access( szProjectFilePath, 4 ) )	// if a specified file exists
	{																														// and we have read access right

		if( strlen( szDir ) )
		{
			char		szProjectDirectory[_MAX_PATH	+1];
		
			szProjectDirectory[0] = '\0';
			strcat( szProjectDirectory, szDrive );
			strcat( szProjectDirectory, szDir );
			SetCurrentDirectory( szProjectDirectory );
		}

	FILE*	file;
	if ( flagPrint )
		{
		file= fopen(LOG_FILE_NAME, "w+t");
		fprintf(file, "%s", "MakePDF\n" );
		fclose(file);
		}

	while ( stricmp(pOptTarget	->pszOptionText, "TARGET"	 ) ) pOptTarget		++;
	while ( stricmp(pOptPlatform->pszOptionText, "PLATFORM") ) pOptPlatform	++;
	while ( stricmp(pOptOS			->pszOptionText, "OS"			 ) ) pOptOS				++;
	while ( stricmp(pOptFile		->pszOptionText, "FILE"		 ) ) pOptFile			++;
	while ( stricmp(pOptOpt			->pszOptionText, "OPTIONS" ) ) pOptOpt			++;

	if ( pOptFile->bOptionOn && *(pOptFile->pszOptionVal) )
		InternalConvertFileName( pOptFile->pszOptionVal, szSourceFilePath );

	SetCommonVar( pOptOS->pszOptionVal, pOptPlatform->pszOptionVal, pOptTarget->pszOptionVal ); 

	TargetNode		Head( szProjectFilePath, NULL );
	TargetNode*		pProjectNode;
	TargetNode*		pTarget;

	Head.ProcessNMake(TARGET_PROJECT);
	pProjectNode = Head.GetFirstChildPRJ();
	while ( pProjectNode )
		{
		 pProjectNode->ProcessNMake(TARGET_FILE_C);
		 if ( *szSourceFilePath && ( pTarget=pProjectNode->FindByNameTargetC(szSourceFilePath) ) != NULL )
				{
				 OptionNode	*pOption = pTarget->GetCompileOptions();
				 if ( pOption )
					{
					 printf(" cl -n %s", szSourceFilePath);
					 while ( pOption )
							{
							 printf(" -%s", pOption->GetOptionText() );
							 pOption= pOption->GetNext();
							}
					 printf("\n" );
					}
				 break;
				}
		 pProjectNode = pProjectNode->GetNext();
		}


	if ( !pOptFile->bOptionOn )
		{
			Head.CreateProjectTree();
			Head.RaiseUpPathC();
			Head.PrintProjectTree(0);
			Head.SetProjectPath();
			Head.ProcessFileH();
			Head.RaiseUpPathH();
			Head.RaiseUpTargetH();
			if (pOptOpt->bOptionOn)
				{
					Head.RaiseUpOptions();
					Head.WritePDFOptions();
				}
			Head.Wildcards();
			Head.PullDownPath();
			Head.PrintProjectTree(0);
			Head.ConvertFileName();
			Head.WritePDF();
		}
	SetCurrentDirectory( szOldDirectory );
	}
	
	return 0;
}