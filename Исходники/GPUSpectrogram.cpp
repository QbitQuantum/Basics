//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int _cdecl main( int NumArgs, char** ppCmdLine )
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // This may fail if Direct3D 10 isn't installed
    WCHAR wszPath[MAX_PATH+1] = {0};
    if( !::GetSystemDirectory( wszPath, MAX_PATH + 1 ) )
        return false;
    wcscat_s( wszPath, MAX_PATH, L"\\d3d10.dll" );
    HMODULE hMod = LoadLibrary( wszPath );
    if( NULL == hMod )
    {
        PrintError( "DirectX 10 is necessary to run GPUSpectrogram.\n" );
        return 1;
    }
    FreeLibrary( hMod );

    // parse the command line
    if( !ParseCommandLine( ppCmdLine, NumArgs ) )
        return 1;

    // create a device
    HRESULT hr = S_OK;
    ID3D10Device* pDevice = NULL;
    DWORD dwCreateFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    dwCreateFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif
    hr = D3D10CreateDevice( NULL, D3D10_DRIVER_TYPE_HARDWARE, ( HMODULE )0, dwCreateFlags,
                            D3D10_SDK_VERSION, &pDevice );
    if( FAILED( hr ) )
    {
        hr = D3D10CreateDevice( NULL, D3D10_DRIVER_TYPE_REFERENCE, ( HMODULE )0, dwCreateFlags,
                                D3D10_SDK_VERSION, &pDevice );
        if( FAILED( hr ) )
        {
            PrintError( "A suitable D3D10 device could not be created.\n" );
            return 1;
        }
    }

    if( FAILED( InitResources( pDevice ) ) )
    {
        PrintError( "GPUSpectrogram encountered an error creating resources.\n" );
        return 2;
    }

    CreateSpectrogram( pDevice );

    if( FAILED( SaveSpectogramToFile( pDevice, g_strBitmapName, g_pSourceTexture ) ) )
        PrintError( "GPUSpectrogram encountered an error saving the spectrogram image file.\n" );

    DestroyResources();
    SAFE_RELEASE( pDevice );

    return 0;
}