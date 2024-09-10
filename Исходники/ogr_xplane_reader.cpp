int OGRXPlaneReader::StartParsing( const char * pszFilename )
{
    fp = VSIFOpen( pszFilename, "rt" );
    if (fp == NULL)
        return FALSE;

    const char* pszLine = CPLReadLine(fp);
    if (!pszLine || (strcmp(pszLine, "I") != 0 &&
                     strcmp(pszLine, "A") != 0))
    {
        VSIFClose(fp);
        fp = NULL;
        return FALSE;
    }

    pszLine = CPLReadLine(fp);
    if (!pszLine || IsRecognizedVersion(pszLine) == FALSE)
    {
        VSIFClose(fp);
        fp = NULL;
        return FALSE;
    }

    CPLFree(this->pszFilename);
    this->pszFilename = CPLStrdup(pszFilename);

    nLineNumber = 2;
    CPLDebug("XPlane", "Version/Copyright : %s", pszLine);

    Rewind();

    return TRUE;
}