static void test_GetDiskInfoA(void)
{
    BOOL ret;
    DWORD error, cluster_size;
    DWORDLONG free, total;
    char path[MAX_PATH], *p;

    GetSystemDirectoryA(path, MAX_PATH);
    if ((p = strchr(path, '\\'))) *++p = 0;

    ret = GetDiskInfoA(path, &cluster_size, &free, &total);
    ok(ret, "GetDiskInfoA failed %u\n", GetLastError());

    ret = GetDiskInfoA(path, &cluster_size, &free, NULL);
    ok(ret, "GetDiskInfoA failed %u\n", GetLastError());

    ret = GetDiskInfoA(path, &cluster_size, NULL, NULL);
    ok(ret, "GetDiskInfoA failed %u\n", GetLastError());

    ret = GetDiskInfoA(path, NULL, NULL, NULL);
    ok(ret, "GetDiskInfoA failed %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    strcpy(p, "\\non\\existing\\path");
    ret = GetDiskInfoA(path, NULL, NULL, NULL);
    error = GetLastError();
    ok(!ret ||
       broken(ret), /* < IE7 */
       "GetDiskInfoA succeeded\n");
    ok(error == ERROR_PATH_NOT_FOUND ||
       broken(error == 0xdeadbeef), /* < IE7 */
       "got %u expected ERROR_PATH_NOT_FOUND\n", error);

    SetLastError(0xdeadbeef);
    ret = GetDiskInfoA(NULL, NULL, NULL, NULL);
    error = GetLastError();
    ok(!ret, "GetDiskInfoA succeeded\n");
    ok(error == ERROR_INVALID_PARAMETER, "got %u expected ERROR_INVALID_PARAMETER\n", error);
}