//******************************************************************************************
//
void	TargetNode::WritePDF()
{
	char	szFileNamePDF[_MAX_PATH];
	strcpy( szFileNamePDF, GetMakeFileName() );
	char*	pszExt = strrchr( szFileNamePDF, '.');
	if ( pszExt )
		memcpy( pszExt+1, "pdf", 5);
	else
		strcat( szFileNamePDF, ".pdf");

	if ( GetSlash() == '\\' )
		filePDF = fopen( szFileNamePDF, "w+t" );
	else
		filePDF = fopen( szFileNamePDF, "w+b" );
	if ( !filePDF )
		{
		 MessageBox(NULL, "Open file error", "MakePDF", MB_OK);
		 return;
		}

	char	szTimeBuff[40], szDateBuff[40];
	char	szBuffer[_MAX_PATH+1];

	ZeroMemory( (void*)&szBuffer, sizeof(szBuffer) );
	memset( szBuffer, '#', 80 );

//	_tzset();
	_strtime( szTimeBuff );
	_strdate( szDateBuff );

	fprintf( filePDF, "%s", szBuffer );
	fprintf( filePDF, "\n");
	fprintf( filePDF, "##\tFile was created by MakePDF %s %s", szDateBuff, szTimeBuff );
	fprintf( filePDF, "\n");
	fprintf( filePDF, "##\tMakeFile\t: %s", GetMakeFileName() );
	fprintf( filePDF, "\n");
	fprintf( filePDF, "##\tPlatform\t: %s", GetPlatformTarget() );
	fprintf( filePDF, "\n");
	fprintf( filePDF, "##\tTargetOS\t: %s", GetTargetOS() );
	fprintf( filePDF, "\n");
	fprintf( filePDF, "%s", szBuffer );
	fprintf( filePDF, "\n"); fprintf( filePDF, "\n");

	TargetNode*	pTargetPRJ = GetFirstChildPRJ();
	while ( pTargetPRJ )
		{
		 pTargetPRJ->WritePDFTree(0);
		 pTargetPRJ = pTargetPRJ->GetNext();
		}

	fclose( filePDF );
}