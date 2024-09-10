long PdfOutputDevice::PrintVLen( const char* pszFormat, va_list args )
{
    long    lBytes;

    if( !pszFormat )
    {
        PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
    }

    if( m_hFile )
    {
        if( (lBytes = vfprintf( m_hFile, pszFormat, args )) < 0 )
        {
            perror( NULL );
            PODOFO_RAISE_ERROR( ePdfError_UnexpectedEOF );
        }
    }
    else
    {
        // OC 17.08.2010: Use new function _vscprintf to get the number of characters:
        // visual c++  8.0 == 1400 (Visual Studio 2005)
        // i am not shure if 1300 is ok here, but who cares this cruel compiler version
#if (defined _MSC_VER && _MSC_VER >= 1400 )
        lBytes = _vscprintf( pszFormat, args );
#elif (defined _MSC_VER || defined __hpux)  // vsnprintf without buffer does not work with MS-VC or HPUX
        int len = 1024;
        do
        {
            char * temp = new char[len+1]; // OC 17.08.2010 BugFix: +1 avoids corrupted heap
            lBytes = vsnprintf( temp, len+1, pszFormat, args );
            delete[] temp;
            len *= 2;
        } while (lBytes < 0 );
#else
        lBytes = vsnprintf( NULL, 0, pszFormat, args );
#endif
    }

    return lBytes;
}