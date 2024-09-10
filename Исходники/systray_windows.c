void setIcon(const wchar_t* iconFile, int lenth) {
    HICON hIcon = (HICON) LoadImageW(NULL, iconFile, IMAGE_ICON, 64, 64, LR_LOADFROMFILE);
    if (hIcon == NULL) {
        reportWindowsError("load icon image");
    } else {
        nid.hIcon = hIcon;
        nid.uFlags = NIF_ICON;
        Shell_NotifyIcon(NIM_MODIFY, &nid);
    }
}