void TCCFrm::FrmCopyFileToClipboard()
{
    HGLOBAL hGblFiles;
    unsigned char *gblBuf;
    DROPFILES dropFiles;
    WCHAR szWinDir[MAX_PATH];
    WCHAR filename[1024];
    int lenWinDir, flen, len;
    dropFiles.pFiles = sizeof(DROPFILES);
    dropFiles.pt.x = 0;
    dropFiles.pt.y = 0;
    dropFiles.fNC = FALSE;
    dropFiles.fWide = TRUE;
    GetWindowsDirectoryW(szWinDir, MAX_PATH);
    lenWinDir = wcslen(szWinDir);
    memset(filename, 0, 1024 * sizeof(WCHAR));
    memcpy(filename, szWinDir, lenWinDir * sizeof(WCHAR));
    memcpy(filename + lenWinDir, L"\\Fonts\\", 7 * sizeof(WCHAR));
    GetWindowTextW(m_hEditFileName, filename + lenWinDir + 7, 512);
    flen = wcslen(filename) + 2;
    len = sizeof(DROPFILES) + flen * sizeof(WCHAR) + 2;
    hGblFiles = GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE, len);
    gblBuf = (unsigned char *)GlobalLock(hGblFiles);
    memcpy(gblBuf, &dropFiles, sizeof(DROPFILES));
    memcpy(gblBuf + sizeof(DROPFILES), filename, flen * sizeof(WCHAR));
    GlobalUnlock(hGblFiles);
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_HDROP, hGblFiles);
    CloseClipboard();
}