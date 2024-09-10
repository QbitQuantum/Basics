void JabberGetAvatarFileName( HANDLE hContact, char* pszDest, int cbLen )
{
	JCallService( MS_DB_GETPROFILEPATH, cbLen, LPARAM( pszDest ));

	int tPathLen = strlen( pszDest );
	tPathLen += mir_snprintf( pszDest + tPathLen, MAX_PATH - tPathLen, "\\Jabber\\"  );
	CreateDirectoryA( pszDest, NULL );

	char* szFileType;
	switch( JGetByte( hContact, "AvatarType", PA_FORMAT_PNG )) {
		case PA_FORMAT_JPEG: szFileType = "jpg";   break;
		case PA_FORMAT_GIF:  szFileType = "gif";   break;
		case PA_FORMAT_BMP:  szFileType = "bmp";   break;
		case PA_FORMAT_PNG:  szFileType = "png";   break;
		default: szFileType = "bin";
	}

	if ( hContact != NULL ) {
		char str[ 256 ];
		DBVARIANT dbv;
		if ( !JGetStringUtf( hContact, "jid", &dbv )) {
			strncpy( str, dbv.pszVal, sizeof str );
			str[ sizeof(str)-1 ] = 0;
			JFreeVariant( &dbv );
		}
		else ltoa(( long )hContact, str, 10 );

		char* hash = JabberSha1( str );
		mir_snprintf( pszDest + tPathLen, MAX_PATH - tPathLen, "%s.%s", hash, szFileType );
		mir_free( hash );
	}
	else if ( jabberThreadInfo != NULL ) {
		mir_snprintf( pszDest + tPathLen, MAX_PATH - tPathLen, TCHAR_STR_PARAM"@%s avatar.%s", jabberThreadInfo->username, jabberThreadInfo->server, szFileType );
	}
	else {
		DBVARIANT dbv1, dbv2;
		BOOL res1 = DBGetContactSetting( NULL, jabberProtoName, "LoginName", &dbv1 );
		BOOL res2 = DBGetContactSetting( NULL, jabberProtoName, "LoginServer", &dbv2 );
		mir_snprintf( pszDest + tPathLen, MAX_PATH - tPathLen, "%s@%s avatar.%s", 
			res1 ? "noname" : dbv1.pszVal, 
			res2 ? jabberProtoName : dbv2.pszVal,
			szFileType );
		if (!res1) JFreeVariant( &dbv1 );
		if (!res2) JFreeVariant( &dbv2 );
	}	
}