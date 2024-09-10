/***********************************************************************
 *      WSASetBlockingHook		(WINSOCK.109)
 */
FARPROC16 WINAPI WSASetBlockingHook16(FARPROC16 lpBlockFunc)
{
    /* FIXME: should deal with 16-bit proc */
    return (FARPROC16)WSASetBlockingHook( (FARPROC)lpBlockFunc );
}