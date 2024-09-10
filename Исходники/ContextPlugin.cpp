STDMETHODIMP CContextPlugin::GetCustomAdminInterface( IDispatch **ppValue )
{
    HRESULT hr = S_OK;

    if ( ( NULL == ppValue ) )
    {
        return( E_POINTER );
    }
    
    *ppValue = NULL;

    CComObject< CContextAdmin > *spContextAdmin;

    hr = CComObject< CContextAdmin >::CreateInstance( &spContextAdmin );
    if( SUCCEEDED( hr ) )
    {
        CComPtr< IDispatch > spAdmin( spContextAdmin );
        hr = spContextAdmin->Initialize( this );
        if ( SUCCEEDED( hr ) )
        {
            hr = spContextAdmin->QueryInterface( IID_IDispatch, (void **) ppValue );
        }
    }

    return( hr );
}