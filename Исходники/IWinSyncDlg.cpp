BOOL CIWinSyncDlg::ShowStatusBalloon(UINT uID)
{
    // Display a balloon message for a sync job with a custom icon
    NOTIFYICONDATA nid = {sizeof(nid)};
    nid.uFlags = NIF_INFO | NIF_GUID;
    nid.guidItem = __uuidof(CIWinSyncDlg);
    nid.dwInfoFlags = NIIF_USER | NIIF_LARGE_ICON;
	LoadString(g_hInst, IDS_STATUS_TITLE, nid.szInfoTitle, ARRAYSIZE(nid.szInfoTitle));
    LoadString(g_hInst, uID, nid.szInfo, ARRAYSIZE(nid.szInfo));
    LoadIconMetric(g_hInst, MAKEINTRESOURCE(IDR_MAINFRAME), LIM_LARGE, &nid.hBalloonIcon);
    return Shell_NotifyIcon(NIM_MODIFY, &nid);
}