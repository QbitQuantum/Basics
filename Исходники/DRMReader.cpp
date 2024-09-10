//------------------------------------------------------------------------------
// Name: CLicenseViewer::Initialize()
// Desc: Initialization.
//------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CLicenseViewer::Initialize()
{
    HRESULT hr = S_OK;

    do
    {
        //
        // Reset the m_hr variable
        //
        m_hr = S_OK;

        //
        // Create callback event, if it doesn't already exist
        //
        if ( NULL == m_hEvent )
        {
            m_hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
            if ( !m_hEvent )
            {
                hr = HRESULT_FROM_WIN32( ::GetLastError() );
                _tprintf( _T( "CreateEvent failed 0x%08lX\n" ), hr );
                break;
            }
        }
    
        //
        // Create a Reader and get the DRM reader interface
        //
        if ( NULL == m_pIWMReader )
        {
            hr = WMCreateReader( NULL, 0, &m_pIWMReader ); 
            if ( FAILED( hr ) || NULL == m_pIWMReader )
            {
                hr = E_FAIL;
                _tprintf( _T( "Failed to create WMReader 0x%08lX\n" ), hr );
                break;
            }

            SAFE_RELEASE( m_pIWMDRMReader );
            assert( m_pIWMReader );
        	hr = m_pIWMReader->QueryInterface( IID_IWMDRMReader, ( void **)&m_pIWMDRMReader );
            if ( FAILED( hr ) )
            {
                _tprintf( _T( "Failed to QI for DRM Reader interface 0x%08lX\n" ), hr );
                break;
            }
        }
    }
    while ( FALSE );
    
    return hr;
}