BOOL EditFile(PCHAR pszInput, PCHAR pszOutput)
{
    BOOL fGood = TRUE;

    HANDLE hOld = INVALID_HANDLE_VALUE;
    HANDLE hNew = INVALID_HANDLE_VALUE;
    PDETOUR_BINARY pBinary = NULL;

    if (pszOutput != NULL) {
        printf("%s -> %s:\n", pszInput, pszOutput);
    }
    else {
        printf("%s:\n", pszInput, pszOutput);
    }

    hOld = CreateFile(pszInput,
                      GENERIC_READ,
                      FILE_SHARE_READ,
                      NULL,
                      OPEN_EXISTING,
                      FILE_ATTRIBUTE_NORMAL,
                      NULL);

    if (hOld == INVALID_HANDLE_VALUE) {
        printf("Couldn't open input file: %s, error: %d\n",
               pszInput, GetLastError());
        fGood = FALSE;
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

    if (s_fRestore) {
        if (!DetourBinaryEditImports(pBinary,
                                     NULL,
                                     RestoreByway,
                                     RestoreFile,
                                     RestoreSymbol,
                                     RestoreCommit)) {

            printf("DetourBinaryEditImports for munge failed: %d\n", GetLastError());
        }
    }

    if (s_fMunge) {
        MUNGE_STATE state;
        state.fLastWasByway = FALSE;
        state.nBywayCount = 1;

        if (!DetourBinaryEditImports(pBinary,
                                     &state,
                                     MungeByway,
                                     MungeFile,
                                     MungeSymbol,
                                     MungeCommit)) {

            printf("DetourBinaryEditImports for munge failed: %d\n", GetLastError());
        }
    }

    if (s_fList) {
        if (!DetourBinaryEditImports(pBinary,
                                     NULL,
                                     ListByway,
                                     ListFile,
                                     ListSymbol,
                                     ListCommit)) {

            printf("DetourBinaryEditImports for list failed: %d\n", GetLastError());
        }
    }

    if (pszOutput != NULL) {
        hNew = CreateFile(pszOutput,
                          GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS,
                          FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
        if (hNew == INVALID_HANDLE_VALUE) {
            printf("Couldn't open output file: %s, error: %d\n",
                   pszOutput, GetLastError());
            fGood = FALSE;
            goto end;
        }

        if (!DetourBinaryWrite(pBinary, hNew)) {
            printf("DetourBinaryWrite failed: %d\n", GetLastError());
            fGood = FALSE;
        }

        CloseHandle(hNew);
        hNew = INVALID_HANDLE_VALUE;
    }

    DetourBinaryClose(pBinary);
    pBinary = NULL;


    if (fGood && pszOutput != NULL) {
        if (!BindImageEx(BIND_NO_BOUND_IMPORTS, pszOutput, ".", ".", NULL)) {
            printf("Warning: Couldn't bind binary %s: %d\n", pszOutput, GetLastError());
        }
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
    return fGood;
}