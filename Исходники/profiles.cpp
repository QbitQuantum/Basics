// assumes UnregisterHotKeys was called before
static int RegisterHotKeys()
{
    hMessageWindow = CreateWindowEx(0, _T("STATIC"), NULL, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
    SetWindowLongPtr(hMessageWindow, GWLP_WNDPROC, (LONG_PTR)MessageWndProc);

    int count = GetProfileCount(0, 0);
    for ( int i=0; i < count; i++ ) {
        if (!db_get_b(NULL, MODULENAME, OptName(i, SETTING_REGHOTKEY), 0))
            continue;

        WORD wHotKey = db_get_w(NULL, MODULENAME, OptName(i, SETTING_HOTKEY), 0);
        hkInfo = ( HKINFO* )realloc(hkInfo, (hkiCount+1)*sizeof(HKINFO));
        if (hkInfo == NULL)
            return -1;

        char atomname[255];
        mir_snprintf(atomname, _countof(atomname), "StatusProfile_%d", i);
        hkInfo[hkiCount].id = GlobalAddAtomA(atomname);
        if (hkInfo[hkiCount].id == 0)
            continue;

        hkInfo[hkiCount].profile = i;
        hkiCount ++;
        RegisterHotKey(hMessageWindow, (int)hkInfo[hkiCount-1].id, GetFsModifiers(wHotKey), LOBYTE(wHotKey));
    }

    if (hkiCount == 0)
        UnregisterHotKeys();

    return 0;
}