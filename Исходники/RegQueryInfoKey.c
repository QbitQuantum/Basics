static
VOID
TestKeyAccess_(
    _In_ PCSTR File,
    _In_ INT Line,
    _In_ REGSAM DesiredAccess,
    _In_ LONG ExpectedReturn,
    _In_ BOOLEAN ExpectSd)
{
    DWORD cbSd;
    HKEY hKey;
    LONG ret;

    ret = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"Software", 0, DesiredAccess, &hKey);
    ok_(File, Line)(ret == NO_ERROR, "RegOpenKeyEx returned %ld\n", ret);
    if (ret == NO_ERROR)
    {
        cbSd = 0x55555555;
        ret = RegQueryInfoKeyW(hKey, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &cbSd, NULL);
        ok_(File, Line)(ret == ExpectedReturn, "RegQueryInfoKeyW returned %ld\n", ret);
        if (ExpectSd)
            ok_(File, Line)(cbSd != 0 && cbSd != 0x55555555, "RegQueryInfoKeyW - cbSd = %lu\n", cbSd);
        else
            ok_(File, Line)(cbSd == 0, "RegQueryInfoKeyW - cbSd = %lu\n", cbSd);

        cbSd = 0x55555555;
        ret = RegQueryInfoKeyA(hKey, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &cbSd, NULL);
        ok_(File, Line)(ret == ExpectedReturn, "RegQueryInfoKeyA returned %ld\n", ret);
        if (ExpectSd)
            ok_(File, Line)(cbSd != 0 && cbSd != 0x55555555, "RegQueryInfoKeyA - cbSd = %lu\n", cbSd);
        else
            ok_(File, Line)(cbSd == 0, "RegQueryInfoKeyA - cbSd = %lu\n", cbSd);
        ret = RegCloseKey(hKey);
        ok_(File, Line)(ret == NO_ERROR, "RegCloseKey returned %ld\n", ret);
    }
    else
    {
        skip_(File, Line)("No key handle\n");
    }
}