int MyOpen(HWND hEdit)
{
    int id;
    HWND hMain;
    DWORD dwSize = 0L;
    OPENFILENAME ofn;
    HANDLE hFile;
    DWORD dwAccBytes;
    LPTSTR lpszBuf;

    HGLOBAL hMem;

    id = MyConfirm(hEdit);
    if (id == IDCANCEL)
        return -1;

    // OPENFILENAME構造体を設定
    memset(&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hEdit;
    ofn.lpstrFilter =
        TEXT("text(*.txt)\0*.txt\0All files(*.*)\0*.*\0\0");
    ofn.lpstrFile = szFile;
    ofn.lpstrFileTitle = szFileTitle;
    ofn.nMaxFile = MAX_PATH;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = TEXT("txt");
    ofn.lpstrTitle = TEXT("猫でもわかるファイルオープン");

    if(GetOpenFileName(&ofn) == 0)  // 「ファイルを開く」ダイアログ
        return -1;

    hFile = CreateFile(szFile,  // ファイル名
        GENERIC_READ,           // 読み取り/書き込みアクセス
        0,                      // 共有設定 0だと共有対象としない
        NULL,                   // セキュリティ属性
        OPEN_ALWAYS,            // ファイルがすでに存在しているかどうか
        FILE_ATTRIBUTE_NORMAL,  // ファイル属性
        NULL);
    dwSize = GetFileSize(hFile, NULL);  // ファイルサイズを取得

    // メモリを動的に確保
    hMem = GlobalAlloc(GHND, dwSize + sizeof(TCHAR));
    if (hMem == NULL) {
        MessageBox(hEdit, TEXT("メモリを確保できません"),
                   TEXT("猫でもわかるメモ帳もどき"),
                   MB_ICONEXCLAMATION | MB_OK);
        return -1;
    }
    lpszBuf = (LPTSTR)GlobalLock(hMem);

    // ファイルを読み込み、エディットコントロールに表示する
    ReadFile(hFile, lpszBuf, dwSize, &dwAccBytes, NULL);
    lpszBuf[dwAccBytes] = TEXT('\0');
    Edit_SetText(hEdit, lpszBuf);

    // タイトルバーの設定
    wsprintf(szTitle, szTitle_org, szFileTitle, dwSize);
    hMain = GetParent(hEdit);
    SetWindowText(hMain, szTitle);

    CloseHandle(hFile);
    GlobalUnlock(hMem);
    GlobalFree(hMem);

    return 0;
}