/*************************************************************
 *     UnloadPerfCounterTextStringsA (loadperf.@)
 *
 * NOTES
 *   See UnloadPerfCounterTextStringsW
 */
DWORD WINAPI UnloadPerfCounterTextStringsA(LPCSTR cmdline, BOOL quiet)
{
    DWORD ret;
    LPWSTR cmdlineW = NULL;

    if (cmdline && !(cmdlineW = strdupAW(cmdline))) return ERROR_OUTOFMEMORY;

    ret = UnloadPerfCounterTextStringsW(cmdlineW, quiet);

    HeapFree(GetProcessHeap(), 0, cmdlineW);

    return ret;
}