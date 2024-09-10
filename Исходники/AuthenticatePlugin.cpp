STDMETHODIMP CAuthenticatePlugin::GetCustomAdminInterface
(
    IDispatch **ppValue
)
{
    if( ( NULL == ppValue ) )
    {
        return( E_POINTER );
    }

    HRESULT hr = S_OK;

    *ppValue = NULL;

    CComObject<CAuthenticateAdmin> *pAuthenticateAdmin = NULL;

    hr = CComObject<CAuthenticateAdmin>::CreateInstance( &pAuthenticateAdmin );

    if( SUCCEEDED( hr ) )
    {
        pAuthenticateAdmin->AddRef();
        hr = pAuthenticateAdmin->Initialize( this );
    }

    if( SUCCEEDED(hr) )
    {
        hr = pAuthenticateAdmin->QueryInterface( IID_IDispatch, (void **) ppValue );
    }

    if( NULL != pAuthenticateAdmin )
    {
        pAuthenticateAdmin->Release();
    }

    return( hr );
}