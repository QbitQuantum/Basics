void MusPlayer_WinAPI::on_open_clicked()
{
    OPENFILENAMEW open;
    memset(&open, 0, sizeof(open));

    wchar_t flnm[MAX_PATH];
    flnm[0]=L'\0';
    open.lStructSize = sizeof(OPENFILENAMEW);
    open.hInstance = m_hInstance;
    open.hwndOwner = m_hWnd;
    open.lpstrFilter = L"All files (*.*)\0*.*";
    open.lpstrDefExt = L"\0";
    open.lpstrFile = flnm;
    open.nMaxFile = MAX_PATH;
    open.lpstrTitle = L"Open music file to play...";
    open.Flags = OFN_FILEMUSTEXIST;
    if(GetOpenFileNameW(&open)==TRUE)
    {
        currentMusic = Wstr2Str(open.lpstrFile);
    } else {
        return;
    }

    Mix_HaltMusic();
    on_play_clicked();
}