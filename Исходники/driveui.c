static INT_PTR CALLBACK drivechoose_dlgproc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int i, sel;
    char c;
    char drive[] = "X:";

    switch(uMsg)
    {
    case WM_INITDIALOG:
        {
        ULONG mask = ~drive_available_mask(0); /* the mask is now which drives aren't available */
        for( c = 'A'; c<= 'Z'; c++){
            drive[0] = c;
            if(!( mask & (1 << (c - 'A'))))
                SendDlgItemMessageA( hwndDlg, IDC_DRIVESA2Z, CB_ADDSTRING, 0, (LPARAM) drive);
        }
        drive[0] = lParam;
        SendDlgItemMessageA( hwndDlg, IDC_DRIVESA2Z, CB_SELECTSTRING, 0, (LPARAM) drive);
        return TRUE;
        }
    case WM_COMMAND:
        if(HIWORD(wParam) != BN_CLICKED) break;
        switch (LOWORD(wParam))
        {
        case IDOK:
            i = SendDlgItemMessageA( hwndDlg, IDC_DRIVESA2Z, CB_GETCURSEL, 0, 0);
            if( i != CB_ERR){
                SendDlgItemMessageA( hwndDlg, IDC_DRIVESA2Z, CB_GETLBTEXT, i, (LPARAM) drive);
                sel = drive[0];
            } else
                sel = -1;
            EndDialog(hwndDlg, sel);
            return TRUE;
        case IDCANCEL:
            EndDialog(hwndDlg, -1);
            return TRUE;
        }
    }
    return FALSE;
}