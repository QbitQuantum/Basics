/*********************************************************************
 * delhist_on_command [internal]
 *
 * handle WM_COMMAND in Delete browsing history dialog
 *
 */
static INT_PTR delhist_on_command(HWND hdlg, WPARAM wparam)
{
    switch (wparam)
    {
        case MAKEWPARAM(IDOK, BN_CLICKED):
            if (IsDlgButtonChecked(hdlg, IDC_DELETE_TEMP_FILES))
                FreeUrlCacheSpaceW(NULL, 100, 0);

            if (IsDlgButtonChecked(hdlg, IDC_DELETE_COOKIES))
            {
                WCHAR pathW[MAX_PATH];

                if(SHGetSpecialFolderPathW(NULL, pathW, CSIDL_COOKIES, TRUE))
                    FreeUrlCacheSpaceW(pathW, 100, 0);
            }

            if (IsDlgButtonChecked(hdlg, IDC_DELETE_HISTORY))
            {
                WCHAR pathW[MAX_PATH];

                if(SHGetSpecialFolderPathW(NULL, pathW, CSIDL_HISTORY, TRUE))
                    FreeUrlCacheSpaceW(pathW, 100, 0);
            }

            EndDialog(hdlg, IDOK);
            return TRUE;

        case MAKEWPARAM(IDCANCEL, BN_CLICKED):
            EndDialog(hdlg, IDCANCEL);
            return TRUE;

        case MAKEWPARAM(IDC_DELETE_TEMP_FILES, BN_CLICKED):
        case MAKEWPARAM(IDC_DELETE_COOKIES, BN_CLICKED):
        case MAKEWPARAM(IDC_DELETE_HISTORY, BN_CLICKED):
        case MAKEWPARAM(IDC_DELETE_FORM_DATA, BN_CLICKED):
        case MAKEWPARAM(IDC_DELETE_PASSWORDS, BN_CLICKED):
        {
            BOOL any = IsDlgButtonChecked(hdlg, IDC_DELETE_TEMP_FILES) ||
                       IsDlgButtonChecked(hdlg, IDC_DELETE_COOKIES) ||
                       IsDlgButtonChecked(hdlg, IDC_DELETE_HISTORY) ||
                       IsDlgButtonChecked(hdlg, IDC_DELETE_FORM_DATA) ||
                       IsDlgButtonChecked(hdlg, IDC_DELETE_PASSWORDS);
            EnableWindow(GetDlgItem(hdlg, IDOK), any);
            break;
        }

        default:
            break;
    }
    return FALSE;
}