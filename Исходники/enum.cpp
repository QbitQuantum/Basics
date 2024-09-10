BOOL WINAPI DDEnumCallback( GUID *pGUID, LPSTR pDescription, LPSTR strName,
                              LPVOID pContext )
{
	LPDIRECTDRAW7 pDD = NULL;	
	HRESULT hr;

	
	if( FAILED( hr = DirectDrawCreateEx( pGUID, (VOID**)&pDD, 
										 IID_IDirectDraw7, NULL ) ) )
		return DDENUMRET_CANCEL;

	
	pDD->GetDeviceIdentifier( &DeviceInfo[g_iMaxDevices], 0 );


	
	if(pDD) {
		pDD->Release();
		pDD = NULL;
	}

	
	if( g_iMaxDevices < MAX_DEVICES )
		g_iMaxDevices++;
	else
		return DDENUMRET_CANCEL;

	return DDENUMRET_OK;
}