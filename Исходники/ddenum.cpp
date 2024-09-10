//-----------------------------------------------------------------------------
// Name: DDEnumCallbackEx()
// Desc: This callback gets the information for each device enumerated
//-----------------------------------------------------------------------------
BOOL WINAPI DDEnumCallbackEx( GUID *pGUID, LPSTR pDescription, LPSTR strName,
                              LPVOID pContext, HMONITOR hm )
{
    LPDIRECTDRAW7 pDD = NULL;	
    HRESULT hr;

    // Create a DirectDraw object using the enumerated GUID
    if( FAILED( hr = DirectDrawCreateEx( pGUID, (VOID**)&pDD, 
                                         IID_IDirectDraw7, NULL ) ) )
        return DDENUMRET_CANCEL;

    // Get the device information and save it
    pDD->GetDeviceIdentifier( &g_DeviceIdent[g_iMaxDevices].DeviceInfo, 0 );
    pDD->GetDeviceIdentifier( &g_DeviceIdent[g_iMaxDevices].DeviceInfoHost, 
                              DDGDI_GETHOSTIDENTIFIER );

    // Finished with the DirectDraw object, so release it
    SAFE_RELEASE( pDD ); 

    // Bump to the next open slot or finish the callbacks if full
    if( g_iMaxDevices < MAX_DEVICES )
        g_iMaxDevices++;
    else
        return DDENUMRET_CANCEL;

    return DDENUMRET_OK;
}