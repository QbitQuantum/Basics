static void test_ImmDestroyIMCC(void)
{
    HIMCC imcc;
    DWORD ret, count, size;
    VOID *p;

    imcc = ImmCreateIMCC(sizeof(CANDIDATEINFO));
    count = ImmGetIMCCLockCount(imcc);
    ok(count == 0, "expect 0, returned %d\n", count);
    p = ImmLockIMCC(imcc);
    ok(p != NULL, "ImmLockIMCC failed!\n");
    count = ImmGetIMCCLockCount(imcc);
    ok(count == 1, "expect 1, returned %d\n", count);
    size = ImmGetIMCCSize(imcc);
    ok(size == sizeof(CANDIDATEINFO), "returned %d\n", size);
    p = ImmDestroyIMCC(imcc);
    ok(p == NULL, "Destroy a locked IMCC should success!\n");
    p = ImmLockIMCC(imcc);
    ok(p == NULL, "Lock a destroyed IMCC should fail!\n");
    ret = ImmUnlockIMCC(imcc);
    ok(ret == FALSE, "Unlock a destroyed IMCC should return FALSE!\n");
    count = ImmGetIMCCLockCount(imcc);
    ok(count == 0, "Get lock count of a destroyed IMCC should return 0!\n");
    size = ImmGetIMCCSize(imcc);
    ok(size == 0, "Get size of a destroyed IMCC should return 0!\n");
    SetLastError(0xdeadbeef);
    p = ImmDestroyIMCC(imcc);
    ok(p != NULL, "returned NULL\n");
    ret = GetLastError();
    ok(ret == ERROR_INVALID_HANDLE, "wrong last error %08x!\n", ret);
}