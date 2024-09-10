static VOID
SetListBoxColumns(HWND hwndListBox)
{
    RECT rect = {0, 0, 103, 0};
    MapDialogRect(hwndListBox, &rect);

    SendMessage(hwndListBox, LB_SETTABSTOPS, (WPARAM)1, (LPARAM)&rect.right);
}