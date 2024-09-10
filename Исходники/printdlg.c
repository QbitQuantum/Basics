static void test_PageSetupDlgA(void)
{
    LPPAGESETUPDLGA pDlg;
    DWORD res;

    pDlg = HeapAlloc(GetProcessHeap(), 0, (sizeof(PAGESETUPDLGA)) * 2);
    if (!pDlg) return;

    SetLastError(0xdeadbeef);
    res = PageSetupDlgA(NULL);
    ok( !res && (CommDlgExtendedError() == CDERR_INITIALIZATION),
        "returned %u with %u and 0x%x (expected '0' and "
        "CDERR_INITIALIZATION)\n", res, GetLastError(), CommDlgExtendedError());

    ZeroMemory(pDlg, sizeof(PAGESETUPDLGA));
    pDlg->lStructSize = sizeof(PAGESETUPDLGA) -1;
    SetLastError(0xdeadbeef);
    res = PageSetupDlgA(pDlg);
    ok( !res && (CommDlgExtendedError() == CDERR_STRUCTSIZE),
        "returned %u with %u and 0x%x (expected '0' and "
        "CDERR_STRUCTSIZE)\n", res, GetLastError(), CommDlgExtendedError());

    ZeroMemory(pDlg, sizeof(PAGESETUPDLGA));
    pDlg->lStructSize = sizeof(PAGESETUPDLGA) +1;
    pDlg->Flags = PSD_RETURNDEFAULT;
    SetLastError(0xdeadbeef);
    res = PageSetupDlgA(pDlg);
    ok( !res && (CommDlgExtendedError() == CDERR_STRUCTSIZE),
        "returned %u with %u and 0x%x (expected '0' and CDERR_STRUCTSIZE)\n",
        res, GetLastError(), CommDlgExtendedError());


    ZeroMemory(pDlg, sizeof(PAGESETUPDLGA));
    pDlg->lStructSize = sizeof(PAGESETUPDLGA);
    pDlg->Flags = PSD_RETURNDEFAULT | PSD_NOWARNING;
    SetLastError(0xdeadbeef);
    res = PageSetupDlgA(pDlg);
    ok( res || (CommDlgExtendedError() == PDERR_NODEFAULTPRN),
        "returned %u with %u and 0x%x (expected '!= 0' or '0' and "
        "PDERR_NODEFAULTPRN)\n", res, GetLastError(), CommDlgExtendedError());

    if (!res && (CommDlgExtendedError() == PDERR_NODEFAULTPRN)) {
        skip("No printer configured.\n");
        HeapFree(GetProcessHeap(), 0, pDlg);
        return;
    }

    ok( pDlg->hDevMode && pDlg->hDevNames,
        "got %p and %p (expected '!= NULL' for both)\n",
        pDlg->hDevMode, pDlg->hDevNames);

    GlobalFree(pDlg->hDevMode);
    GlobalFree(pDlg->hDevNames);

    HeapFree(GetProcessHeap(), 0, pDlg);

}