int VSIStatExL( const char * pszFilename, VSIStatBufL *psStatBuf, int nFlags )

{
    char    szAltPath[4];
    /* enable to work on "C:" as if it were "C:\" */
    if( strlen(pszFilename) == 2 && pszFilename[1] == ':' )
    {
        szAltPath[0] = pszFilename[0];
        szAltPath[1] = pszFilename[1];
        szAltPath[2] = '\\';
        szAltPath[3] = '\0';

        pszFilename = szAltPath;
    }

    VSIFilesystemHandler *poFSHandler =
        VSIFileManager::GetHandler( pszFilename );

    if (nFlags == 0)
        nFlags = VSI_STAT_EXISTS_FLAG | VSI_STAT_NATURE_FLAG | VSI_STAT_SIZE_FLAG;

    return poFSHandler->Stat( pszFilename, psStatBuf, nFlags );
}