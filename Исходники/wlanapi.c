static void WlanRenameProfile_test(void)
{
    DWORD ret;

    /* invalid pReserved */
    ret = WlanRenameProfile((HANDLE) -1, &InterfaceGuid, L"test", L"test1", (PVOID) 1);
    ok(ret == ERROR_INVALID_PARAMETER, "expected failure\n");

    /* invalid InterfaceGuid */
    ret = WlanRenameProfile((HANDLE) -1, NULL, L"test", L"test1", NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "expected failure\n");

    /* invalid strOldProfileName */
    ret = WlanRenameProfile((HANDLE) -1, &InterfaceGuid, NULL, L"test1", NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "expected failure\n");

    /* invalid strNewProfileName */
    ret = WlanRenameProfile((HANDLE) -1, &InterfaceGuid, L"test", NULL, NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "expected failure\n");    
}