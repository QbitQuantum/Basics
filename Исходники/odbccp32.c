BOOL WINAPI SQLInstallTranslatorEx(LPCSTR lpszTranslator, LPCSTR lpszPathIn,
               LPSTR lpszPathOut, WORD cbPathOutMax, WORD *pcbPathOut,
               WORD fRequest, LPDWORD lpdwUsageCount)
{
    LPCSTR p;
    LPWSTR translator, pathin;
    WCHAR pathout[MAX_PATH];
    BOOL ret;
    WORD cbOut = 0;

    clear_errors();
    TRACE("%s %s %p %d %p %d %p\n", debugstr_a(lpszTranslator),
          debugstr_a(lpszPathIn), lpszPathOut, cbPathOutMax, pcbPathOut,
          fRequest, lpdwUsageCount);

    for (p = lpszTranslator; *p; p += lstrlenA(p) + 1)
        TRACE("%s\n", debugstr_a(p));

    translator = SQLInstall_strdup_multi(lpszTranslator);
    pathin = SQLInstall_strdup(lpszPathIn);

    ret = SQLInstallTranslatorExW(translator, pathin, pathout, MAX_PATH,
                                  &cbOut, fRequest, lpdwUsageCount);
    if (ret)
    {
        int len =  WideCharToMultiByte(CP_ACP, 0, pathout, -1, lpszPathOut,
                                       0, NULL, NULL);
        if (len)
        {
            if (pcbPathOut)
                *pcbPathOut = len - 1;

            if (!lpszPathOut || cbPathOutMax < len)
            {
                ret = FALSE;
                goto out;
            }
            len =  WideCharToMultiByte(CP_ACP, 0, pathout, -1, lpszPathOut,
                                       cbPathOutMax, NULL, NULL);
        }
    }

out:
    HeapFree(GetProcessHeap(), 0, translator);
    HeapFree(GetProcessHeap(), 0, pathin);
    return ret;
}