int VSIWin32FilesystemHandler::Stat( const char * pszFilename, 
                                     VSIStatBufL * pStatBuf,
                                     int nFlags )

{
    (void) nFlags;

#if (defined(WIN32) && _MSC_VER >= 1310) || __MSVCRT_VERSION__ >= 0x0601
    if( CSLTestBoolean(
            CPLGetConfigOption( "GDAL_FILENAME_IS_UTF8", "YES" ) ) )
    {
        int nResult;
        wchar_t *pwszFilename = 
            CPLRecodeToWChar( pszFilename, CPL_ENC_UTF8, CPL_ENC_UCS2 );

        nResult = _wstat64( pwszFilename, pStatBuf );
        CPLFree( pwszFilename );

        return nResult;
    }
    else
#endif
    {
        return( VSI_STAT64( pszFilename, pStatBuf ) );
    }
}