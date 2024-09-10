static void test_info_size(void)
{   DWORD hdl, retval;
    char mypath[MAX_PATH] = "";

    SetLastError(MY_LAST_ERROR);
    retval = GetFileVersionInfoSizeA( NULL, NULL);
    ok( !retval,
	"GetFileVersionInfoSizeA result wrong! 0L expected, got 0x%08x\n",
	retval);
    EXPECT_INVALID__NOT_FOUND;

    hdl = 0x55555555;
    SetLastError(MY_LAST_ERROR);
    retval = GetFileVersionInfoSizeA( NULL, &hdl);
    ok( !retval,
	"GetFileVersionInfoSizeA result wrong! 0L expected, got 0x%08x\n",
	retval);
    EXPECT_INVALID__NOT_FOUND;
    ok( hdl == 0L,
	"Handle wrong! 0L expected, got 0x%08x\n", hdl);

    SetLastError(MY_LAST_ERROR);
    retval = GetFileVersionInfoSizeA( "", NULL);
    ok( !retval,
	"GetFileVersionInfoSizeA result wrong! 0L expected, got 0x%08x\n",
	retval);
    EXPECT_BAD_PATH__NOT_FOUND;

    hdl = 0x55555555;
    SetLastError(MY_LAST_ERROR);
    retval = GetFileVersionInfoSizeA( "", &hdl);
    ok( !retval,
	"GetFileVersionInfoSizeA result wrong! 0L expected, got 0x%08x\n",
	retval);
    EXPECT_BAD_PATH__NOT_FOUND;
    ok( hdl == 0L,
	"Handle wrong! 0L expected, got 0x%08x\n", hdl);

    SetLastError(MY_LAST_ERROR);
    retval = GetFileVersionInfoSizeA( "kernel32.dll", NULL);
    ok( retval,
	"GetFileVersionInfoSizeA result wrong! <> 0L expected, got 0x%08x\n",
	retval);
    ok((NO_ERROR == GetLastError()) || (MY_LAST_ERROR == GetLastError()),
	"Last error wrong! NO_ERROR/0x%08x (NT4)  expected, got %u\n",
	MY_LAST_ERROR, GetLastError());

    hdl = 0x55555555;
    SetLastError(MY_LAST_ERROR);
    retval = GetFileVersionInfoSizeA( "kernel32.dll", &hdl);
    ok( retval,
	"GetFileVersionInfoSizeA result wrong! <> 0L expected, got 0x%08x\n",
	retval);
    ok((NO_ERROR == GetLastError()) || (MY_LAST_ERROR == GetLastError()),
	"Last error wrong! NO_ERROR/0x%08x (NT4)  expected, got %u\n",
	MY_LAST_ERROR, GetLastError());
    ok( hdl == 0L,
	"Handle wrong! 0L expected, got 0x%08x\n", hdl);

    SetLastError(MY_LAST_ERROR);
    retval = GetFileVersionInfoSizeA( "notexist.dll", NULL);
    ok( !retval,
	"GetFileVersionInfoSizeA result wrong! 0L expected, got 0x%08x\n",
	retval);
    ok( (ERROR_FILE_NOT_FOUND == GetLastError()) ||
	(ERROR_RESOURCE_DATA_NOT_FOUND == GetLastError()) ||
	(MY_LAST_ERROR == GetLastError()) ||
	(ERROR_SUCCESS == GetLastError()), /* win2k */
	"Last error wrong! ERROR_FILE_NOT_FOUND/ERROR_RESOURCE_DATA_NOT_FOUND "
	"(XP)/0x%08x (NT4) expected, got %u\n", MY_LAST_ERROR, GetLastError());

    /* test a currently loaded executable */
    if(GetModuleFileNameA(NULL, mypath, MAX_PATH)) {
	hdl = 0x55555555;
	SetLastError(MY_LAST_ERROR);
	retval = GetFileVersionInfoSizeA( mypath, &hdl);
	ok( retval,
            "GetFileVersionInfoSizeA result wrong! <> 0L expected, got 0x%08x\n",
	    retval);
	ok((NO_ERROR == GetLastError()) || (MY_LAST_ERROR == GetLastError()),
            "Last error wrong! NO_ERROR/0x%08x (NT4)  expected, got %u\n",
	    MY_LAST_ERROR, GetLastError());
	ok( hdl == 0L,
            "Handle wrong! 0L expected, got 0x%08x\n", hdl);
    }
    else
	trace("skipping GetModuleFileNameA(NULL,..) failed\n");

    /* test a not loaded executable */
    if(GetSystemDirectoryA(mypath, MAX_PATH)) {
	lstrcatA(mypath, "\\regsvr32.exe");

	if(INVALID_FILE_ATTRIBUTES == GetFileAttributesA(mypath))
	    trace("GetFileAttributesA(%s) failed\n", mypath);
	else {
	    hdl = 0x55555555;
	    SetLastError(MY_LAST_ERROR);
	    retval = GetFileVersionInfoSizeA( mypath, &hdl);
	    ok( retval,
		"GetFileVersionInfoSizeA result wrong! <> 0L expected, got 0x%08x\n",
		retval);
	    ok((NO_ERROR == GetLastError()) || (MY_LAST_ERROR == GetLastError()),
		"Last error wrong! NO_ERROR/0x%08x (NT4)  expected, got %u\n",
		MY_LAST_ERROR, GetLastError());
	    ok( hdl == 0L,
		"Handle wrong! 0L expected, got 0x%08x\n", hdl);
	}
    }
    else
	trace("skipping GetSystemDirectoryA(mypath,..) failed\n");

    create_file("test.txt");

    /* no version info */
    SetLastError(0xdeadbeef);
    hdl = 0xcafe;
    retval = GetFileVersionInfoSizeA("test.txt", &hdl);
    ok(retval == 0, "Expected 0, got %d\n", retval);
    ok(hdl == 0, "Expected 0, got %d\n", hdl);
    ok(GetLastError() == ERROR_RESOURCE_DATA_NOT_FOUND ||
       GetLastError() == ERROR_SUCCESS, /* win2k */
       "Expected ERROR_RESOURCE_DATA_NOT_FOUND, got %d\n", GetLastError());

    DeleteFileA("test.txt");
}