static void
trayicon_set_icon (SeafileTrayIcon *icon, HICON hIcon)
{
    int ret;
    unsigned int msg;
    HICON prev_icon;

    if (!hIcon || hIcon == icon->nid.hIcon)
        return;

    msg = icon->nid.hIcon? NIM_MODIFY : NIM_ADD;

    prev_icon = icon->nid.hIcon;
    icon->nid.hIcon = hIcon;
    icon->nid.uFlags = NIF_ICON;

    ret = Shell_NotifyIconW (msg, &icon->nid);

    if (!ret) {
        applet_warning ("trayicon_set_icon failed, GLE=%lu\n", GetLastError());
        icon->nid.hIcon = prev_icon;
    }
}