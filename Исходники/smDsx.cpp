// Direct3D 생성
BOOL CreateD3D()
{
    // DirectDraw 인터페이스 생성
    LPDIRECTDRAW lpdd;

    // 설정된 DirectDraw Device
    HRESULT hresult = DirectDrawCreate( NULL, &lpdd, NULL );
    if ( hresult != DD_OK )
	{
		MESSAGE( "DirectDrawCreate" );
        return FALSE;
	}

    // DirectDraw2 인터페이스 얻기
    hresult = lpdd->QueryInterface( IID_IDirectDraw4, (LPVOID*)&lpDD );
    if ( hresult != DD_OK )
	{
		MESSAGE( "lpdd->QueryInterface" );
        return FALSE;
	}

    // DirectDraw 인터페이스 제거
    lpdd->Release();


    // Direct3D 인터페이스 얻기
    hresult = lpDD->QueryInterface( IID_IDirect3D3, (LPVOID*)&lpD3D );
    if ( hresult != DD_OK )
	{
		MESSAGE( "lpDD3->QueryInterface" );
        return FALSE;
	}

    // Direct3D Device 인터페이스 얻기
	hresult = lpD3D->EnumDevices( DeviceEnumCallback, (LPVOID)&lpDeviceDesc );
    if ( hresult != DD_OK )
	{
		MESSAGE( "lpD3D->EnumDevices" );
        return FALSE;
	}

	lpD3DDeviceDesc = FindBestDevice( lpDeviceDesc );
	if ( !lpD3DDeviceDesc )
		return FALSE;

    return TRUE;
}