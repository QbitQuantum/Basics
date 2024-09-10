char* VSIArchiveFilesystemHandler::SplitFilename(const char *pszFilename,
                                                 CPLString &osFileInArchive,
                                                 int bCheckMainFileExists)
{
    int i = 0;

    if (strcmp(pszFilename, GetPrefix()) == 0)
        return NULL;

    /* Allow natural chaining of VSI drivers without requiring double slash */
    
    CPLString osDoubleVsi(GetPrefix());
    osDoubleVsi += "/vsi";
    
    if (strncmp(pszFilename, osDoubleVsi.c_str(), osDoubleVsi.size()) == 0)
        pszFilename += strlen(GetPrefix());
    else
        pszFilename += strlen(GetPrefix()) + 1;

    while(pszFilename[i])
    {
        std::vector<CPLString> oExtensions = GetExtensions();
        std::vector<CPLString>::const_iterator iter;
        int nToSkip = 0;

        for( iter = oExtensions.begin(); iter != oExtensions.end(); ++iter )
        {
            const CPLString& osExtension = *iter;
            if (EQUALN(pszFilename + i, osExtension.c_str(), strlen(osExtension.c_str())))
            {
                nToSkip = strlen(osExtension.c_str());
                break;
            }
        }

        if (nToSkip != 0)
        {
            VSIStatBufL statBuf;
            char* archiveFilename = CPLStrdup(pszFilename);
            int bArchiveFileExists = FALSE;

            if (archiveFilename[i + nToSkip] == '/' ||
                archiveFilename[i + nToSkip] == '\\')
            {
                archiveFilename[i + nToSkip] = 0;
            }

            if (!bCheckMainFileExists)
            {
                bArchiveFileExists = TRUE;
            }
            else
            {
                CPLMutexHolder oHolder( &hMutex );

                if (oFileList.find(archiveFilename) != oFileList.end() )
                {
                    bArchiveFileExists = TRUE;
                }
            }

            if (!bArchiveFileExists)
            {
                VSIFilesystemHandler *poFSHandler = 
                    VSIFileManager::GetHandler( archiveFilename );
                if (poFSHandler->Stat(archiveFilename, &statBuf,
                                      VSI_STAT_EXISTS_FLAG | VSI_STAT_NATURE_FLAG) == 0 &&
                    !VSI_ISDIR(statBuf.st_mode))
                {
                    bArchiveFileExists = TRUE;
                }
            }

            if (bArchiveFileExists)
            {
                if (pszFilename[i + nToSkip] == '/' ||
                    pszFilename[i + nToSkip] == '\\')
                {
                    char* pszArchiveInFileName = CPLStrdup(pszFilename + i + nToSkip + 1);

                    /* Replace a/../b by b and foo/a/../b by foo/b */
                    while(TRUE)
                    {
                        char* pszPrevDir = strstr(pszArchiveInFileName, "/../");
                        if (pszPrevDir == NULL || pszPrevDir == pszArchiveInFileName)
                            break;

                        char* pszPrevSlash = pszPrevDir - 1;
                        while(pszPrevSlash != pszArchiveInFileName &&
                                *pszPrevSlash != '/')
                            pszPrevSlash --;
                        if (pszPrevSlash == pszArchiveInFileName)
                            memmove(pszArchiveInFileName, pszPrevDir + nToSkip, strlen(pszPrevDir + nToSkip) + 1);
                        else
                            memmove(pszPrevSlash + 1, pszPrevDir + nToSkip, strlen(pszPrevDir + nToSkip) + 1);
                    }

                    osFileInArchive = pszArchiveInFileName;
                    CPLFree(pszArchiveInFileName);
                }
                else
                    osFileInArchive = "";

                /* Remove trailing slash */
                if (osFileInArchive.size())
                {
                    char lastC = osFileInArchive[strlen(osFileInArchive) - 1];
                    if (lastC == '\\' || lastC == '/')
                        osFileInArchive.resize(strlen(osFileInArchive) - 1);
                }

                return archiveFilename;
            }
            CPLFree(archiveFilename);
        }
        i++;
    }
    return NULL;
}