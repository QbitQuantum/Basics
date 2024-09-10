//--------------------------------------------------------------------------------------
// Enumerate for each adapter all of the supported display modes, 
// device types, adapter formats, back buffer formats, window/full screen support, 
// depth stencil formats, multisampling types/qualities, and presentations intervals.
//
// For each combination of device type (HAL/REF), adapter format, back buffer format, and
// IsWindowed it will call the app's ConfirmDevice callback.  This allows the app
// to reject or allow that combination based on its caps/etc.  It also allows the 
// app to change the BehaviorFlags.  The BehaviorFlags defaults non-pure HWVP 
// if supported otherwise it will default to SWVP, however the app can change this 
// through the ConfirmDevice callback.
//--------------------------------------------------------------------------------------
_Use_decl_annotations_
HRESULT CD3D11Enumeration::Enumerate( LPDXUTCALLBACKISD3D11DEVICEACCEPTABLE IsD3D11DeviceAcceptableFunc,
                                      void* pIsD3D11DeviceAcceptableFuncUserContext )
{
    CDXUTPerfEventGenerator eventGenerator( DXUT_PERFEVENTCOLOR, L"DXUT D3D11 Enumeration" );
    HRESULT hr;
    IDXGIFactory1* pFactory = DXUTGetDXGIFactory();
    if( !pFactory )
        return E_FAIL;

    m_bHasEnumerated = true;
    m_IsD3D11DeviceAcceptableFunc = IsD3D11DeviceAcceptableFunc;
    m_pIsD3D11DeviceAcceptableFuncUserContext = pIsD3D11DeviceAcceptableFuncUserContext;

    ClearAdapterInfoList();

    for( int index = 0; ; ++index )
    {
        IDXGIAdapter* pAdapter = nullptr;
        hr = pFactory->EnumAdapters( index, &pAdapter );
        if( FAILED( hr ) ) // DXGIERR_NOT_FOUND is expected when the end of the list is hit
            break;

        IDXGIAdapter2* pAdapter2 = nullptr;
        if ( SUCCEEDED( pAdapter->QueryInterface( __uuidof(IDXGIAdapter2), ( LPVOID* )&pAdapter2 ) ) )
        {
            // Succeeds on DirectX 11.1 Runtime systems
            DXGI_ADAPTER_DESC2 desc;
            hr = pAdapter2->GetDesc2( &desc );
            pAdapter2->Release();

            if ( SUCCEEDED(hr) && ( desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE ) )
            {
                // Skip "always there" Microsoft Basics Display Driver
                pAdapter->Release();
                continue;
            }
        }

        CD3D11EnumAdapterInfo* pAdapterInfo = new (std::nothrow) CD3D11EnumAdapterInfo;
        if( !pAdapterInfo )
        {
            SAFE_RELEASE( pAdapter );
            return E_OUTOFMEMORY;
        }
        pAdapterInfo->AdapterOrdinal = index;
        pAdapter->GetDesc( &pAdapterInfo->AdapterDesc );
        pAdapterInfo->m_pAdapter = pAdapter;

        // Enumerate the device driver types on the adapter.
        hr = EnumerateDevices( pAdapterInfo );
        if( FAILED( hr ) )
        {
            delete pAdapterInfo;
            continue;
        }

        hr = EnumerateOutputs( pAdapterInfo );
        if( FAILED( hr ) || pAdapterInfo->outputInfoList.empty() )
        {
            delete pAdapterInfo;
            continue;
        }

        // Get info for each devicecombo on this device
        if( FAILED( hr = EnumerateDeviceCombos( pAdapterInfo ) ) )
        {
            delete pAdapterInfo;
            continue;
        }

        m_AdapterInfoList.push_back( pAdapterInfo );
    }

    //  If we did not get an adapter then we should still enumerate WARP and Ref.
    if (m_AdapterInfoList.size() == 0)
    {
        CD3D11EnumAdapterInfo* pAdapterInfo = new (std::nothrow) CD3D11EnumAdapterInfo;
        if( !pAdapterInfo )
        {
            return E_OUTOFMEMORY;
        }
        pAdapterInfo->bAdapterUnavailable = true;

        hr = EnumerateDevices( pAdapterInfo );

        // Get info for each devicecombo on this device
        if( FAILED( hr = EnumerateDeviceCombosNoAdapter(  pAdapterInfo ) ) )
        {
            delete pAdapterInfo;
        }

        if (SUCCEEDED(hr)) m_AdapterInfoList.push_back( pAdapterInfo );
    }

    //
    // Check for 2 or more adapters with the same name. Append the name
    // with some instance number if that's the case to help distinguish
    // them.
    //
    bool bUniqueDesc = true;
    for( size_t i = 0; i < m_AdapterInfoList.size(); i++ )
    {
        auto pAdapterInfo1 = m_AdapterInfoList[ i ];

        for( size_t j = i + 1; j < m_AdapterInfoList.size(); j++ )
        {
            auto pAdapterInfo2 = m_AdapterInfoList[ j ];
            if( wcsncmp( pAdapterInfo1->AdapterDesc.Description,
                pAdapterInfo2->AdapterDesc.Description, DXGI_MAX_DEVICE_IDENTIFIER_STRING ) == 0 )
            {
                bUniqueDesc = false;
                break;
            }
        }

        if( !bUniqueDesc )
            break;
    }

    for( auto it = m_AdapterInfoList.begin(); it != m_AdapterInfoList.end(); ++it )
    {
        wcscpy_s( (*it)->szUniqueDescription, 100, (*it)->AdapterDesc.Description );
        if( !bUniqueDesc )
        {
            WCHAR sz[100];
            swprintf_s( sz, 100, L" (#%u)", (*it)->AdapterOrdinal );
            wcscat_s( (*it)->szUniqueDescription, DXGI_MAX_DEVICE_IDENTIFIER_STRING, sz );
        }
    }

    D3D_FEATURE_LEVEL fLvl[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };

    // Check WARP max feature level
    {
        ID3D11Device* pDevice = nullptr;
        hr = DXUT_Dynamic_D3D11CreateDevice( nullptr, D3D_DRIVER_TYPE_WARP, 0, 0, fLvl, _countof(fLvl),
                                             D3D11_SDK_VERSION, &pDevice, &m_warpFL, nullptr );
        if ( hr == E_INVALIDARG )
        {
            // DirectX 11.0 runtime will not recognize FL 11.1, so try without it
            hr = DXUT_Dynamic_D3D11CreateDevice( nullptr, D3D_DRIVER_TYPE_WARP, 0, 0, &fLvl[1], _countof(fLvl) - 1,
                                                 D3D11_SDK_VERSION, &pDevice, &m_warpFL, nullptr );
        }

        if ( SUCCEEDED(hr) )
        {
            pDevice->Release();
        }
        else
            m_warpFL = D3D_FEATURE_LEVEL_10_1;
    }

    // Check REF max feature level
    {
        ID3D11Device* pDevice = nullptr;
        hr = DXUT_Dynamic_D3D11CreateDevice( nullptr, D3D_DRIVER_TYPE_REFERENCE, 0, 0, fLvl, _countof(fLvl),
                                             D3D11_SDK_VERSION, &pDevice, &m_refFL, nullptr );
        if ( hr == E_INVALIDARG )
        {
            // DirectX 11.0 runtime will not recognize FL 11.1, so try without it
            hr = DXUT_Dynamic_D3D11CreateDevice( nullptr, D3D_DRIVER_TYPE_REFERENCE, 0, 0, &fLvl[1], _countof(fLvl) - 1,
                                                 D3D11_SDK_VERSION, &pDevice, &m_refFL, nullptr );
        }

        if ( SUCCEEDED(hr) )
        {
            pDevice->Release();
        }
        else
            m_refFL = D3D_FEATURE_LEVEL_11_0;
    }

    return S_OK;
}