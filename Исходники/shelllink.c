static void test_get_set(void)
{
    HRESULT r;
    IShellLinkA *sl;
    IShellLinkW *slW = NULL;
    char mypath[MAX_PATH];
    char buffer[INFOTIPSIZE];
    LPITEMIDLIST pidl, tmp_pidl;
    const char * str;
    int i;
    WORD w;

    r = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                         &IID_IShellLinkA, (LPVOID*)&sl);
    ok(r == S_OK, "no IID_IShellLinkA (0x%08x)\n", r);
    if (r != S_OK)
        return;

    /* Test Getting / Setting the description */
    strcpy(buffer,"garbage");
    r = IShellLinkA_GetDescription(sl, buffer, sizeof(buffer));
    ok(r == S_OK, "GetDescription failed (0x%08x)\n", r);
    ok(*buffer=='\0', "GetDescription returned '%s'\n", buffer);

    str="Some description";
    r = IShellLinkA_SetDescription(sl, str);
    ok(r == S_OK, "SetDescription failed (0x%08x)\n", r);

    strcpy(buffer,"garbage");
    r = IShellLinkA_GetDescription(sl, buffer, sizeof(buffer));
    ok(r == S_OK, "GetDescription failed (0x%08x)\n", r);
    ok(lstrcmp(buffer,str)==0, "GetDescription returned '%s'\n", buffer);

    /* Test Getting / Setting the work directory */
    strcpy(buffer,"garbage");
    r = IShellLinkA_GetWorkingDirectory(sl, buffer, sizeof(buffer));
    ok(r == S_OK, "GetWorkingDirectory failed (0x%08x)\n", r);
    ok(*buffer=='\0', "GetWorkingDirectory returned '%s'\n", buffer);

    str="c:\\nonexistent\\directory";
    r = IShellLinkA_SetWorkingDirectory(sl, str);
    ok(r == S_OK, "SetWorkingDirectory failed (0x%08x)\n", r);

    strcpy(buffer,"garbage");
    r = IShellLinkA_GetWorkingDirectory(sl, buffer, sizeof(buffer));
    ok(r == S_OK, "GetWorkingDirectory failed (0x%08x)\n", r);
    ok(lstrcmpi(buffer,str)==0, "GetWorkingDirectory returned '%s'\n", buffer);

    /* Test Getting / Setting the path */
    strcpy(buffer,"garbage");
    r = IShellLinkA_GetPath(sl, buffer, sizeof(buffer), NULL, SLGP_RAWPATH);
    todo_wine ok(r == S_FALSE || broken(r == S_OK) /* NT4/W2K */, "GetPath failed (0x%08x)\n", r);
    ok(*buffer=='\0', "GetPath returned '%s'\n", buffer);

    CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                     &IID_IShellLinkW, (LPVOID*)&slW);
    if (!slW)
        skip("SetPath with NULL parameter crashes on Win9x\n");
    else
    {
        IShellLinkW_Release(slW);
        r = IShellLinkA_SetPath(sl, NULL);
        ok(r==E_INVALIDARG ||
           broken(r==S_OK), /* Some Win95 and NT4 */
           "SetPath failed (0x%08x)\n", r);
    }

    r = IShellLinkA_SetPath(sl, "");
    ok(r==S_OK, "SetPath failed (0x%08x)\n", r);

    strcpy(buffer,"garbage");
    r = IShellLinkA_GetPath(sl, buffer, sizeof(buffer), NULL, SLGP_RAWPATH);
    todo_wine ok(r == S_FALSE, "GetPath failed (0x%08x)\n", r);
    ok(*buffer=='\0', "GetPath returned '%s'\n", buffer);

    /* Win98 returns S_FALSE, but WinXP returns S_OK */
    str="c:\\nonexistent\\file";
    r = IShellLinkA_SetPath(sl, str);
    ok(r==S_FALSE || r==S_OK, "SetPath failed (0x%08x)\n", r);

    strcpy(buffer,"garbage");
    r = IShellLinkA_GetPath(sl, buffer, sizeof(buffer), NULL, SLGP_RAWPATH);
    ok(r == S_OK, "GetPath failed (0x%08x)\n", r);
    ok(lstrcmpi(buffer,str)==0, "GetPath returned '%s'\n", buffer);

    /* Get some real path to play with */
    GetWindowsDirectoryA( mypath, sizeof(mypath)-12 );
    strcat(mypath, "\\regedit.exe");

    /* Test the interaction of SetPath and SetIDList */
    tmp_pidl=NULL;
    r = IShellLinkA_GetIDList(sl, &tmp_pidl);
    todo_wine ok(r == S_OK, "GetIDList failed (0x%08x)\n", r);
    if (r == S_OK)
    {
        BOOL ret;

        strcpy(buffer,"garbage");
        ret = SHGetPathFromIDListA(tmp_pidl, buffer);
        todo_wine {
        ok(ret, "SHGetPathFromIDListA failed\n");
        }
        if (ret)
            ok(lstrcmpi(buffer,str)==0, "GetIDList returned '%s'\n", buffer);
        pILFree(tmp_pidl);
    }