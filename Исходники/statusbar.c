void khm_statusbar_set_part(int id, HICON icon, wchar_t * text) {
    int idx;

    if (!khm_hwnd_statusbar)
        return;

    idx = sb_find_index(id);
    if(idx < 0)
        return;

    if (khm_statusbar_parts[idx].hIcon != NULL) {
        DestroyIcon(khm_statusbar_parts[idx].hIcon);
        khm_statusbar_parts[idx].hIcon = NULL;
    }

    if (icon) {
        khm_statusbar_parts[idx].hIcon = CopyImage(icon, IMAGE_ICON,
                                                   GetSystemMetrics(SM_CXSMICON),
                                                   GetSystemMetrics(SM_CYSMICON),
                                                   LR_COPYFROMRESOURCE);
    }

    SendMessage(khm_hwnd_statusbar,
                SB_SETICON,
                idx,
                (LPARAM) (khm_statusbar_parts[idx].hIcon ? khm_statusbar_parts[idx].hIcon:icon));

    SendMessage(khm_hwnd_statusbar,
                SB_SETTEXT,
                idx,
                (LPARAM) text);
}