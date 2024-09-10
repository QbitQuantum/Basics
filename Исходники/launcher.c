static void
error(int rc, wchar_t * format, ... )
{
    va_list va;
    wchar_t message[MSGSIZE];
    wchar_t win_message[MSGSIZE];
    int len;

    va_start(va, format);
    len = _vsnwprintf_s(message, MSGSIZE, _TRUNCATE, format, va);

    if (rc == 0) {  /* a Windows error */
        winerror(GetLastError(), win_message, MSGSIZE);
        if (len >= 0) {
            _snwprintf_s(&message[len], MSGSIZE - len, _TRUNCATE, L": %ls",
                         win_message);
        }
    }

#if !defined(_WINDOWS)
    fwprintf(stderr, L"%ls\n", message);
#else
    MessageBox(NULL, message, TEXT("Python Launcher is sorry to say ..."),
               MB_OK);
#endif
    exit(rc);
}