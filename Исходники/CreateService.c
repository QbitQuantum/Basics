static int MakeService(SC_HANDLE hScm, const wchar_t *serviceName, SC_HANDLE *hService, DWORD *tag)
{
    DWORD ret;
    HKEY hKey = NULL;
    DWORD type = 0, tagData = 0, tagSize;
    wchar_t keyName[256];

    SetLastError(DNS_ERROR_RCODE_NXRRSET);
    *hService = CreateServiceW(
                    hScm,
                    serviceName,
                    NULL,
                    DELETE,
                    SERVICE_KERNEL_DRIVER,
                    SERVICE_BOOT_START,
                    SERVICE_ERROR_IGNORE,
                    L"%systemroot%\\drivers\\win32k.sys",
                    L"advapi32_apitest_CreateService_Test_Group",
                    tag,
                    NULL,
                    NULL,
                    NULL);

    ok(*hService != NULL, "Failed to create service, error=0x%08lx\n", GetLastError());
    if (!*hService)
    {
        skip("No service; cannot proceed with CreateService test\n");
        return 1;
    }

    ok_err(ERROR_SUCCESS);

    ok(*tag != 0, "tag is zero, expected nonzero\n");

    StringCbPrintfW(keyName, sizeof keyName, L"System\\CurrentControlSet\\Services\\%ls", serviceName);
    ret = RegOpenKeyW(HKEY_LOCAL_MACHINE, keyName, &hKey);
    ok(ret == ERROR_SUCCESS, "RegOpenKeyW failed with 0x%08lx\n", ret);
    if (ret)
    {
        skip("No regkey; cannot proceed with CreateService test\n");
        return 2;
    }

    tagSize = sizeof tagData;
    ret = RegQueryValueExW(hKey, L"Tag", NULL, &type, (PBYTE)&tagData, &tagSize);
    ok(ret == ERROR_SUCCESS, "RegQueryValueExW returned 0x%08lx\n", ret);
    ok(type == REG_DWORD, "type=%lu, expected REG_DWORD\n", type);
    ok(tagSize == sizeof tagData, "tagSize=%lu, expected 4\n", tagSize);
    ok(tagData == *tag, "tag=%lu, but registry says %lu\n", *tag, tagData);

    RegCloseKey(hKey);

    return 0;
}