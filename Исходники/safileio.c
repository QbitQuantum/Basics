int SAUtf8WRemove( const char *pszFilename )
{
    const wchar_t *pwszFileName = Utf8ToWideChar( pszFilename );
    int rc = -1; 
    if( pwszFileName != NULL )
    {
        rc = _wremove( pwszFileName );
    }
    free ((wchar_t*) pwszFileName);
    return rc;
}