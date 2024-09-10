/***********************************************************************
 *           AtlAxCreateControlEx            [atl100.@]
 *
 * REMARKS
 *   See http://www.codeproject.com/com/cwebpage.asp for some background
 *
 */
HRESULT WINAPI AtlAxCreateControlEx(LPCOLESTR lpszName, HWND hWnd,
        IStream *pStream, IUnknown **ppUnkContainer, IUnknown **ppUnkControl,
        REFIID iidSink, IUnknown *punkSink)
{
    CLSID controlId;
    HRESULT hRes;
    IOleObject *pControl;
    IUnknown *pUnkControl;
    IPersistStreamInit *pPSInit;
    IUnknown *pContainer;
    enum {IsGUID=0,IsHTML=1,IsURL=2} content;

    TRACE("(%s %p %p %p %p %p %p)\n", debugstr_w(lpszName), hWnd, pStream,
            ppUnkContainer, ppUnkControl, iidSink, punkSink);

    hRes = CLSIDFromString( lpszName, &controlId );
    if ( FAILED(hRes) )
        hRes = CLSIDFromProgID( lpszName, &controlId );
    if ( SUCCEEDED( hRes ) )
        content = IsGUID;
    else {
        /* FIXME - check for MSHTML: prefix! */
        content = IsURL;
        controlId = CLSID_WebBrowser;
    }

    hRes = CoCreateInstance( &controlId, 0, CLSCTX_ALL, &IID_IOleObject,
            (void**) &pControl );
    if ( FAILED( hRes ) )
    {
        WARN( "cannot create ActiveX control %s instance - error 0x%08x\n",
                debugstr_guid( &controlId ), hRes );
        return hRes;
    }

    hRes = IOleObject_QueryInterface( pControl, &IID_IPersistStreamInit, (void**) &pPSInit );
    if ( SUCCEEDED( hRes ) )
    {
        if (!pStream)
            IPersistStreamInit_InitNew( pPSInit );
        else
            IPersistStreamInit_Load( pPSInit, pStream );
        IPersistStreamInit_Release( pPSInit );
    } else
        WARN("cannot get IID_IPersistStreamInit out of control\n");

    IOleObject_QueryInterface( pControl, &IID_IUnknown, (void**) &pUnkControl );
    IOleObject_Release( pControl );


    hRes = AtlAxAttachControl( pUnkControl, hWnd, &pContainer );
    if ( FAILED( hRes ) )
        WARN("cannot attach control to window\n");

    if ( content == IsURL )
    {
        IWebBrowser2 *browser;

        hRes = IOleObject_QueryInterface( pControl, &IID_IWebBrowser2, (void**) &browser );
        if ( !browser )
            WARN( "Cannot query IWebBrowser2 interface: %08x\n", hRes );
        else {
            VARIANT url;

            IWebBrowser2_put_Visible( browser, VARIANT_TRUE ); /* it seems that native does this on URL (but do not on MSHTML:! why? */

            V_VT(&url) = VT_BSTR;
            V_BSTR(&url) = SysAllocString( lpszName );

            hRes = IWebBrowser2_Navigate2( browser, &url, NULL, NULL, NULL, NULL );
            if ( FAILED( hRes ) )
                WARN( "IWebBrowser2::Navigate2 failed: %08x\n", hRes );
            SysFreeString( V_BSTR(&url) );

            IWebBrowser2_Release( browser );
        }
    }

    if (ppUnkContainer)
    {
        *ppUnkContainer = pContainer;
        if ( pContainer )
            IUnknown_AddRef( pContainer );
    }
    if (ppUnkControl)
    {
        *ppUnkControl = pUnkControl;
        if ( pUnkControl )
            IUnknown_AddRef( pUnkControl );
    }

    if ( pUnkControl )
        IUnknown_Release( pUnkControl );
    if ( pContainer )
        IUnknown_Release( pContainer );

    return S_OK;
}