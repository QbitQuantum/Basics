void glwtWin32Error(const char *msg)
{
   LPVOID msgbuf = 0;
   DWORD err = GetLastError();

    if(!FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        err,
        0,
        (LPSTR) &msgbuf,
        0, NULL ))
    {
        glwtErrorPrintf("%s: %d\n", msg, err);
        return;
    }

    glwtErrorPrintf("%s: %s\n", msg, (const char *)msgbuf);
    LocalFree(msgbuf);
}