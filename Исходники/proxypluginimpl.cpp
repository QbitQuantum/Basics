/////////////////////////////////////////////////////////////////////////////
//
// [OnGetContentInformation]
//
// IWMSCacheProxyServerCallback
//
/////////////////////////////////////////////////////////////////////////////
HRESULT STDMETHODCALLTYPE 
CProxyPlugin::OnGetContentInformation(
                    long lHr,
                    IWMSContext *pContentInfo,
                    VARIANT varContext
                    )
{
    HRESULT returnHr = (HRESULT) lHr;
    HRESULT hr = S_OK;
    COpState *pOpState = NULL;
    WMS_CACHE_QUERY_MISS_RESPONSE CacheMissPolicy = WMS_CACHE_QUERY_MISS_SKIP;
    IWMSDataContainerVersion *pContentVersion = NULL;
    CComBSTR bstrUrl;
    BOOL fDownload = FALSE;
    long lContentType = 0;
    DWORD dwCacheFlags;
    WCHAR szPort[ 20 ];

    if( ( VT_UNKNOWN != V_VT( &varContext ) ) || 
        ( NULL == V_UNKNOWN( &varContext ) ) )
    {
        return( E_INVALIDARG );
    }

    pOpState = ( COpState *) V_UNKNOWN( &varContext );

    if( FAILED( returnHr ) )
    {
        if( NS_E_CONNECTION_FAILURE == returnHr )
        {
            // Do protocol rollover
            pOpState->m_dwProtocolIndex++;

            if( NULL == g_ProxyProtocols[ pOpState->m_dwProtocolIndex ] )
            {
                // we have tried all the protocols and failed
                hr = E_NOINTERFACE;
                goto abort;
            }

            bstrUrl = g_ProxyProtocols[ pOpState->m_dwProtocolIndex ];
            bstrUrl.Append( L"://" );
            bstrUrl.Append( pOpState->m_bstrHost );
            
            // if we we are using the same protocol requested by the client, then we should
            // also use the port specified by the client (if one was specified)
            if( ( 0 != pOpState->m_wPort ) &&
                ( 0 == _wcsicmp( g_ProxyProtocols[ pOpState->m_dwProtocolIndex ], pOpState->m_bstrProtocol ) ) )
            {
                bstrUrl.Append( L":" );
				_itow_s( pOpState->m_wPort, szPort,sizeof(szPort)/sizeof(WCHAR), 10 );
                bstrUrl.Append( szPort );
            }

            bstrUrl.Append( L"/" );
            bstrUrl.Append( pOpState->m_bstrPath );

            hr = m_pICacheProxyServer->GetContentInformation(
                                            bstrUrl,
                                            pOpState->m_pPresentationContext,
                                            this,
                                            NULL,
                                            (IWMSCacheProxyServerCallback *) this,
                                            varContext
                                            );
            if( FAILED( hr ) )
            {
                goto abort;
            }

            return( S_OK );
        }
        else if( E_ACCESSDENIED == returnHr )
        {
            // the origin server requires authentication to provide information about this content.
            // since we don't have the credentials, we can either proxy this stream on-demand (in
            // which case the player will be prompted for the credentials) or simply fail this request.
            // let's opt for proxying the stream.
            CacheMissPolicy = WMS_CACHE_QUERY_MISS_PLAY_ON_DEMAND;
        }
        else
        {
            hr = returnHr;
            goto abort;
        }
    }
    else
    {
        hr = pContentInfo->GetLongValue( WMS_CACHE_CONTENT_INFORMATION_CONTENT_TYPE,
                                         WMS_CACHE_CONTENT_INFORMATION_CONTENT_TYPE_ID,
                                         (long *) &lContentType,
                                         0 );
        if( FAILED( hr ) )
        {
            goto abort;
        }
        
        if( WMS_CACHE_CONTENT_TYPE_BROADCAST & lContentType )
        {
            hr = pContentInfo->GetAndQueryIUnknownValue( WMS_CACHE_CONTENT_INFORMATION_DATA_CONTAINER_VERSION,
                                                         WMS_CACHE_CONTENT_INFORMATION_DATA_CONTAINER_VERSION_ID,
                                                         IID_IWMSDataContainerVersion,
                                                         (IUnknown **) &pContentVersion,
                                                         0 );
            if( ( FAILED( hr ) ) || ( NULL == pContentVersion ) )
            {
                hr = FAILED( hr ) ? hr : E_UNEXPECTED;
                goto abort;
            }

            hr = pContentVersion->GetCacheFlags( (long *) &dwCacheFlags );
            if( FAILED( hr ) )
            {
                goto abort;
            }

            if( dwCacheFlags & WMS_DATA_CONTAINER_VERSION_ALLOW_STREAM_SPLITTING )
            {
                CacheMissPolicy = WMS_CACHE_QUERY_MISS_PLAY_BROADCAST;
            }
            else
            {
                CacheMissPolicy = WMS_CACHE_QUERY_MISS_PLAY_ON_DEMAND;
            }
        }
        else  // It is an on-demand publishing point
        {
            CacheMissPolicy = WMS_CACHE_QUERY_MISS_PLAY_ON_DEMAND;
        }
    }

    hr = S_OK;

    bstrUrl = g_ProxyProtocols[ pOpState->m_dwProtocolIndex ];
    bstrUrl.Append( L"://" );
    bstrUrl.Append( pOpState->m_bstrHost );
    
    // if we we are using the same protocol requested by the client, then we should
    // also use the port specified by the client (if one was specified)
    if( ( 0 != pOpState->m_wPort ) &&
        ( 0 == _wcsicmp( g_ProxyProtocols[ pOpState->m_dwProtocolIndex ], pOpState->m_bstrProtocol ) ) )
    {
        bstrUrl.Append( L":" );
		_itow_s( pOpState->m_wPort, szPort,sizeof(szPort)/sizeof(WCHAR), 10 );
        bstrUrl.Append( szPort );
    }

    bstrUrl.Append( L"/" );
    bstrUrl.Append( pOpState->m_bstrPath );

abort:
    hr = pOpState->m_pCacheProxyCallback->OnQueryCacheMissPolicy( hr,
                                                                  CacheMissPolicy,
                                                                  bstrUrl,
                                                                  NULL,
                                                                  pContentInfo,
                                                                  pOpState->m_varContext );
    if( FAILED( hr ) )
    {
        hr = S_OK;
    }

    if( NULL != pOpState )
    {
        pOpState->Release();
    }

    if( NULL != pContentVersion )
    {
        pContentVersion->Release();
    }

    return( S_OK );
}