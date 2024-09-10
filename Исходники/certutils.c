static DWORD
VMCABackupFiles(
    PCSTR pszBaseFilePath
    )
{
    DWORD dwError = ERROR_SUCCESS;
    const DWORD MAX_NUMBER_OF_BAKUPS = 32;
    struct STAT st = { 0 };
    DWORD dwCounter;

    PSTR pszDestFile = NULL;
    PSTR pszSourceFile = NULL;

    for (dwCounter = MAX_NUMBER_OF_BAKUPS; dwCounter > 0; --dwCounter)
    {
        dwError = VMCAAllocateStringPrintfA(
                              &pszDestFile,
                              "%s.%d",
                              pszBaseFilePath,
                              dwCounter);
        BAIL_ON_ERROR(dwError);

        if(STAT(pszDestFile, &st) == ERROR_SUCCESS ) 
        {
            UNLINK(pszDestFile);
        }

        dwError = VMCAAllocateStringPrintfA(
                              &pszSourceFile,
                              "%s.%d",
                              pszBaseFilePath,
                              dwCounter - 1);
        BAIL_ON_ERROR(dwError);

        RENAME(pszSourceFile, pszDestFile);

        VMCA_SAFE_FREE_STRINGA(pszDestFile);
        VMCA_SAFE_FREE_STRINGA(pszSourceFile);

        pszDestFile = NULL;
        pszSourceFile = NULL;
    }

    VMCA_SAFE_FREE_STRINGA(pszDestFile);

    dwError = VMCAAllocateStringPrintfA(
                          &pszDestFile,
                          "%s.%d",
                          pszBaseFilePath,
                          0);
    BAIL_ON_ERROR(dwError);

    RENAME(pszBaseFilePath, pszDestFile);

error:
    VMCA_SAFE_FREE_STRINGA(pszDestFile);
    VMCA_SAFE_FREE_STRINGA(pszSourceFile);

    return dwError;
}