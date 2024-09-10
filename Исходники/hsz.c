DWORD InternalDdeQueryString(
DWORD idInst,
HSZ hsz,
PVOID psz,
DWORD cbMax,
INT iCodePage)
{
    PCL_INSTANCE_INFO pcii;
    DWORD dwRet = 0;
    WCHAR szw[256];
// BOOL fDefUsed; // LATER

    EnterDDECrit;

    pcii = ValidateInstance((HANDLE)LongToHandle( idInst ));
    if (pcii == NULL) {
        BestSetLastDDEMLError(DMLERR_INVALIDPARAMETER);
        goto Exit;
    }

    if (ValidateHSZ(hsz) == HSZT_INVALID) {
        SetLastDDEMLError(pcii, DMLERR_INVALIDPARAMETER);
        goto Exit;
    }

    if (LATOM_FROM_HSZ(hsz) == 0) {
        if (iCodePage == CP_WINUNICODE) {
            if (psz != NULL) {
                *(LPWSTR)psz = L'\0';
            }
            dwRet = sizeof(WCHAR);
            goto Exit;
        } else {
            if (psz != NULL) {
                *(LPSTR)psz = '\0';
            }
            dwRet = sizeof(CHAR);
            goto Exit;
        }
    }

    if (psz == NULL) {
        cbMax = sizeof(szw);
        psz = (PVOID)szw;
    }

    switch (iCodePage) {
    case CP_WINANSI:
        dwRet = GetAtomNameA(LATOM_FROM_HSZ(hsz), psz, cbMax);
        break;

    default:
        dwRet = GetAtomNameW(LATOM_FROM_HSZ(hsz), (LPWSTR)psz, cbMax / sizeof(WCHAR));
        if (iCodePage != CP_WINUNICODE) {

            /*
             * convert psz to the appropriate codepage and count the
             * characters(ie BYTES for DBCS!) to alter dwRet.
             */
#ifdef LATER
            // Does this routine work in place? (i.e. input and output buffer the same).
            WideCharToMultiByte((UINT)iCodePage, 0, szw,
                    sizeof(szw) /  sizeof(WCHAR),
                    (LPSTR)psz, cbMax, NULL, &fDefUsed);
#endif
            dwRet = cbMax + 1;
        }
        break;
    }

Exit:
    LeaveDDECrit;
    return (dwRet);
}