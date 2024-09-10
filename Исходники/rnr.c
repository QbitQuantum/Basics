/*
 * @implemented
 */
INT
WSAAPI
WSALookupServiceNextA(IN HANDLE hLookup,
                      IN DWORD dwControlFlags,
                      IN OUT LPDWORD lpdwBufferLength,
                      OUT LPWSAQUERYSETA lpqsResults)
{
    LPWSAQUERYSETW UnicodeQuerySet;
    DWORD UnicodeQuerySetSize = *lpdwBufferLength;
    INT ErrorCode;
    DPRINT("WSALookupServiceNextA: %lx\n", hLookup);

    /* Check how much the user is giving */
    if (UnicodeQuerySetSize >= sizeof(WSAQUERYSETW))
    {
        /* Allocate the buffer we'll use */
        UnicodeQuerySet = HeapAlloc(WsSockHeap, 0, UnicodeQuerySetSize);
        if (!UnicodeQuerySet) UnicodeQuerySetSize = 0;
    }
    else
    {
        /* His buffer is too small */
        UnicodeQuerySetSize = 0;
        UnicodeQuerySet = NULL;
    }

    /* Call the Unicode Function */
    ErrorCode = WSALookupServiceNextW(hLookup,
                                      dwControlFlags,
                                      &UnicodeQuerySetSize,
                                      UnicodeQuerySet);
    if (ErrorCode == ERROR_SUCCESS)
    {
        /* Not convert to ANSI */
        ErrorCode = MapUnicodeQuerySetToAnsi(UnicodeQuerySet,
                                             lpdwBufferLength,
                                             lpqsResults);
        if (ErrorCode != ERROR_SUCCESS) SetLastError(ErrorCode);
    }
    else
    {
        /* Check if we ran out of space */
        if (GetLastError() == WSAEFAULT)
        {
            /* Return how much space we'll need, including padding */
            *lpdwBufferLength = UnicodeQuerySetSize +
                                ((sizeof(ULONG) * 6) - (6 * 1));
        }
    }

    /* If we had a local buffer, free it */
    if (UnicodeQuerySet) HeapFree(WsSockHeap, 0, UnicodeQuerySet);

    /* Return to caller */
    return ErrorCode == ERROR_SUCCESS ? ErrorCode : SOCKET_ERROR;
}