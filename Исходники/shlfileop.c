/* tests the FO_DELETE action */
static void test_delete(void)
{
    SHFILEOPSTRUCTA shfo;
    DWORD ret;
    CHAR buf[MAX_PATH];

    sprintf(buf, "%s\\%s", CURR_DIR, "test?.txt");
    buf[strlen(buf) + 1] = '\0';

    shfo.hwnd = NULL;
    shfo.wFunc = FO_DELETE;
    shfo.pFrom = buf;
    shfo.pTo = "\0";
    shfo.fFlags = FOF_FILESONLY | FOF_NOCONFIRMATION | FOF_SILENT;
    shfo.hNameMappings = NULL;
    shfo.lpszProgressTitle = NULL;

    ok(!SHFileOperationA(&shfo), "Deletion was successful\n");
    ok(file_exists("test4.txt"), "Directory should not be removed\n");
    ok(!file_exists("test1.txt"), "File should be removed\n");

    ret = SHFileOperationA(&shfo);
    ok(!ret, "Directory exists, but is not removed, ret=%ld\n", ret);
    ok(file_exists("test4.txt"), "Directory should not be removed\n");

    shfo.fFlags = FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI;

    ok(!SHFileOperationA(&shfo), "Directory removed\n");
    ok(!file_exists("test4.txt"), "Directory should be removed\n");

    ret = SHFileOperationA(&shfo);
    ok(!ret, "The requested file does not exist, ret=%ld\n", ret);

    init_shfo_tests();
    sprintf(buf, "%s\\%s", CURR_DIR, "test4.txt");
    buf[strlen(buf) + 1] = '\0';
    ok(MoveFileA("test1.txt", "test4.txt\\test1.txt"), "Fill the subdirectory\n");
    ok(!SHFileOperationA(&shfo), "Directory removed\n");
    ok(!file_exists("test4.txt"), "Directory is removed\n");

    init_shfo_tests();
    shfo.pFrom = "test1.txt\0test4.txt\0";
        ok(!SHFileOperationA(&shfo), "Directory and a file removed\n");
        ok(!file_exists("test1.txt"), "The file should be removed\n");
        ok(!file_exists("test4.txt"), "Directory should be removed\n");
    ok(file_exists("test2.txt"), "This file should not be removed\n");

    /* FOF_FILESONLY does not delete a dir matching a wildcard */
    init_shfo_tests();
    shfo.fFlags |= FOF_FILESONLY;
    shfo.pFrom = "*.txt\0";
        ok(!SHFileOperation(&shfo), "Failed to delete files\n");
        ok(!file_exists("test1.txt"), "test1.txt should be removed\n");
        ok(!file_exists("test_5.txt"), "test_5.txt should be removed\n");
    ok(file_exists("test4.txt"), "test4.txt should not be removed\n");

    /* FOF_FILESONLY only deletes a dir if explicitly specified */
    init_shfo_tests();
    shfo.pFrom = "test_?.txt\0test4.txt\0";
        ok(!SHFileOperation(&shfo), "Failed to delete files\n");
        ok(!file_exists("test4.txt"), "test4.txt should be removed\n");
        ok(!file_exists("test_5.txt"), "test_5.txt should be removed\n");
    ok(file_exists("test1.txt"), "test1.txt should not be removed\n");

    /* try to delete an invalid filename */
    init_shfo_tests();
    shfo.pFrom = "\0";
    shfo.fFlags &= ~FOF_FILESONLY;
    shfo.fAnyOperationsAborted = FALSE;
    ret = SHFileOperation(&shfo);
        ok(ret == ERROR_ACCESS_DENIED, "Expected ERROR_ACCESS_DENIED, got %ld\n", ret);
    ok(!shfo.fAnyOperationsAborted, "Expected no aborted operations\n");
    ok(file_exists("test1.txt"), "Expected test1.txt to exist\n");

    /* try an invalid function */
    init_shfo_tests();
    shfo.pFrom = "test1.txt\0";
    shfo.wFunc = 0;
    ret = SHFileOperation(&shfo);
        ok(ret == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %ld\n", ret);
    ok(file_exists("test1.txt"), "Expected test1.txt to exist\n");

    /* try an invalid list, only one null terminator */
    init_shfo_tests();
    shfo.pFrom = "";
    shfo.wFunc = FO_DELETE;
    ret = SHFileOperation(&shfo);
        ok(ret == ERROR_ACCESS_DENIED, "Expected ERROR_ACCESS_DENIED, got %ld\n", ret);
    ok(file_exists("test1.txt"), "Expected test1.txt to exist\n");

    /* delete a dir, and then a file inside the dir, same as
    * deleting a nonexistent file
    */
    init_shfo_tests();
    shfo.pFrom = "testdir2\0testdir2\\one.txt\0";
    ret = SHFileOperation(&shfo);
        ok(ret == ERROR_PATH_NOT_FOUND, "Expected ERROR_PATH_NOT_FOUND, got %ld\n", ret);
        ok(!file_exists("testdir2"), "Expected testdir2 to not exist\n");
    ok(!file_exists("testdir2\\one.txt"), "Expected testdir2\\one.txt to not exist\n");

    /* try the FOF_NORECURSION flag, continues deleting subdirs */
    init_shfo_tests();
    shfo.pFrom = "testdir2\0";
    shfo.fFlags |= FOF_NORECURSION;
    ret = SHFileOperation(&shfo);
        ok(ret == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %ld\n", ret);
        ok(!file_exists("testdir2\\one.txt"), "Expected testdir2\\one.txt to not exist\n");
        ok(!file_exists("testdir2\\nested"), "Expected testdir2\\nested to exist\n");
}