extern "C" HRESULT CompletePathA(
    LPSTR               szPath,             //@parm  [out] Full Path name   (Must be MAX_PATH in size)
    LPCSTR              szRelPath,          //@parm  Relative Path name
    LPCSTR              szAbsPath           //@parm  Absolute Path name portion (NULL uses current path)
)
{

    LPSTR   szFile;

    int             iStat;

    // If the spec, starts with PathSeparator, it is by definition complete.
    if (szRelPath[0] == PATHSEPARATOR && szRelPath[1] == PATHSEPARATOR) {
        strcpy(szPath, szRelPath);
        return (S_OK);
    }

    // Get the drive letter.
    if (strchr(szRelPath,':') == NULL) {
        // No drive was specified.
        if (szAbsPath == NULL) {
            GetFullPathNameA(szRelPath, MAX_PATH, szPath, &szFile);
            RemoveDotsA(szPath);
            return S_OK;
        }
        else { // An absolute path was specified.
            // Check if the relative path is relative to '\\'
            if (*szRelPath == PATHSEPARATOR) {
                ParsePathA(szAbsPath,szPath,NULL,NULL);
                strcat(szPath,szRelPath);
            }
            else {
                if ((iStat = AppendPathA(szPath,szAbsPath,szRelPath)) < 0)
                    return (iStat);
            }
            RemoveDotsA (szPath);
            return S_OK;
        }
    }
    else {
        GetFullPathNameA(szRelPath, MAX_PATH, szPath, &szFile);
        RemoveDotsA (szPath);
        return S_OK;
    }

}