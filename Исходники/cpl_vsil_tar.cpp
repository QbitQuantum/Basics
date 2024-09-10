VSIVirtualHandle* VSITarFilesystemHandler::Open( const char *pszFilename, 
                                                 const char *pszAccess)
{
    char* tarFilename;
    CPLString osTarInFileName;

    if (strchr(pszAccess, 'w') != NULL ||
        strchr(pszAccess, '+') != NULL)
    {
        CPLError(CE_Failure, CPLE_AppDefined,
                 "Only read-only mode is supported for /vsitar");
        return NULL;
    }

    tarFilename = SplitFilename(pszFilename, osTarInFileName, TRUE);
    if (tarFilename == NULL)
        return NULL;

    VSIArchiveReader* poReader = OpenArchiveFile(tarFilename, osTarInFileName);
    if (poReader == NULL)
    {
        CPLFree(tarFilename);
        return NULL;
    }

    CPLString osSubFileName("/vsisubfile/");
    VSITarEntryFileOffset* pOffset = (VSITarEntryFileOffset*) poReader->GetFileOffset();
    osSubFileName += CPLString().Printf(CPL_FRMT_GUIB, pOffset->nOffset);
    osSubFileName += "_";
    osSubFileName += CPLString().Printf(CPL_FRMT_GUIB, poReader->GetFileSize());
    osSubFileName += ",";
    delete pOffset;
    
    if (VSIIsTGZ(tarFilename))
    {
        osSubFileName += "/vsigzip/";
        osSubFileName += tarFilename;
    }
    else
        osSubFileName += tarFilename;

    delete(poReader);

    CPLFree(tarFilename);
    tarFilename = NULL;

    return (VSIVirtualHandle* )VSIFOpenL(osSubFileName, "rb");
}