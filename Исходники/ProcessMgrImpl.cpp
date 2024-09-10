 BOOL CProcessMgrImpl::SetWin7Mute( BOOL bMute/* =TRUE */ )
 {
     if ( m_bMute == bMute )
         return S_OK;
         
         
     IMMDeviceEnumerator* pEnumerator;
     
     HRESULT hr = E_FAIL;
     CoInitialize( NULL );
     hr = CoCreateInstance( __uuidof( MMDeviceEnumerator ), NULL,
                            CLSCTX_ALL, __uuidof( IMMDeviceEnumerator ), ( void** )&pEnumerator );
                            
     IMMDevice* pDevice;
     hr = pEnumerator->GetDefaultAudioEndpoint( eRender, eConsole, &pDevice );
     if ( FAILED( hr ) )
         return hr;
         
     IAudioSessionManager2* pasm = NULL;
     hr = pDevice->Activate( __uuidof( IAudioSessionManager2 ), CLSCTX_ALL, NULL, ( void** )&pasm );
     if ( FAILED( hr ) )
         return hr;
         
     IAudioSessionEnumerator* audio_session_enumerator;
     if ( SUCCEEDED( pasm->GetSessionEnumerator( &audio_session_enumerator ) ) )
     {
         int count;
         
         if ( SUCCEEDED( audio_session_enumerator->GetCount( &count ) ) )
         {
             for ( int i = 0; i < count; i++ )
             {
                 IAudioSessionControl* audio_session_control;
                 IAudioSessionControl2* audio_session_control2;
                 
                 if ( SUCCEEDED( audio_session_enumerator->GetSession( i, &audio_session_control ) ) )
                 {
                     if ( SUCCEEDED( audio_session_control->QueryInterface( __uuidof( IAudioSessionControl2 ), ( void** )&audio_session_control2 ) ) )
                     {
                         DWORD processid;
                         
                         if ( SUCCEEDED( audio_session_control2->GetProcessId( &processid ) ) )
                         {
                             if ( processid == GetCurrentProcessId() )
                             {
                                 ISimpleAudioVolume* pSAV;
                                 hr = audio_session_control2->QueryInterface( __uuidof( ISimpleAudioVolume ), ( void** ) &pSAV );
                                 if ( SUCCEEDED( hr ) )
                                 {
                                     hr = pSAV->SetMute( bMute, NULL );
                                     if ( SUCCEEDED( hr ) )
                                     {
                                         m_bMute = bMute;
                                     }
                                     pSAV->Release();
                                 }
                             }
                             audio_session_control->Release();
                             audio_session_control2->Release();
                         }
                     }
                 }
             }
             audio_session_enumerator->Release();
         }
     }
     
     pasm->Release();
     
     SafeRelease( &pEnumerator );
     
     ::CoUninitialize();
     
     return hr;
 }