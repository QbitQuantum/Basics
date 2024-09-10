INT_PTR CALLBACK
about_dlg_proc(HWND hwnd,
               UINT uMsg,
               WPARAM wParam,
               LPARAM lParam) {

    switch(uMsg) {
    case WM_INITDIALOG:
        {
            HANDLE hsnap;
            HWND hw;

            SetDlgItemText(hwnd, IDC_PRODUCT,
                           TEXT(KH_VERSTR_PRODUCT_1033));
            /* retain the original copyright strings */
#ifdef OVERRIDE_COPYRIGHT
            SetDlgItemText(hwnd, IDC_COPYRIGHT,
                           TEXT(KH_VERSTR_COPYRIGHT_1033));
#endif
            SetDlgItemText(hwnd, IDC_BUILDINFO,
                           TEXT(KH_VERSTR_BUILDINFO_1033));

            hsnap =
                CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,
                                         0);

            if (hsnap != INVALID_HANDLE_VALUE) {
                LVCOLUMN lvc;
                MODULEENTRY32 mod;
                RECT r;

                hw = GetDlgItem(hwnd, IDC_MODULES);
#ifdef DEBUG
                assert(hw != NULL);
#endif

                GetWindowRect(hw, &r);
                OffsetRect(&r, -r.left, -r.top);

                ZeroMemory(&lvc, sizeof(lvc));
                lvc.mask = LVCF_TEXT | LVCF_WIDTH;

                lvc.pszText = L"Name";
                lvc.cx = r.right / 4;

                ListView_InsertColumn(hw, 0, &lvc);

                lvc.pszText = L"Path";
                lvc.cx = (r.right * 3) / 4;
                ListView_InsertColumn(hw, 1, &lvc);

                ZeroMemory(&mod, sizeof(mod));
                mod.dwSize = sizeof(mod);

                /* done with columns, now for the actual data */
                if (!Module32First(hsnap, &mod))
                    goto _done_with_modules;

                do {

                    LVITEM lvi;
                    int idx;

                    ZeroMemory(&lvi, sizeof(lvi));

                    lvi.mask = LVIF_TEXT;
                    lvi.pszText = mod.szModule;
                    idx = ListView_InsertItem(hw, &lvi);

                    lvi.mask = LVIF_TEXT;
                    lvi.iItem = idx;
                    lvi.iSubItem = 1;
                    lvi.pszText = mod.szExePath;
                    ListView_SetItem(hw, &lvi);

                    ZeroMemory(&mod, sizeof(mod));
                    mod.dwSize = sizeof(mod);
                } while(Module32Next(hsnap, &mod));

            _done_with_modules:
                CloseHandle(hsnap);
            }
        }
        return FALSE;

    case WM_DESTROY:
        return TRUE;

    case WM_CLOSE:
        EndDialog(hwnd, 0);
        return TRUE;

    case WM_COMMAND:
        if (wParam == MAKEWPARAM(IDOK, BN_CLICKED)) {
            EndDialog(hwnd, 0);
        }
        return TRUE;
    }

    return FALSE;
}