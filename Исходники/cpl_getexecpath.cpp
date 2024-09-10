int CPLGetExecPath( char *pszPathBuf, int nMaxLength )
{
    long nPID = getpid();
    CPLString osExeLink;

    osExeLink.Printf( "/proc/%ld/exe", nPID );
    ssize_t nResultLen = readlink( osExeLink, pszPathBuf, nMaxLength );
    if( nResultLen >= 0 )
        pszPathBuf[nResultLen] = '\0';
    else
        pszPathBuf[0] = '\0';

    return nResultLen > 0;
}