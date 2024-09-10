HMODULE
LoadModuleWithSymbolsFullPath(
    _In_ PSTR pszFullModuleFileName)
{
    HMODULE hmod;
    DWORD64 dwModuleBase;

    /* Load the DLL */
    hmod = LoadLibraryExA(pszFullModuleFileName,
                          NULL,
                          LOAD_IGNORE_CODE_AUTHZ_LEVEL |
                          DONT_RESOLVE_DLL_REFERENCES |
                          LOAD_WITH_ALTERED_SEARCH_PATH);
    if (hmod == NULL)
    {
        return NULL;
    }

    /* Load symbols for this module */
    dwModuleBase = SymLoadModule64(ghProcess,
                                   NULL,
                                   pszFullModuleFileName,
                                   NULL,
                                   (DWORD_PTR)hmod,
                                   0);
    if (dwModuleBase == 0)
    {
        /* ERROR_SUCCESS means, we have symbols already */
        if (GetLastError() != ERROR_SUCCESS)
        {
            return NULL;
        }
    }
    else
    {
        printf("Successfully loaded symbols for '%s'\n",
               pszFullModuleFileName);
    }

    return hmod;
}