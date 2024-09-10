/*
 * Just like JLI_ReportErrorMessage, except that it concatenates the system
 * error message if any, its upto the calling routine to correctly
 * format the separation of the messages.
 */
void
JLI_ReportErrorMessageSys(const char *fmt, ...)
{
    va_list vl;

    int save_errno = errno;
    DWORD       errval;
    jboolean freeit = JNI_FALSE;
    char  *errtext = NULL;

    va_start(vl, fmt);

    if ((errval = GetLastError()) != 0) {               /* Platform SDK / DOS Error */
        int n = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|
            FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_ALLOCATE_BUFFER,
            NULL, errval, 0, (LPTSTR)&errtext, 0, NULL);
        if (errtext == NULL || n == 0) {                /* Paranoia check */
            errtext = "";
            n = 0;
        } else {
            freeit = JNI_TRUE;
            if (n > 2) {                                /* Drop final CR, LF */
                if (errtext[n - 1] == '\n') n--;
                if (errtext[n - 1] == '\r') n--;
                errtext[n] = '\0';
            }
        }
    } else {   /* C runtime error that has no corresponding DOS error code */
        errtext = strerror(save_errno);
    }

    if (IsJavaw()) {
        char *message;
        int mlen;
        /* get the length of the string we need */
        int len = mlen =  _vscprintf(fmt, vl) + 1;
        if (freeit) {
           mlen += (int)JLI_StrLen(errtext);
        }

        message = (char *)JLI_MemAlloc(mlen);
        _vsnprintf(message, len, fmt, vl);
        message[len]='\0';

        if (freeit) {
           JLI_StrCat(message, errtext);
        }

        MessageBox(NULL, message, "Java Virtual Machine Launcher",
            (MB_OK|MB_ICONSTOP|MB_APPLMODAL));

        JLI_MemFree(message);
    } else {
        vfprintf(stderr, fmt, vl);
        if (freeit) {
           fprintf(stderr, "%s", errtext);
        }
    }
    if (freeit) {
        (void)LocalFree((HLOCAL)errtext);
    }
    va_end(vl);
}