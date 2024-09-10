static void test_WTSEnumerateProcessesW(void)
{
    BOOL found = FALSE, ret;
    DWORD count, i;
    PWTS_PROCESS_INFOW info;
    WCHAR *pname, nameW[MAX_PATH];

    GetModuleFileNameW(NULL, nameW, MAX_PATH);
    for (pname = nameW + lstrlenW(nameW); pname > nameW; pname--)
    {
        if(*pname == '/' || *pname == '\\')
        {
            pname++;
            break;
        }
    }

    info = NULL;
    SetLastError(0xdeadbeef);
    ret = WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, 1, 1, &info, &count);
    todo_wine
    ok(!ret, "expected WTSEnumerateProcessesW to fail\n");
    todo_wine
    ok(GetLastError()== ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER got: %d\n", GetLastError());
    if (info) WTSFreeMemory(info);

    info = NULL;
    SetLastError(0xdeadbeef);
    ret = WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, 0, 0, &info, &count);
    todo_wine
    ok(!ret, "expected WTSEnumerateProcessesW to fail\n");
    todo_wine
    ok(GetLastError()== ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER got: %d\n", GetLastError());
    if (info) WTSFreeMemory(info);

    info = NULL;
    SetLastError(0xdeadbeef);
    ret = WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, 0, 2, &info, &count);
    todo_wine
    ok(!ret, "expected WTSEnumerateProcessesW to fail\n");
    todo_wine
    ok(GetLastError()== ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER got: %d\n", GetLastError());
    if (info) WTSFreeMemory(info);

    SetLastError(0xdeadbeef);
    ret = WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, 0, 1, NULL, &count);
    ok(!ret, "expected WTSEnumerateProcessesW to fail\n");
    todo_wine
    ok(GetLastError()== ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER got: %d\n", GetLastError());

    info = NULL;
    SetLastError(0xdeadbeef);
    ret = WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, 0, 1, &info, NULL);
    ok(!ret, "expected WTSEnumerateProcessesW to fail\n");
    todo_wine
    ok(GetLastError()== ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER got: %d\n", GetLastError());
    if (info) WTSFreeMemory(info);

    count = 0;
    info = NULL;
    SetLastError(0xdeadbeef);
    ret = WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, 0, 1, &info, &count);
    ok(ret || broken(!ret), /* fails on Win2K with error ERROR_APP_WRONG_OS */
        "expected WTSEnumerateProcessesW to succeed; failed with %d\n", GetLastError());
    for(i = 0; ret && i < count; i++)
    {
        found = found || !lstrcmpW(pname, info[i].pProcessName);
    }
    todo_wine
    ok(found || broken(!ret), "process name %s not found\n", wine_dbgstr_w(pname));
    if (info) WTSFreeMemory(info);
}