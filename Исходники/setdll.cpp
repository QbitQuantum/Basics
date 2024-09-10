BOOL SetFile(PCHAR pszPath)
{
    BOOL bGood = TRUE;
    HANDLE hOld = INVALID_HANDLE_VALUE;
    HANDLE hNew = INVALID_HANDLE_VALUE;
    PDETOUR_BINARY pBinary = NULL;

    CHAR szOrg[MAX_PATH];
    CHAR szNew[MAX_PATH];
    CHAR szOld[MAX_PATH];

    szOld[0] = '\0';
    szNew[0] = '\0';

    StringCchCopyA(szOrg, sizeof(szOrg), pszPath);
    StringCchCopyA(szNew, sizeof(szNew), szOrg);
    StringCchCatA(szNew, sizeof(szNew), "#");
    StringCchCopyA(szOld, sizeof(szOld), szOrg);
    StringCchCatA(szOld, sizeof(szOld), "~");
    printf("  %s:\n", pszPath);

    hOld = CreateFileA(szOrg,
                       GENERIC_READ,
                       FILE_SHARE_READ,
                       NULL,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL);

    if (hOld == INVALID_HANDLE_VALUE) {
        printf("Couldn't open input file: %s, error: %d\n",
               szOrg, GetLastError());
        bGood = FALSE;
        goto end;
    }

    hNew = CreateFileA(szNew,
                       GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hNew == INVALID_HANDLE_VALUE) {
        printf("Couldn't open output file: %s, error: %d\n",
               szNew, GetLastError());
        bGood = FALSE;
        goto end;
    }

    if ((pBinary = DetourBinaryOpen(hOld)) == NULL) {
        printf("DetourBinaryOpen failed: %d\n", GetLastError());
        goto end;
    }

    if (hOld != INVALID_HANDLE_VALUE) {
        CloseHandle(hOld);
        hOld = INVALID_HANDLE_VALUE;
    }

    {
        BOOL bAddedDll = FALSE;

        DetourBinaryResetImports(pBinary);

        if (!s_fRemove) {
            if (!DetourBinaryEditImports(pBinary,
                                         &bAddedDll,
                                         AddBywayCallback, NULL, NULL, NULL)) {
                printf("DetourBinaryEditImports failed: %d\n", GetLastError());
            }
        }

        if (!DetourBinaryEditImports(pBinary, NULL,
                                     ListBywayCallback, ListFileCallback,
                                     NULL, NULL)) {

            printf("DetourBinaryEditImports failed: %d\n", GetLastError());
        }

        if (!DetourBinaryWrite(pBinary, hNew)) {
            printf("DetourBinaryWrite failed: %d\n", GetLastError());
            bGood = FALSE;
        }

        DetourBinaryClose(pBinary);
        pBinary = NULL;

        if (hNew != INVALID_HANDLE_VALUE) {
            CloseHandle(hNew);
            hNew = INVALID_HANDLE_VALUE;
        }

        if (bGood) {
            if (!DeleteFileA(szOld)) {
                DWORD dwError = GetLastError();
                if (dwError != ERROR_FILE_NOT_FOUND) {
                    printf("Warning: Couldn't delete %s: %d\n", szOld, dwError);
                    bGood = FALSE;
                }
            }
            if (!MoveFileA(szOrg, szOld)) {
                printf("Error: Couldn't back up %s to %s: %d\n",
                       szOrg, szOld, GetLastError());
                bGood = FALSE;
            }
            if (!MoveFileA(szNew, szOrg)) {
                printf("Error: Couldn't install %s as %s: %d\n",
                       szNew, szOrg, GetLastError());
                bGood = FALSE;
            }
        }

        DeleteFileA(szNew);
    }


  end:
    if (pBinary) {
        DetourBinaryClose(pBinary);
        pBinary = NULL;
    }
    if (hNew != INVALID_HANDLE_VALUE) {
        CloseHandle(hNew);
        hNew = INVALID_HANDLE_VALUE;
    }
    if (hOld != INVALID_HANDLE_VALUE) {
        CloseHandle(hOld);
        hOld = INVALID_HANDLE_VALUE;
    }
    return bGood;
}