//-----------------------------------------------------------------------------------------
// This function does the following steps:
//
//      1. Initialize XACT by calling pEngine->Initialize 
//      2. Register for the XACT notification desired
//      3. Create the in memory XACT wave bank(s) you want to use
//      4. Create the streaming XACT wave bank(s) you want to use
//      5. Create the XACT sound bank(s) you want to use
//      6. Store indices to the XACT cue(s) your game uses
//-----------------------------------------------------------------------------------------
HRESULT PrepareXACT()
{
    HRESULT hr;
    WCHAR str[MAX_PATH];
    HANDLE hFile;
    DWORD dwFileSize;
    DWORD dwBytesRead;
    HANDLE hMapFile;

    // Clear struct
    ZeroMemory( &g_audioState, sizeof( AUDIO_STATE ) );
    InitializeCriticalSection( &g_audioState.cs );

    hr = CoInitializeEx( NULL, COINIT_MULTITHREADED );  // COINIT_APARTMENTTHREADED will work too
    if( SUCCEEDED( hr ) )
    {
        // Switch to auditioning mode based on command line.  Change if desired
        bool bAuditionMode = DoesCommandLineContainAuditionSwitch();
        bool bDebugMode = false;

        DWORD dwCreationFlags = 0;
        if( bAuditionMode ) dwCreationFlags |= XACT_FLAG_API_AUDITION_MODE;
        if( bDebugMode ) dwCreationFlags |= XACT_FLAG_API_DEBUG_MODE;

        hr = XACT3CreateEngine( dwCreationFlags, &g_audioState.pEngine );
    }
    if( FAILED( hr ) || g_audioState.pEngine == NULL )
        return E_FAIL;

    // Initialize & create the XACT runtime 
    XACT_RUNTIME_PARAMETERS xrParams = {0};
    xrParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
    xrParams.fnNotificationCallback = XACTNotificationCallback;
    hr = g_audioState.pEngine->Initialize( &xrParams );
    if( FAILED( hr ) )
        return hr;

    //-----------------------------------------------------------------------------------------
    // Register for XACT notifications
    //-----------------------------------------------------------------------------------------

    // The "wave bank prepared" notification will let the app know when it is save to use
    // play cues that reference streaming wave data.
    XACT_NOTIFICATION_DESCRIPTION desc = {0};
    desc.flags = XACT_FLAG_NOTIFICATION_PERSIST;
    desc.type = XACTNOTIFICATIONTYPE_WAVEBANKPREPARED;
    g_audioState.pEngine->RegisterNotification( &desc );

    // The "sound bank destroyed" notification will let the app know when it is save to use
    // play cues that reference streaming wave data.
    desc.flags = XACT_FLAG_NOTIFICATION_PERSIST;
    desc.type = XACTNOTIFICATIONTYPE_SOUNDBANKDESTROYED;
    g_audioState.pEngine->RegisterNotification( &desc );

    // The "cue stop" notification will let the app know when it a song stops so a new one 
    // can be played
    desc.flags = XACT_FLAG_NOTIFICATION_PERSIST;
    desc.type = XACTNOTIFICATIONTYPE_CUESTOP;
    desc.cueIndex = XACTINDEX_INVALID;
    g_audioState.pEngine->RegisterNotification( &desc );

    // The "cue prepared" notification will let the app know when it a a cue that uses 
    // streaming data has been prepared so it is ready to be used for zero latency streaming
    desc.flags = XACT_FLAG_NOTIFICATION_PERSIST;
    desc.type = XACTNOTIFICATIONTYPE_CUEPREPARED;
    desc.cueIndex = XACTINDEX_INVALID;
    g_audioState.pEngine->RegisterNotification( &desc );


    if( FAILED( hr = FindMediaFileCch( str, MAX_PATH, L"InMemoryWaveBank.xwb" ) ) )
        return hr;

    // Create an "in memory" XACT wave bank file using memory mapped file IO
    hr = E_FAIL; // assume failure
    hFile = CreateFile( str, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
    if( hFile != INVALID_HANDLE_VALUE )
    {
        dwFileSize = GetFileSize( hFile, NULL );
        if( dwFileSize != -1 )
        {
            hMapFile = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
            if( hMapFile )
            {
                g_audioState.pbInMemoryWaveBank = MapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );
                if( g_audioState.pbInMemoryWaveBank )
                {
                    hr = g_audioState.pEngine->CreateInMemoryWaveBank( g_audioState.pbInMemoryWaveBank, dwFileSize, 0,
                                                                       0, &g_audioState.pInMemoryWaveBank );
                }
                CloseHandle( hMapFile ); // pbInMemoryWaveBank maintains a handle on the file so close this unneeded handle
            }
        }
        CloseHandle( hFile ); // pbInMemoryWaveBank maintains a handle on the file so close this unneeded handle
    }
    if( FAILED( hr ) )
        return E_FAIL; // CleanupXACT() will cleanup state before exiting

    //-----------------------------------------------------------------------------------------
    // Create a streaming XACT wave bank file.  
    // Take note of the following:
    // 1) This wave bank in the XACT project file must marked as a streaming wave bank 
    //    This is set inside the XACT authoring tool)
    // 2) Use FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING flags when opening the file 
    // 3) To use cues that reference this streaming wave bank, you must wait for the 
    //    wave bank to prepared first or the playing the cue will fail
    //-----------------------------------------------------------------------------------------
    if( FAILED( hr = FindMediaFileCch( str, MAX_PATH, L"StreamingWaveBank.xwb" ) ) )
        return hr;
    hr = E_FAIL; // assume failure
    g_audioState.hStreamingWaveBankFile = CreateFile( str,
                                                      GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
                                                      FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING, NULL );
    if( g_audioState.hStreamingWaveBankFile != INVALID_HANDLE_VALUE )
    {
        XACT_WAVEBANK_STREAMING_PARAMETERS wsParams;
        ZeroMemory( &wsParams, sizeof( XACT_WAVEBANK_STREAMING_PARAMETERS ) );
        wsParams.file = g_audioState.hStreamingWaveBankFile;
        wsParams.offset = 0;

        // 64 means to allocate a 64 * 2k buffer for streaming.  
        // This is a good size for DVD streaming and takes good advantage of the read ahead cache
        wsParams.packetSize = 64;

        hr = g_audioState.pEngine->CreateStreamingWaveBank( &wsParams, &g_audioState.pStreamingWaveBank );
    }
    if( FAILED( hr ) )
        return E_FAIL; // CleanupXACT() will cleanup state before exiting

    // Create the XACT sound bank file with using memory mapped file IO
    if( FAILED( hr = FindMediaFileCch( str, MAX_PATH, L"sounds.xsb" ) ) )
        return hr;
    hr = E_FAIL; // assume failure
    hFile = CreateFile( str, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
    if( hFile != INVALID_HANDLE_VALUE )
    {
        dwFileSize = GetFileSize( hFile, NULL );
        if( dwFileSize != -1 )
        {
            // Allocate the data here and free the data when recieving the sound bank destroyed notification
            g_audioState.pbSoundBank = new BYTE[dwFileSize];
            if( g_audioState.pbSoundBank )
            {
                if( 0 != ReadFile( hFile, g_audioState.pbSoundBank, dwFileSize, &dwBytesRead, NULL ) )
                {
                    hr = g_audioState.pEngine->CreateSoundBank( g_audioState.pbSoundBank, dwFileSize, 0,
                                                                0, &g_audioState.pSoundBank );
                }
            }
        }
        CloseHandle( hFile ); // pbInMemoryWaveBank maintains a handle on the file so close this unneeded handle
    }
    if( FAILED( hr ) )
        return E_FAIL; // CleanupXACT() will cleanup state before exiting

    // Get the cue indices from the sound bank
    g_audioState.iZap = g_audioState.pSoundBank->GetCueIndex( "zap" );
    g_audioState.iRev = g_audioState.pSoundBank->GetCueIndex( "rev" );
    for( int i = 0; i < 3; i++ )
    {
        CHAR sz[256];
        StringCchPrintfA( sz, 256, "song%d", i + 1 );
        g_audioState.iSong[i] = g_audioState.pSoundBank->GetCueIndex( sz );
    }

    return S_OK;
}