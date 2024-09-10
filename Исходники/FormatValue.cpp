    template <> int Translate( 
        wchar_t* srcBuf, 
        size_t srcCharLen, 
        wchar_t* destBuf, 
        size_t destCharLen )
    {
        if ( destCharLen > 0 )
        {
            _ASSERT( destBuf != NULL );

            srcCharLen = std::min( srcCharLen, destCharLen );

            errno_t err = wmemcpy_s( destBuf, srcCharLen, srcBuf, srcCharLen );
            _ASSERT( err == 0 );
            UNREFERENCED_PARAMETER( err );
        }
        return srcCharLen;
    }