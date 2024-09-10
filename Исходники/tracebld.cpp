BOOL CLIENT::LogMessageV(PCHAR pszMsg, ...)
{
    DWORD cbWritten = 0;
    CHAR szBuf[1024];
    PCHAR pcchEnd = szBuf + ARRAYSIZE(szBuf) - 2;
    PCHAR pcchCur = szBuf;
    HRESULT hr;

    va_list args;
    va_start(args, pszMsg);
    hr = StringCchVPrintfExA(pcchCur, pcchEnd - pcchCur,
                             &pcchCur, NULL, STRSAFE_NULL_ON_FAILURE,
                             pszMsg, args);
    va_end(args);
    if (FAILED(hr)) {
        goto cleanup;
    }

    hr = StringCchPrintfExA(pcchCur, szBuf + (ARRAYSIZE(szBuf)) - pcchCur,
                            &pcchCur, NULL, STRSAFE_NULL_ON_FAILURE,
                            "\n");

  cleanup:
    WriteFile(hFile, szBuf, (DWORD)(pcchCur - szBuf), &cbWritten, NULL);
    return TRUE;
}