void CPlugins::Enumerate()
{
	HUSKEY hKey = NULL;
	if ( SHRegOpenUSKey( REGISTRY_KEY _T("\\Plugins\\General"),
		KEY_READ, NULL, &hKey, FALSE ) != ERROR_SUCCESS ) return;

	for ( DWORD nKey = 0 ; ; nKey++ )
	{
		TCHAR szName[ 128 ], szCLSID[ 64 ];
		DWORD dwType, dwName = _countof( szName ), dwCLSID = sizeof( szCLSID );

		if ( SHRegEnumUSValue( hKey, nKey, szName, &dwName, &dwType,
			(LPBYTE)szCLSID, &dwCLSID, SHREGENUM_DEFAULT ) != ERROR_SUCCESS ) break;

		if ( dwType != REG_SZ ) continue;
		szCLSID[ 38 ] = 0;

		CLSID pCLSID;
		if ( ! Hashes::fromGuid( szCLSID, &pCLSID ) ) continue;

		CQuickLock oLock( m_pSection );

		for ( POSITION pos = GetIterator() ; pos ; )
		{
			if ( GetNext( pos )->m_pCLSID == pCLSID )
			{
				pCLSID = GUID_NULL;
				break;
			}
		}

		if ( pCLSID == GUID_NULL ) continue;

		if ( CPlugin* pPlugin = new CPlugin( pCLSID, szName ) )
		{
			m_pList.AddTail( pPlugin );

			if ( LookupEnable( pCLSID ) )
				pPlugin->Start();
		}
	}

	SHRegCloseUSKey( hKey );
}