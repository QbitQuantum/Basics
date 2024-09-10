static void test_invalid_parametersW(void)
{
    static const WCHAR nonexistentW[] = {'c',':','\\','n','o','n','e','x','i','s','t','e','n','t','.','c','a','b',0};
    static const WCHAR emptyW[] = {0};

    BOOL ret;
    WCHAR source[MAX_PATH], temp[MAX_PATH];
    int i;

    const struct
    {
        PCWSTR CabinetFile;
        PSP_FILE_CALLBACK_W MsgHandler;
        DWORD expected_lasterror;
        int todo_lasterror;
    } invalid_parameters[] =
    {
        {nonexistentW, NULL,            ERROR_FILE_NOT_FOUND},
        {nonexistentW, dummy_callbackW, ERROR_FILE_NOT_FOUND},
        {source,       NULL,            ERROR_INVALID_DATA, 1},
        {source,       dummy_callbackW, ERROR_INVALID_DATA, 1},
    };

    ret = SetupIterateCabinetW(NULL, 0, NULL, NULL);
    if (!ret && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("SetupIterateCabinetW is not available\n");
        return;
    }

    GetTempPathW(sizeof(temp)/sizeof(WCHAR), temp);
    GetTempFileNameW(temp, docW, 0, source);

    create_source_fileW(source, NULL, 0);

    for (i = 0; i < sizeof(invalid_parameters)/sizeof(invalid_parameters[0]); i++)
    {
        SetLastError(0xdeadbeef);
        ret = SetupIterateCabinetW(invalid_parameters[i].CabinetFile, 0,
                                   invalid_parameters[i].MsgHandler, NULL);
        ok(!ret, "[%d] Expected SetupIterateCabinetW to return 0, got %d\n", i, ret);
        if (invalid_parameters[i].todo_lasterror)
        {
            todo_wine
            ok(GetLastError() == invalid_parameters[i].expected_lasterror,
               "[%d] Expected GetLastError() to return %u, got %u\n",
               i, invalid_parameters[i].expected_lasterror, GetLastError());
        }
        else
        {
            ok(GetLastError() == invalid_parameters[i].expected_lasterror,
               "[%d] Expected GetLastError() to return %u, got %u\n",
               i, invalid_parameters[i].expected_lasterror, GetLastError());
        }
    }

    SetLastError(0xdeadbeef);
    ret = SetupIterateCabinetW(NULL, 0, NULL, NULL);
    ok(!ret, "Expected SetupIterateCabinetW to return 0, got %d\n", ret);
    ok(GetLastError() == ERROR_INVALID_PARAMETER ||
       GetLastError() == ERROR_NOT_ENOUGH_MEMORY, /* Vista/Win2k8 */
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
       GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupIterateCabinetW(NULL, 0, dummy_callbackW, NULL);
    ok(!ret, "Expected SetupIterateCabinetW to return 0, got %d\n", ret);
    ok(GetLastError() == ERROR_INVALID_PARAMETER ||
       GetLastError() == ERROR_NOT_ENOUGH_MEMORY, /* Vista/Win2k8 */
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
       GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupIterateCabinetW(emptyW, 0, NULL, NULL);
    ok(!ret, "Expected SetupIterateCabinetW to return 0, got %d\n", ret);
    ok(GetLastError() == ERROR_NOT_ENOUGH_MEMORY ||
       GetLastError() == ERROR_FILE_NOT_FOUND, /* NT4/Win2k */
       "Expected GetLastError() to return ERROR_NOT_ENOUGH_MEMORY, got %u\n",
       GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupIterateCabinetW(emptyW, 0, dummy_callbackW, NULL);
    ok(!ret, "Expected SetupIterateCabinetW to return 0, got %d\n", ret);
    ok(GetLastError() == ERROR_NOT_ENOUGH_MEMORY ||
       GetLastError() == ERROR_FILE_NOT_FOUND, /* NT4/Win2k */
       "Expected GetLastError() to return ERROR_NOT_ENOUGH_MEMORY, got %u\n",
       GetLastError());

    DeleteFileW(source);
}