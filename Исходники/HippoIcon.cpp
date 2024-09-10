void
HippoIcon::updateTip(const WCHAR *tip)
{
    NOTIFYICONDATA notifyIconData = { 0 };
    notifyIconData.uID = 0;
    notifyIconData.hWnd = window_;
    notifyIconData.uFlags = NIF_TIP;
    StringCchCopyW(notifyIconData.szTip, 
                   sizeof(notifyIconData.szTip) / sizeof(notifyIconData.szTip[0]),
                   tip);
    notifyIconData.szTip;
    Shell_NotifyIcon(NIM_MODIFY, &notifyIconData);
}