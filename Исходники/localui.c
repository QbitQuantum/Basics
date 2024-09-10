static INT_PTR CALLBACK dlgproc_addport(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    addportui_t * data;
    DWORD   status;
    DWORD   dummy;
    DWORD   len;
    DWORD   res;

    switch(msg)
    {
    case WM_INITDIALOG:
        SetWindowLongPtrW(hwnd, DWLP_USER, lparam);
        return TRUE;

    case WM_COMMAND:
        if (wparam == MAKEWPARAM(IDOK, BN_CLICKED))
        {
            data = (addportui_t *) GetWindowLongPtrW(hwnd, DWLP_USER);
            /* length in WCHAR, without the '\0' */
            len = SendDlgItemMessageW(hwnd, ADDPORT_EDIT, WM_GETTEXTLENGTH, 0, 0);
            data->portname = HeapAlloc(GetProcessHeap(), 0, (len + 1) * sizeof(WCHAR));

            if (!data->portname) {
                EndDialog(hwnd, FALSE);
                return TRUE;
            }
            /* length is in WCHAR, including the '\0' */
            GetDlgItemTextW(hwnd, ADDPORT_EDIT, data->portname, len + 1);
            status = ERROR_SUCCESS;
            res = XcvDataW( data->hXcv, cmd_PortIsValidW, (PBYTE) data->portname,
                            (lstrlenW(data->portname) + 1) * sizeof(WCHAR),
                            (PBYTE) &dummy, 0, &len, &status);

            TRACE("got %u with status %u\n", res, status);
            if (res && (status == ERROR_SUCCESS)) {
                /* The caller must free data->portname */
                EndDialog(hwnd, TRUE);
                return TRUE;
            }

            if (res && (status == ERROR_INVALID_NAME)) {
                dlg_invalid_portname(hwnd, data->portname);
                HeapFree(GetProcessHeap(), 0, data->portname);
                data->portname = NULL;
                return TRUE;
            }

            dlg_win32error(hwnd, status);
            HeapFree(GetProcessHeap(), 0, data->portname);
            data->portname = NULL;
            return TRUE;
        }

        if (wparam == MAKEWPARAM(IDCANCEL, BN_CLICKED))
        {
            EndDialog(hwnd, FALSE);
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}