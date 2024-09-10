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
HRESULT CD3D9Enumeration::Enumerate( LPDXUTCALLBACKISD3D9DEVICEACCEPTABLE IsD3D9DeviceAcceptableFunc,
                                     void* pIsD3D9DeviceAcceptableFuncUserContext )
{
    CDXUTPerfEventGenerator eventGenerator( DXUT_PERFEVENTCOLOR, L"DXUT D3D9 Enumeration" );
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( pD3D == NULL )
    {
        pD3D = DXUTGetD3D9Object();
        if( pD3D == NULL )
            return DXUTERR_NODIRECT3D;
    }

    m_bHasEnumerated = true;
    m_pD3D = pD3D;
    m_IsD3D9DeviceAcceptableFunc = IsD3D9DeviceAcceptableFunc;
    m_pIsD3D9DeviceAcceptableFuncUserContext = pIsD3D9DeviceAcceptableFuncUserContext;

    HRESULT hr;
    ClearAdapterInfoList();
    CGrowableArray <D3DFORMAT> adapterFormatList;

    const D3DFORMAT allowedAdapterFormatArray[] =
    {
        D3DFMT_X8R8G8B8,
        D3DFMT_X1R5G5B5,
        D3DFMT_R5G6B5,
        D3DFMT_A2R10G10B10
    };
    const UINT allowedAdapterFormatArrayCount = sizeof( allowedAdapterFormatArray ) / sizeof
        ( allowedAdapterFormatArray[0] );

    UINT numAdapters = pD3D->GetAdapterCount();
    for( UINT adapterOrdinal = 0; adapterOrdinal < numAdapters; adapterOrdinal++ )
    {
        CD3D9EnumAdapterInfo* pAdapterInfo = new CD3D9EnumAdapterInfo;
        if( pAdapterInfo == NULL )
            return E_OUTOFMEMORY;

        pAdapterInfo->AdapterOrdinal = adapterOrdinal;
        pD3D->GetAdapterIdentifier( adapterOrdinal, 0, &pAdapterInfo->AdapterIdentifier );

        // Get list of all display modes on this adapter.  
        // Also build a temporary list of all display adapter formats.
        adapterFormatList.RemoveAll();

        for( UINT iFormatList = 0; iFormatList < allowedAdapterFormatArrayCount; iFormatList++ )
        {
            D3DFORMAT allowedAdapterFormat = allowedAdapterFormatArray[iFormatList];
            UINT numAdapterModes = pD3D->GetAdapterModeCount( adapterOrdinal, allowedAdapterFormat );
            for( UINT mode = 0; mode < numAdapterModes; mode++ )
            {
                D3DDISPLAYMODE displayMode;
                pD3D->EnumAdapterModes( adapterOrdinal, allowedAdapterFormat, mode, &displayMode );

                if( displayMode.Width < m_nMinWidth ||
                    displayMode.Height < m_nMinHeight ||
                    displayMode.Width > m_nMaxWidth ||
                    displayMode.Height > m_nMaxHeight ||
                    displayMode.RefreshRate < m_nRefreshMin ||
                    displayMode.RefreshRate > m_nRefreshMax )
                {
                    continue;
                }

                pAdapterInfo->displayModeList.Add( displayMode );

                if( !adapterFormatList.Contains( displayMode.Format ) )
                    adapterFormatList.Add( displayMode.Format );
            }

        }

        D3DDISPLAYMODE displayMode;
        pD3D->GetAdapterDisplayMode( adapterOrdinal, &displayMode );
        if( !adapterFormatList.Contains( displayMode.Format ) )
            adapterFormatList.Add( displayMode.Format );

        // Sort displaymode list
        qsort( pAdapterInfo->displayModeList.GetData(),
               pAdapterInfo->displayModeList.GetSize(), sizeof( D3DDISPLAYMODE ),
               SortModesCallback );

        // Get info for each device on this adapter
        if( FAILED( EnumerateDevices( pAdapterInfo, &adapterFormatList ) ) )
        {
            delete pAdapterInfo;
            continue;
        }

        // If at least one device on this adapter is available and compatible
        // with the app, add the adapterInfo to the list
        if( pAdapterInfo->deviceInfoList.GetSize() > 0 )
        {
            hr = m_AdapterInfoList.Add( pAdapterInfo );
            if( FAILED( hr ) )
                return hr;
        }
        else
            delete pAdapterInfo;
    }

    //
    // Check for 2 or more adapters with the same name. Append the name
    // with some instance number if that's the case to help distinguish
    // them.
    //
    bool bUniqueDesc = true;
    CD3D9EnumAdapterInfo* pAdapterInfo;
    for( int i = 0; i < m_AdapterInfoList.GetSize(); i++ )
    {
        CD3D9EnumAdapterInfo* pAdapterInfo1 = m_AdapterInfoList.GetAt( i );

        for( int j = i + 1; j < m_AdapterInfoList.GetSize(); j++ )
        {
            CD3D9EnumAdapterInfo* pAdapterInfo2 = m_AdapterInfoList.GetAt( j );
            if( _stricmp( pAdapterInfo1->AdapterIdentifier.Description,
                          pAdapterInfo2->AdapterIdentifier.Description ) == 0 )
            {
                bUniqueDesc = false;
                break;
            }
        }

        if( !bUniqueDesc )
            break;
    }

    for( int i = 0; i < m_AdapterInfoList.GetSize(); i++ )
    {
        pAdapterInfo = m_AdapterInfoList.GetAt( i );

        MultiByteToWideChar( CP_ACP, 0,
                             pAdapterInfo->AdapterIdentifier.Description, -1,
                             pAdapterInfo->szUniqueDescription, 100 );
        pAdapterInfo->szUniqueDescription[100] = 0;

        if( !bUniqueDesc )
        {
            WCHAR sz[100];
            swprintf_s( sz, 100, L" (#%d)", pAdapterInfo->AdapterOrdinal );
            wcscat_s( pAdapterInfo->szUniqueDescription, 256, sz );

        }
    }

    return S_OK;
}