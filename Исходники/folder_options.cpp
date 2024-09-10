static
INT_PTR
CALLBACK
FolderOptionsFileTypesDlg(
    HWND hwndDlg,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    LPNMLISTVIEW lppl;
    LVITEMW lvItem;
    WCHAR Buffer[255], FormatBuffer[255];
    PFOLDER_FILE_TYPE_ENTRY pItem;
    OPENASINFO Info;

    switch(uMsg)
    {
        case WM_INITDIALOG:
            InitializeFileTypesListCtrl(hwndDlg);
            return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case 14006:
                    pItem = FindSelectedItem(GetDlgItem(hwndDlg, 14000));
                    if (pItem)
                    {
                        Info.oaifInFlags = OAIF_ALLOW_REGISTRATION | OAIF_REGISTER_EXT;
                        Info.pcszClass = pItem->FileExtension;
                        SHOpenWithDialog(hwndDlg, &Info);
                    }
                    break;
            }

            break;
        case WM_NOTIFY:
            lppl = (LPNMLISTVIEW) lParam;

            if (lppl->hdr.code == LVN_ITEMCHANGING)
            {
                ZeroMemory(&lvItem, sizeof(LVITEM));
                lvItem.mask = LVIF_PARAM;
                lvItem.iItem = lppl->iItem;
                if (!SendMessageW(lppl->hdr.hwndFrom, LVM_GETITEMW, 0, (LPARAM)&lvItem))
                    return TRUE;

                pItem = (PFOLDER_FILE_TYPE_ENTRY)lvItem.lParam;
                if (!pItem)
                    return TRUE;

                if (!(lppl->uOldState & LVIS_FOCUSED) && (lppl->uNewState & LVIS_FOCUSED))
                {
                    /* new focused item */
                    if (!LoadStringW(shell32_hInstance, IDS_FILE_DETAILS, FormatBuffer, sizeof(FormatBuffer) / sizeof(WCHAR)))
                    {
                        /* use default english format string */
                        wcscpy(FormatBuffer, L"Details for '%s' extension");
                    }

                    /* format buffer */
                    swprintf(Buffer, FormatBuffer, &pItem->FileExtension[1]);
                    /* update dialog */
                    SetDlgItemTextW(hwndDlg, 14003, Buffer);

                    if (!LoadStringW(shell32_hInstance, IDS_FILE_DETAILSADV, FormatBuffer, sizeof(FormatBuffer) / sizeof(WCHAR)))
                    {
                        /* use default english format string */
                        wcscpy(FormatBuffer, L"Files with extension '%s' are of type '%s'. To change settings that affect all '%s' files, click Advanced.");
                    }
                    /* format buffer */
                    swprintf(Buffer, FormatBuffer, &pItem->FileExtension[1], &pItem->FileDescription[0], &pItem->FileDescription[0]);
                    /* update dialog */
                    SetDlgItemTextW(hwndDlg, 14007, Buffer);
                }
            }
            break;
    }

    return FALSE;
}