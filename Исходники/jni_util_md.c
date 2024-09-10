size_t
getLastErrorString(char *utf8_jvmErrorMsg, size_t cbErrorMsg)
{
    size_t n = 0;
    if (cbErrorMsg > 0) {
        BOOLEAN noError = FALSE;
        WCHAR *utf16_osErrorMsg = (WCHAR *)malloc(cbErrorMsg*sizeof(WCHAR));
        if (utf16_osErrorMsg == NULL) {
            // OOM accident
            strncpy(utf8_jvmErrorMsg, "Out of memory", cbErrorMsg);
            // truncate if too long
            utf8_jvmErrorMsg[cbErrorMsg - 1] = '\0';
            n = strlen(utf8_jvmErrorMsg);
        } else {
            DWORD errval = GetLastError();
            if (errval != 0) {
                // WIN32 error
                n = (size_t)FormatMessageW(
                    FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    errval,
                    0,
                    utf16_osErrorMsg,
                    (DWORD)cbErrorMsg,
                    NULL);
                if (n > 3) {
                    // Drop final '.', CR, LF
                    if (utf16_osErrorMsg[n - 1] == L'\n') --n;
                    if (utf16_osErrorMsg[n - 1] == L'\r') --n;
                    if (utf16_osErrorMsg[n - 1] == L'.') --n;
                    utf16_osErrorMsg[n] = L'\0';
                }
            } else if (errno != 0) {
                // C runtime error that has no corresponding WIN32 error code
                const WCHAR *rtError = _wcserror(errno);
                if (rtError != NULL) {
                    wcsncpy(utf16_osErrorMsg, rtError, cbErrorMsg);
                    // truncate if too long
                    utf16_osErrorMsg[cbErrorMsg - 1] = L'\0';
                    n = wcslen(utf16_osErrorMsg);
                }
            } else
                noError = TRUE; //OS has no error to report

            if (!noError) {
                if (n > 0) {
                    n = WideCharToMultiByte(
                        CP_UTF8,
                        0,
                        utf16_osErrorMsg,
                        (int)n,
                        utf8_jvmErrorMsg,
                        (int)cbErrorMsg,
                        NULL,
                        NULL);

                    // no way to die
                    if (n > 0)
                        utf8_jvmErrorMsg[min(cbErrorMsg - 1, n)] = '\0';
                }

                if (n <= 0) {
                    strncpy(utf8_jvmErrorMsg, "Secondary error while OS message extraction", cbErrorMsg);
                    // truncate if too long
                    utf8_jvmErrorMsg[cbErrorMsg - 1] = '\0';
                    n = strlen(utf8_jvmErrorMsg);
                }
            }
            free(utf16_osErrorMsg);
        }
    }
    return n;
}