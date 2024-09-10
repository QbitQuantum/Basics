static int renderspuAtiQuirk_GetICDDriverList(char *pBuf, DWORD cbBuf, DWORD *pcbResult)
{
    static LPCSTR aValueNames[] = {"OpenGLVendorName", "OpenGLDriverName"};
    char *pBufPos = pBuf;
    DWORD cbBufRemain = cbBuf, cbTotal = 0;
    HKEY hKey, hSubkey;
    DWORD dwIndex = 0;
    int i;
    int rc = VINF_SUCCESS;
    char NameBuf[CRREG_MAXKEYNAME];
    LONG lRc;

    if (pcbResult)
        *pcbResult = 0;

    lRc = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
            "SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E968-E325-11CE-BFC1-08002BE10318}",
            0, /* reserved*/
            KEY_READ,
            &hKey);
    if (ERROR_SUCCESS != lRc)
    {
        crDebug("RegOpenKeyEx 1 failed, %d", lRc);
        return VERR_OPEN_FAILED;
    }

    for ( ; ; ++dwIndex)
    {
        lRc = RegEnumKeyA(hKey, dwIndex, NameBuf, CRREG_MAXKEYNAME);
        if (lRc == ERROR_NO_MORE_ITEMS)
            break;
        if (lRc == ERROR_MORE_DATA)
            continue;
        if (lRc != ERROR_SUCCESS)
        {
            crWarning("RegEnumKeyA failed, %d", lRc);
            continue;
        }

        lRc = RegOpenKeyEx(hKey,
                NameBuf,
                0, /* reserved*/
                KEY_READ,
                &hSubkey);
        if (ERROR_SUCCESS != lRc)
        {
            crDebug("RegOpenKeyEx 2 failed, %d", lRc);
            RegCloseKey(hKey);
            return VERR_OPEN_FAILED;
        }

        for (i = 0; i < RT_ELEMENTS(aValueNames); ++i)
        {
            DWORD cbCur = cbBufRemain;
            DWORD type;
            lRc = RegQueryValueExA(hSubkey, aValueNames[i], NULL, /* reserved*/
                    &type,
                    (PBYTE)pBufPos, &cbCur);
            /* exclude second null termination */
            --cbCur;

            if (ERROR_MORE_DATA == lRc)
            {
                if (REG_MULTI_SZ != type)
                {
                    crWarning("unexpected data type! %d", type);
                    continue;
                }
                rc = VERR_BUFFER_OVERFLOW;
                pBufPos = NULL;
                cbBufRemain = 0;
                CRASSERT(cbCur > 0 && cbCur < UINT32_MAX/2);
                cbTotal += cbCur;
                continue;
            }
            if (ERROR_SUCCESS != lRc)
            {
                crDebug("RegQueryValueExA failed, %d", lRc);
                continue;
            }

            if (REG_MULTI_SZ != type)
            {
                crWarning("unexpected data type! %d", type);
                continue;
            }

            /* succeeded */
            CRASSERT(cbCur > 0 && cbCur < UINT32_MAX/2);
            pBufPos += cbCur;
            cbBufRemain -= cbCur;
            cbTotal += cbCur;
            CRASSERT(cbBufRemain < UINT32_MAX/2);
        }

        RegCloseKey(hSubkey);
    }

    RegCloseKey(hKey);

    if (cbTotal)
    {
        /* include second null termination */
        CRASSERT(!pBufPos || pBufPos[0] == '\0');
        ++cbTotal;
    }

    if (pcbResult)
        *pcbResult = cbTotal;

    return rc;
}