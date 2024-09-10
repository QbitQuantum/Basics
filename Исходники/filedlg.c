/* bug 6829 */
static void test_DialogCancel(void)
{
    OPENFILENAMEA ofn;
    BOOL result;
    char szFileName[MAX_PATH] = "";
    char szInitialDir[MAX_PATH];

    GetWindowsDirectory(szInitialDir, MAX_PATH);

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_ENABLEHOOK;
    ofn.lpstrDefExt = "txt";
    ofn.lpfnHook = OFNHookProc;
    ofn.lpstrInitialDir = szInitialDir;

    PrintDlgA(NULL);
    ok(CDERR_INITIALIZATION == CommDlgExtendedError(),
       "expected CDERR_INITIALIZATION, got %d\n", CommDlgExtendedError());

    result = GetOpenFileNameA(&ofn);
    ok(0 == result, "expected 0, got %d\n", result);
    ok(0 == CommDlgExtendedError(), "expected 0, got %d\n",
       CommDlgExtendedError());

    PrintDlgA(NULL);
    ok(CDERR_INITIALIZATION == CommDlgExtendedError(),
       "expected CDERR_INITIALIZATION, got %d\n", CommDlgExtendedError());

    result = GetSaveFileNameA(&ofn);
    ok(0 == result, "expected 0, got %d\n", result);
    ok(0 == CommDlgExtendedError(), "expected 0, got %d\n",
       CommDlgExtendedError());

    PrintDlgA(NULL);
    ok(CDERR_INITIALIZATION == CommDlgExtendedError(),
       "expected CDERR_INITIALIZATION, got %d\n", CommDlgExtendedError());

    /* Before passing the ofn to Unicode functions, remove the ANSI strings */
    ofn.lpstrFilter = NULL;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrDefExt = NULL;

    PrintDlgA(NULL);
    ok(CDERR_INITIALIZATION == CommDlgExtendedError(),
       "expected CDERR_INITIALIZATION, got %d\n", CommDlgExtendedError());

    SetLastError(0xdeadbeef);
    result = GetOpenFileNameW((LPOPENFILENAMEW) &ofn);
    if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
        win_skip("GetOpenFileNameW is not implemented\n");
    else
    {
        ok(0 == result, "expected 0, got %d\n", result);
        ok(0 == CommDlgExtendedError() ||
           broken(CDERR_INITIALIZATION == CommDlgExtendedError()), /* win9x */
           "expected 0, got %d\n", CommDlgExtendedError());
    }

    SetLastError(0xdeadbeef);
    result = GetSaveFileNameW((LPOPENFILENAMEW) &ofn);
    if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
        win_skip("GetSaveFileNameW is not implemented\n");
    else
    {
        ok(0 == result, "expected 0, got %d\n", result);
        ok(0 == CommDlgExtendedError() ||
           broken(CDERR_INITIALIZATION == CommDlgExtendedError()), /* win9x */
           "expected 0, got %d\n", CommDlgExtendedError());
    }
}