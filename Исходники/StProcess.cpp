StString StProcess::getWindowsFolder() {
    StString aWinFolder;
    stUtfWide_t aWndFldr[MAX_PATH];
    GetWindowsDirectoryW(aWndFldr, MAX_PATH);
    aWndFldr[MAX_PATH - 1] = L'\0';
    aWinFolder = StString(aWndFldr) + SYS_FS_SPLITTER;
    return aWinFolder;
}