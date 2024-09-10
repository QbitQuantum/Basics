/**
 * Searches the account name based on a display (real) name (e.g. "John Doe" -> "jdoe").
 * Result "ppwszAccoutName" needs to be freed with CoTaskMemFree!
 */
BOOL VBoxCredProvCredential::TranslateAccountName(PWSTR pwszDisplayName, PWSTR *ppwszAccoutName)
{
    AssertPtrReturn(pwszDisplayName, FALSE);
    VBoxCredProvVerbose(0, "VBoxCredProvCredential::TranslateAccountName: Getting account name for \"%ls\" ...\n",
                        pwszDisplayName);

    /** @todo Do we need ADS support (e.g. TranslateNameW) here? */
    BOOL fFound = FALSE;                        /* Did we find the desired user? */
    NET_API_STATUS rcStatus;
    DWORD dwLevel = 2;                          /* Detailed information about user accounts. */
    DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
    DWORD dwEntriesRead = 0;
    DWORD dwTotalEntries = 0;
    DWORD dwResumeHandle = 0;
    LPUSER_INFO_2 pBuf = NULL;
    LPUSER_INFO_2 pCurBuf = NULL;
    do
    {
        rcStatus = NetUserEnum(NULL,             /* Server name, NULL for localhost. */
                               dwLevel,
                               FILTER_NORMAL_ACCOUNT,
                               (LPBYTE*)&pBuf,
                               dwPrefMaxLen,
                               &dwEntriesRead,
                               &dwTotalEntries,
                               &dwResumeHandle);
        if (   rcStatus == NERR_Success
            || rcStatus == ERROR_MORE_DATA)
        {
            if ((pCurBuf = pBuf) != NULL)
            {
                for (DWORD i = 0; i < dwEntriesRead; i++)
                {
                    /*
                     * Search for the "display name" - that might be
                     * "John Doe" or something similar the user recognizes easier
                     * and may not the same as the "account" name (e.g. "jdoe").
                     */
                    if (   pCurBuf
                        && pCurBuf->usri2_full_name
                        && StrCmpI(pwszDisplayName, pCurBuf->usri2_full_name) == 0)
                    {
                        /*
                         * Copy the real user name (e.g. "jdoe") to our
                         * output buffer.
                         */
                        LPWSTR pwszTemp;
                        HRESULT hr = SHStrDupW(pCurBuf->usri2_name, &pwszTemp);
                        if (hr == S_OK)
                        {
                            *ppwszAccoutName = pwszTemp;
                            fFound = TRUE;
                        }
                        else
                            VBoxCredProvVerbose(0, "VBoxCredProvCredential::TranslateAccountName: Error copying data, hr=%08x\n", hr);
                        break;
                    }
                    pCurBuf++;
                }
            }
            if (pBuf != NULL)
            {
                NetApiBufferFree(pBuf);
                pBuf = NULL;
            }
        }
    } while (rcStatus == ERROR_MORE_DATA && !fFound);

    if (pBuf != NULL)
    {
        NetApiBufferFree(pBuf);
        pBuf = NULL;
    }

    VBoxCredProvVerbose(0, "VBoxCredProvCredential::TranslateAccountName returned rcStatus=%ld, fFound=%RTbool\n",
                        rcStatus, fFound);
    return fFound;

#if 0
    DWORD dwErr = NO_ERROR;
    ULONG cbLen = 0;
    if (   TranslateNameW(pwszName, NameUnknown, NameUserPrincipal, NULL, &cbLen)
        && cbLen > 0)
    {
        VBoxCredProvVerbose(0, "VBoxCredProvCredential::GetAccountName: Translated ADS name has %u characters\n", cbLen));

        ppwszAccoutName = (PWSTR)RTMemAlloc(cbLen * sizeof(WCHAR));
        AssertPtrReturn(pwszName, FALSE);
        if (TranslateNameW(pwszName, NameUnknown, NameUserPrincipal, ppwszAccoutName, &cbLen))
        {
            VBoxCredProvVerbose(0, "VBoxCredProvCredential::GetAccountName: Real ADS account name of '%ls' is '%ls'\n",
                 pwszName, ppwszAccoutName));
        }