HRESULT CReader::Open( const TCHAR *ptszFile )
{

    HRESULT hr = S_OK;


    if ( NULL == ptszFile || NULL == _tcslen(ptszFile))
    {
        return( E_INVALIDARG );
    }

    //
    //  Currently we can play only files. Streams are not supported.
    //
    if( 0 == _tcsnicmp( ptszFile, TEXT( "http" ), 4 ) )
    {
        _tprintf( _T( "Wrong input file - streams are not supported : (hr=0x%08x).\n" ) ,hr );
        return( E_INVALIDARG );
    }

    if ( NULL == m_pReader )
    {
        hr = WMCreateSyncReader(  NULL, 0, &m_pReader );
    }

    if ( FAILED( hr ) )
    {
        _tprintf( _T( "Could not create reader (hr=0x%08x).\n" ), hr );
        return( hr );
    }

    //
    // Open the requested file using IStream just to show how to use IStream with the synchronous reader 
    //
	m_pStream = new CROStream;
	if( NULL == m_pStream )
	{
		hr = E_OUTOFMEMORY;
        _tprintf( _T( "Could not open file (hr=0x%08x).\n" ), hr );
		return( hr );
	}

    hr = m_pStream->Open( ptszFile );
    
    if( FAILED( hr ) )
    {
        _tprintf( _T( "Could not open file (hr=0x%08x).\n" ) ,hr );
        return( hr );
    }

    hr = m_pReader->OpenStream( m_pStream );
    if ( FAILED( hr ) )
    {
        _tprintf( _T( "Could not open file (hr=0x%08x).\n" ), hr );
        return( hr );
    }
    
    //
    // Get the profile interface
    //
    IWMProfile*    pProfile = NULL;

    hr = m_pReader->QueryInterface( IID_IWMProfile, ( VOID ** )&pProfile );
    if ( FAILED( hr ) ) 
    {
        _tprintf( _T(  "Could not QI for IWMProfile (hr=0x%08x).\n" ), hr );
        return( hr );
    }

    //
    // Find out stream numbers for video and audio using the profile
    //
    hr = GetStreamNumbers( pProfile );
    SAFE_RELEASE( pProfile );
    if ( FAILED( hr ) ) 
    {
        _tprintf( _T(  "Could not stream numbers (hr=0x%08x).\n" ), hr );
        return( hr );
    }

    return( hr );
}