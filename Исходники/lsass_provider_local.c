static
DWORD
LocalCfgSetHomedirUmask(
    PLOCAL_CONFIG pConfig,
    PCSTR          pszName,
    PCSTR          pszValue
    )
{
    DWORD dwError = 0;
    PCSTR cp = NULL;
    DWORD dwOct = 0;
    DWORD dwVal = 0;
    DWORD dwCnt = 0;
    char  cp2[2];
    PSTR pszUmask = NULL;

    // Convert the umask octal string to a decimal number

    cp2[1] = 0;

    for (cp = pszValue, dwCnt = 0; isdigit((int)*cp); cp++, dwCnt++)
    {
        dwOct *= 8;

        cp2[0] = *cp;
        dwVal = atoi(cp2);

        if (dwVal > 7)
        {
            dwError = LW_ERROR_INVALID_PARAMETER;
        }
        BAIL_ON_UP_ERROR(dwError);

        dwOct += dwVal;
    }

    if (dwCnt > 4)
    {
        dwError = LW_ERROR_INVALID_PARAMETER;
    }
    BAIL_ON_UP_ERROR(dwError);

    // Disallow 07xx since the user should always have
    // access to his home directory.
    if ((dwOct & 0700) == 0700)
    {
        dwError = LW_ERROR_INVALID_PARAMETER;
    }
    BAIL_ON_UP_ERROR(dwError);

    dwError = LwAllocateString(pszValue, &pszUmask);
    BAIL_ON_UP_ERROR(dwError);

    LW_SAFE_FREE_STRING(pConfig->pszUmask);
    pConfig->pszUmask = pszUmask;
    pszUmask = NULL;

cleanup:

    LW_SAFE_FREE_STRING(pszUmask);

    return dwError;

error:

    goto cleanup;
}