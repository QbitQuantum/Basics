STDMETHODIMP CSOActiveX::SetClientSite( IOleClientSite* aClientSite )
{
    HRESULT hr = IOleObjectImpl<CSOActiveX>::SetClientSite( aClientSite );

    if( !aClientSite )
    {
        ATLASSERT( mWebBrowser2 );
        if( mWebBrowser2 )
            AtlUnadvise( mWebBrowser2, DIID_DWebBrowserEvents2, mCookie );
        return hr;
    }

    CComPtr<IOleContainer> aContainer;
    m_spClientSite->GetContainer( &aContainer );
    ATLASSERT( aContainer );

    if( SUCCEEDED( hr )  && aContainer )
    {
        CComQIPtr<IServiceProvider, &IID_IServiceProvider> aServiceProvider( aContainer );
        ATLASSERT( aServiceProvider );

        if( aServiceProvider )
        {
            aServiceProvider->QueryService( SID_SInternetExplorer,
                                            IID_IWebBrowser,
                                            (void**)&mWebBrowser2 );
            ATLASSERT( mWebBrowser2 );
            if( mWebBrowser2 )
                AtlAdvise( mWebBrowser2, GetUnknown(), DIID_DWebBrowserEvents2, &mCookie );
        }
    }

    return hr;
}