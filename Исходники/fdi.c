static void test_FDIIsCabinet(void)
{
    ERF erf;
    BOOL ret;
    HFDI hfdi;
    INT_PTR fd;
    FDICABINETINFO cabinfo;
    char temp[] = "temp.txt";
    char extract[] = "extract.cab";

    create_test_files();
    create_cab_file();

    hfdi = FDICreate(fdi_alloc, fdi_free, fdi_open, fdi_read,
                     fdi_write, fdi_close, fdi_seek,
                     cpuUNKNOWN, &erf);
    ok(hfdi != NULL, "Expected non-NULL context\n");

    /* native crashes if hfdi or cabinfo are NULL or invalid */

    /* invalid file handle */
    ZeroMemory(&cabinfo, sizeof(FDICABINETINFO));
    SetLastError(0xdeadbeef);
    ret = FDIIsCabinet(hfdi, -1, &cabinfo);
    ok(ret == FALSE, "Expected FALSE, got %d\n", ret);
    ok(GetLastError() == ERROR_INVALID_HANDLE,
       "Expected ERROR_INVALID_HANDLE, got %d\n", GetLastError());
    ok(cabinfo.cbCabinet == 0, "Expected 0, got %d\n", cabinfo.cbCabinet);
    ok(cabinfo.cFiles == 0, "Expected 0, got %d\n", cabinfo.cFiles);
    ok(cabinfo.cFolders == 0, "Expected 0, got %d\n", cabinfo.cFolders);
    ok(cabinfo.iCabinet == 0, "Expected 0, got %d\n", cabinfo.iCabinet);
    ok(cabinfo.setID == 0, "Expected 0, got %d\n", cabinfo.setID);

    createTestFile("temp.txt");
    fd = fdi_open(temp, 0, 0);

    /* file handle doesn't point to a cabinet */
    ZeroMemory(&cabinfo, sizeof(FDICABINETINFO));
    SetLastError(0xdeadbeef);
    ret = FDIIsCabinet(hfdi, fd, &cabinfo);
    ok(ret == FALSE, "Expected FALSE, got %d\n", ret);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());
    ok(cabinfo.cbCabinet == 0, "Expected 0, got %d\n", cabinfo.cbCabinet);
    ok(cabinfo.cFiles == 0, "Expected 0, got %d\n", cabinfo.cFiles);
    ok(cabinfo.cFolders == 0, "Expected 0, got %d\n", cabinfo.cFolders);
    ok(cabinfo.iCabinet == 0, "Expected 0, got %d\n", cabinfo.iCabinet);
    ok(cabinfo.setID == 0, "Expected 0, got %d\n", cabinfo.setID);

    fdi_close(fd);
    DeleteFileA("temp.txt");

    /* try a real cab */
    fd = fdi_open(extract, 0, 0);
    ZeroMemory(&cabinfo, sizeof(FDICABINETINFO));
    SetLastError(0xdeadbeef);
    ret = FDIIsCabinet(hfdi, fd, &cabinfo);
    ok(ret == TRUE, "Expected TRUE, got %d\n", ret);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());
    ok(cabinfo.cFiles == 4, "Expected 4, got %d\n", cabinfo.cFiles);
    ok(cabinfo.cFolders == 1, "Expected 1, got %d\n", cabinfo.cFolders);
    ok(cabinfo.setID == 0xbeef, "Expected 0xbeef, got %d\n", cabinfo.setID);
    todo_wine
    {
        ok(cabinfo.cbCabinet == 182, "Expected 182, got %d\n", cabinfo.cbCabinet);
        ok(cabinfo.iCabinet == 0, "Expected 0, got %d\n", cabinfo.iCabinet);
    }

    fdi_close(fd);
    FDIDestroy(hfdi);
    delete_test_files();
}