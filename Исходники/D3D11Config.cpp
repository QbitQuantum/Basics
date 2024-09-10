bool
D3D11Config::enumerateDisplaysCreateD3DDevice(oapi::GraphicsClient::VIDEODATA *vdata)
{
    oapiWriteLogV("D3D11Config::enumerateDisplaysCreateD3DDevice");
	
    DXGI_ADAPTER_DESC adapterDesc;
    DXGI_OUTPUT_DESC outputDesc;

    // First enumerate the monitors
    PHYSICAL_MONITOR monitor;
    UINT adapterCount = 0, outputCount = 0;
    char *line, cbuf[128];
    HR( CreateDXGIFactory1( __uuidof(IDXGIFactory1), (void**)(&m_dxgiFactory) ) );
    if (!m_dxgiFactory) {
        SHOW_MESSAGE("Initialization error", "CreateDXGIFactory1 failed");
        return false;
    }
    while ( m_dxgiFactory->EnumAdapters1( adapterCount, &dxgiAdapter ) == S_OK ) {
        dxgiAdapter->GetDesc( &adapterDesc );
        while ( dxgiAdapter->EnumOutputs( outputCount, &dxgiOutput ) == S_OK ) {
			dxgiOutput->GetDesc(&outputDesc);

            GetPhysicalMonitorsFromHMONITOR( outputDesc.Monitor, 1, &monitor );
            wcstombs( cbuf, monitor.szPhysicalMonitorDescription, 128 );
            DestroyPhysicalMonitors( 1, &monitor );

            line = new char [128];
            vecDXGIAdapterOutputDesc.push_back( line );
			wcstombs(vecDXGIAdapterOutputDesc[outputCount], adapterDesc.Description, 128);
			strcat(vecDXGIAdapterOutputDesc[outputCount], cbuf);

            vecDXGIOutputs.push_back( dxgiOutput );
            ++outputCount;
        }

        vecDXGIAdapters.push_back( dxgiAdapter );
        ++adapterCount;
    }
    UINT numOutputs = outputCount;

    if ( vdata->deviceidx < 0 || (UINT)vdata->deviceidx > outputCount ) {
        vdata->deviceidx = 0;
    }

    UINT numModes;
    vecDXGIOutputs[vdata->deviceidx]->GetDisplayModeList( DXGI_FORMAT_B8G8R8A8_UNORM,
                                                          0, &numModes, NULL );
    DXGI_MODE_DESC *modes = new DXGI_MODE_DESC [numModes];
    vecDXGIOutputs[vdata->deviceidx]->GetDisplayModeList( DXGI_FORMAT_B8G8R8A8_UNORM,
                                                          0, &numModes, modes );

    dxgiAdapter = vecDXGIAdapters[vdata->deviceidx];
    dxgiOutput = vecDXGIOutputs[vdata->deviceidx];
    dxgiMode = modes[vdata->modeidx];

    //FullScreenWindow = vdata->pageflip;
    driverType = /*vdata->forceenum ? D3D_DRIVER_TYPE_REFERENCE : */D3D_DRIVER_TYPE_UNKNOWN;
    bFullScreenWindow = vdata->fullscreen;
    dwWidth = vdata->winw;
    dwHeight = vdata->winh;

    D3D_FEATURE_LEVEL featureLevels[ ] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1
    };

    UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    HRESULT result = D3D11CreateDevice(
        dxgiAdapter,
        driverType,  // Not unknown
        0,                              // no software device
        createDeviceFlags,
        featureLevels,
        3,                              // Why 3 ? !!
        D3D11_SDK_VERSION,
        &m_d3dDevice,
        &(succeededFeatureLevel),
        &m_d3dImmContext);

    if (!m_d3dDevice) {
        char errMsg[200];
        sprintf(errMsg, "Device creation failed.\nError code: 0x%08p", result);
        MessageBoxA( m_GraphicsClient.m_hWindow, errMsg, "Critical error.",
                     MB_ICONERROR | MB_OK );
    }

    // D3D11 Debugging
  //  m_d3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&m_d3dDebug));

	return true;
}