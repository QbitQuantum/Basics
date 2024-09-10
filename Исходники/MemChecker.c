void MemChecker_ParseLineCB(void *pUser, const char *pszKey, int nKeyLen, const char *pszValue, int nValueLen)
{
    MemChecker *pMe = (MemChecker *)pUser;
    char *pszValueCopy = NULL;

    pszValueCopy = MALLOC(nValueLen + 1);
    if (NULL == pszValueCopy) {
        return;
    }
    MEMCPY(pszValueCopy, pszValue, nValueLen);

    if (0 == STRNCMP("ClassID", pszKey, nKeyLen))
    {
        if (STRBEGINS("0x", pszValueCopy)) {
            pMe->m_clsCheckedApp = STRTOUL(pszValueCopy, NULL, 16);
        } else {
            pMe->m_clsCheckedApp = ATOI(pszValueCopy);
        }
    }
    else if (0 == STRNCMP("OutputTo", pszKey, nKeyLen))
    {
        pMe->m_eOutputMode = ATOI(pszValueCopy);
    }

    FREEIF(pszValueCopy);
}