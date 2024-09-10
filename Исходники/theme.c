static void update_shell_folder_listview(HWND dialog) {
    int i;
    LVITEMW item;
    LONG lSelected = SendDlgItemMessageW(dialog, IDC_LIST_SFPATHS, LVM_GETNEXTITEM, -1,
                                        MAKELPARAM(LVNI_SELECTED,0));

    SendDlgItemMessageW(dialog, IDC_LIST_SFPATHS, LVM_DELETEALLITEMS, 0, 0);

    for (i=0; i<NUM_ELEMS(asfiInfo); i++) {
        WCHAR buffer[MAX_PATH];
        HRESULT hr;
        LPITEMIDLIST pidlCurrent;

        /* Some acrobatic to get the localized name of the shell folder */
        hr = SHGetFolderLocation(dialog, asfiInfo[i].nFolder, NULL, 0, &pidlCurrent);
        if (SUCCEEDED(hr)) { 
            LPSHELLFOLDER psfParent;
            LPCITEMIDLIST pidlLast;
            hr = SHBindToParent(pidlCurrent, &IID_IShellFolder, (LPVOID*)&psfParent, &pidlLast);
            if (SUCCEEDED(hr)) {
                STRRET strRet;
                hr = IShellFolder_GetDisplayNameOf(psfParent, pidlLast, SHGDN_FORADDRESSBAR, &strRet);
                if (SUCCEEDED(hr)) {
                    hr = StrRetToBufW(&strRet, pidlLast, buffer, MAX_PATH);
                }
                IShellFolder_Release(psfParent);
            }
            ILFree(pidlCurrent);
        }

        /* If there's a dangling symlink for the current shell folder, SHGetFolderLocation
         * will fail above. We fall back to the (non-verified) path of the shell folder. */
        if (FAILED(hr)) {
            hr = SHGetFolderPathW(dialog, asfiInfo[i].nFolder|CSIDL_FLAG_DONT_VERIFY, NULL,
                                 SHGFP_TYPE_CURRENT, buffer);
        }
    
        item.mask = LVIF_TEXT | LVIF_PARAM;
        item.iItem = i;
        item.iSubItem = 0;
        item.pszText = buffer;
        item.lParam = (LPARAM)&asfiInfo[i];
        SendDlgItemMessageW(dialog, IDC_LIST_SFPATHS, LVM_INSERTITEMW, 0, (LPARAM)&item);

        item.mask = LVIF_TEXT;
        item.iItem = i;
        item.iSubItem = 1;
        item.pszText = strdupU2W(asfiInfo[i].szLinkTarget);
        SendDlgItemMessageW(dialog, IDC_LIST_SFPATHS, LVM_SETITEMW, 0, (LPARAM)&item);
        HeapFree(GetProcessHeap(), 0, item.pszText);
    }

    /* Ensure that the previously selected item is selected again. */
    if (lSelected >= 0) {
        item.mask = LVIF_STATE;
        item.state = LVIS_SELECTED;
        item.stateMask = LVIS_SELECTED;
        SendDlgItemMessageW(dialog, IDC_LIST_SFPATHS, LVM_SETITEMSTATE, lSelected, (LPARAM)&item);
    }
}