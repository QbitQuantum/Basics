/* static private */
HRESULT REGUTIL::_UnregisterClassBase( REFCLSID rclsid,
									   const char *szProgID,
									   const char *szIndepProgID,
									   char *szOutCLSID )
{
	char szID[64]; 	   // the class ID to register.
	OLECHAR	szWID[64]; // helper for the class ID to register.


    StringFromGUID2( rclsid, szWID, NumItems( szWID ) );
	WideCharToMultiByte( CP_ACP, 
						 0, 
						 szWID, 
						 -1, 
						 szID, 
						 sizeof( szID ), 
						 NULL, 
						 NULL );

	strcpy( szOutCLSID, "CLSID\\" );
	strcat( szOutCLSID, szID );

	// delete the version independant prog ID settings.
	DeleteKey( szIndepProgID, "CurVer" );
	DeleteKey( szIndepProgID, "CLSID" );
	RegDeleteKeyA( HKEY_CLASSES_ROOT, szIndepProgID );

	// delete the prog ID settings.
	DeleteKey( szProgID, "CLSID" );
	RegDeleteKeyA( HKEY_CLASSES_ROOT, szProgID );

	// delete the class ID settings.
	DeleteKey( szOutCLSID, "ProgID" );
	DeleteKey( szOutCLSID, "VersionIndependentProgID" );
	DeleteKey( szOutCLSID, "NotInsertable" );
	RegDeleteKeyA( HKEY_CLASSES_ROOT, szOutCLSID );
	
	
	return S_OK;

} // REGUTIL::_UnregisterClassBase