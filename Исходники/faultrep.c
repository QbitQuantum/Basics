/*************************************************************************
 * AddERExcludedApplicationA  [FAULTREP.@]
 *
 * See AddERExcludedApplicationW
 */
BOOL WINAPI AddERExcludedApplicationA(LPCSTR lpAppFileName)
{
    int len = MultiByteToWideChar(CP_ACP, 0, lpAppFileName, -1, NULL, 0);
    WCHAR *wstr;
    BOOL ret;

    TRACE("(%s)\n", wine_dbgstr_a(lpAppFileName));
    if (len == 0)
        return FALSE;
    wstr = HeapAlloc(GetProcessHeap(), 0, sizeof(WCHAR)*len);
    MultiByteToWideChar(CP_ACP, 0, lpAppFileName, -1, wstr, len);
    ret = AddERExcludedApplicationW(wstr);
    HeapFree(GetProcessHeap(), 0, wstr);
    return ret;
}