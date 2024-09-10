    /*
     *  CopyDirectoryA
     *      WinAPI-like function that copies the full directory @szFrom to @szTo
     *      If @szTo doesn't exist, it is created
     */
    inline BOOL CopyDirectoryA(LPCTSTR szFrom, LPCTSTR szTo)
    {
        if(CreateDirectoryA(szTo, NULL))
        {
            ForeachFile(szFrom, "*.*", false, [&szFrom, &szTo](ModLoaderFile& file)
            {
                CHAR szToFile[MAX_PATH], szFromFile[MAX_PATH];
                const char* pPath = file.filename;
                
                sprintf(szToFile, "%s\\%s", szTo, pPath);
                sprintf(szFromFile, "%s\\%s", szFrom, pPath);

                if(file.is_dir) // Call myself again for recursion
                    CopyDirectoryA(szFromFile, szToFile);
                else
                    CopyFileA(szFromFile, szToFile, FALSE);

                return true;
            });
            
            return TRUE;
        }
        
        return FALSE;
    }