void CAntiVirus::Enum(CComboBox& wndAntiVirus)
{
	if ( ! ::IsWindow( wndAntiVirus.GetSafeHwnd() ) )
		return;

	wndAntiVirus.ResetContent();

	// No anti-virus
	int nAntiVirus = wndAntiVirus.AddString( _T("") );
	wndAntiVirus.SetItemDataPtr( nAntiVirus, (LPVOID)new CString() );

	// Enum available anti-viruses
	CComPtr< ICatInformation > pInfo;
	HRESULT hr = pInfo.CoCreateInstance( CLSID_StdComponentCategoriesMgr );
	if ( SUCCEEDED( hr ) )
	{
		const CATID IDs[ 1 ] = { CATID_MSOfficeAntiVirus };
        CComPtr< IEnumCLSID > pEnum;
        hr = pInfo->EnumClassesOfCategories( 1, IDs, 0, NULL, &pEnum );
		if ( SUCCEEDED( hr ) )
		{
			CLSID clsid;
			while ( pEnum->Next( 1, &clsid, NULL ) == S_OK )
			{
				const CString sCLSID = Hashes::toGuid( clsid, true );
				HKEY hClass = NULL;
				if ( ERROR_SUCCESS == RegOpenKeyEx( HKEY_CLASSES_ROOT, _T("CLSID\\") + sCLSID, 0, KEY_READ, &hClass ) )
				{
					// Get it name
					TCHAR szValue[ MAX_PATH ] = {};
					DWORD nValue = MAX_PATH, nType = REG_SZ;
					if ( ERROR_SUCCESS == RegQueryValueEx( hClass, NULL, NULL, &nType, (LPBYTE)szValue, &nValue ) )
					{
						const int nIndex = wndAntiVirus.AddString( szValue );
						wndAntiVirus.SetItemDataPtr( nIndex, (LPVOID)new CString( sCLSID ) );
						if ( Settings.General.AntiVirus.CompareNoCase( sCLSID ) == 0 )
						{
							nAntiVirus = nIndex;
						}
					}
					RegCloseKey( hClass );
				}
			}
		}
	}

	wndAntiVirus.SetCurSel( nAntiVirus );
	wndAntiVirus.EnableWindow( wndAntiVirus.GetCount() > 1 );
}