FX_WINOLEAUTAPI_(FX_BSTR) FX_SysAllocStringA( const char* pSrc )
{
    // check for null argument
    // if NULL, defer to wide character version
    if ( !pSrc ) 
        return FX_SysAllocString( 0 );

    // get length of the wchar_t string
    mbstate_t state;
    memset( &state, 0, sizeof(state) );
    char const* tmp = pSrc;
    size_t wl = mbsrtowcs( NULL, &tmp, 0, &state );

    // create the buffer
    FX_BSTR bstr = FX_SysAllocStringLen( 0, (uint16_t)wl );
    if ( !bstr ) return 0;

    // copy the buffer
    memset( &state, 0, sizeof(state) );
    tmp = pSrc;
    size_t wl2 = mbsrtowcs( const_cast<wchar_t*>(bstr), &tmp, wl, &state );
    assert( wl == wl2 );
    wl2 = wl2; //avoid warning in release mode
    return bstr;
}