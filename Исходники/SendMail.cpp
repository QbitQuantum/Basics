static char *CopyAddress(char *pszDest, char const *pszAddr, int iSize)
{
    char *pszDomain;

    if (strchr(pszAddr, '@') != NULL ||
        (pszDomain = SysGetEnv(ENV_DEFAULT_DOMAIN)) == NULL)
        StrNCpy(pszDest, pszAddr, iSize);
    else
        SysSNPrintf(pszDest, iSize, "%s@%s", pszAddr, pszDomain);

    return pszDest;
}