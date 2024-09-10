HRESULT    CProxyDirect3D9::CreateDevice                ( UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface )
{
// Do not change the code at the start of this function.
// Some graphic card drivers seem sensitive to the content of the CreateDevice function.
    HRESULT hResult;

    WriteDebugEvent ( "CProxyDirect3D9::CreateDevice" );

    WriteDebugEvent ( SString ( "    Adapter:%d  DeviceType:%d  BehaviorFlags:0x%x"
                                ,Adapter
                                ,DeviceType
                                ,BehaviorFlags
                            ) );

    // Make sure DirectX Get calls will work
    BehaviorFlags &= ~D3DCREATE_PUREDEVICE;

    WriteDebugEvent ( SString ( "    BackBufferWidth:%d  Height:%d  Format:%d  Count:%d"
                                ,pPresentationParameters->BackBufferWidth
                                ,pPresentationParameters->BackBufferHeight
                                ,pPresentationParameters->BackBufferFormat
                                ,pPresentationParameters->BackBufferCount
                           ) );

    WriteDebugEvent ( SString ( "    MultiSampleType:%d  Quality:%d"
                                ,pPresentationParameters->MultiSampleType
                                ,pPresentationParameters->MultiSampleQuality
                           ) );

    WriteDebugEvent ( SString ( "    SwapEffect:%d  Windowed:%d  EnableAutoDepthStencil:%d  AutoDepthStencilFormat:%d  Flags:0x%x"
                                ,pPresentationParameters->SwapEffect
                                ,pPresentationParameters->Windowed
                                ,pPresentationParameters->EnableAutoDepthStencil
                                ,pPresentationParameters->AutoDepthStencilFormat
                                ,pPresentationParameters->Flags
                           ) );

    WriteDebugEvent ( SString ( "    FullScreen_RefreshRateInHz:%d  PresentationInterval:0x%08x"
                                ,pPresentationParameters->FullScreen_RefreshRateInHz
                                ,pPresentationParameters->PresentationInterval
                           ) );


    // Change the window title to MTA: San Andreas
    #ifdef MTA_DEBUG
        SetWindowTextW ( hFocusWindow, MbUTF8ToUTF16("MTA: San Andreas [DEBUG]").c_str() );
    #else
        SetWindowTextW ( hFocusWindow, MbUTF8ToUTF16("MTA: San Andreas").c_str() );
    #endif

    // Detect if second call to CreateDevice
    if ( CreateDeviceSecondCallCheck( hResult, m_pDevice, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface ) )
    {
        return hResult;
    }

    // Enable the auto depth stencil parameter
    pPresentationParameters->EnableAutoDepthStencil = true;
    
    GetVideoModeManager ()->PreCreateDevice ( pPresentationParameters );

    // Create our object.
    hResult = m_pDevice->CreateDevice ( Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface );

    // Store the rendering window in the direct 3d data
    CDirect3DData::GetSingleton ().StoreDeviceWindow ( pPresentationParameters->hDeviceWindow );

    // Make sure the object was created successfully.
    if ( hResult == D3D_OK )
    {
        // Apply input hook
        CMessageLoopHook::GetSingleton ( ).ApplyHook ( hFocusWindow );

        GetVideoModeManager ()->PostCreateDevice ( *ppReturnedDeviceInterface, pPresentationParameters );

        // We must first store the presentation values.
        CDirect3DData::GetSingleton ( ).StoreViewport ( 0, 0,
                                                        pPresentationParameters->BackBufferWidth,
                                                        pPresentationParameters->BackBufferHeight );
        
        // Calc and store readable depth format for shader use
        ERenderFormat ReadableDepthFormat = CDirect3DEvents9::DiscoverReadableDepthFormat ( *ppReturnedDeviceInterface, pPresentationParameters->MultiSampleType, pPresentationParameters->Windowed != 0 );
        CGraphics::GetSingleton ().GetRenderItemManager ()->SetDepthBufferFormat ( ReadableDepthFormat );

        // Now create the proxy device.
        *ppReturnedDeviceInterface = new CProxyDirect3DDevice9 ( *ppReturnedDeviceInterface );

        // Debug output
        D3DDEVICE_CREATION_PARAMETERS parameters;
        (*ppReturnedDeviceInterface)->GetCreationParameters ( &parameters );

        WriteDebugEvent ( SString ( "    Adapter:%d  DeviceType:%d  BehaviorFlags:0x%x  ReadableDepth:%s"
                                    ,parameters.AdapterOrdinal
                                    ,parameters.DeviceType
                                    ,parameters.BehaviorFlags
                                    ,ReadableDepthFormat ? std::string ( (char*)&ReadableDepthFormat, 4 ).c_str () : "None"
                                ) );
    }

    hResult = HandleCreateDeviceResult( hResult, m_pDevice, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface );

    return hResult;
}