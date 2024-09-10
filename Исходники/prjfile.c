static int CreateNewFileData(HWND hwnd)
{
    int items = 0;
    LV_ITEM item;
    RECT r;
    HWND hwndLV = GetDlgItem(hwnd, IDC_LVNEWPROJECT);
    LV_COLUMN lvC;
    ListView_SetExtendedListViewStyle(hwndLV, LVS_EX_FULLROWSELECT);
    ListView_SetImageList(hwndLV, ImageList_Duplicate(treeIml), LVSIL_SMALL);

    GetWindowRect(hwndLV, &r);
    lvC.mask = LVCF_WIDTH | LVCF_SUBITEM ;
    lvC.cx = r.right - r.left;
    lvC.iSubItem = 0;
    ListView_InsertColumn(hwndLV, 0, &lvC);

    memset(&item, 0, sizeof(item));
    item.iItem = items++;
    item.iSubItem = 0;
    item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
    item.iImage = IL_C;
    item.pszText = "C Program File";
    item.lParam = 0;
    ListView_InsertItem(hwndLV, &item);
    
    item.iItem = items++;
    item.iSubItem = 0;
    item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
    item.iImage = IL_H;
    item.pszText = "Header File";
    item.lParam = 6;
    ListView_InsertItem(hwndLV, &item);
    
    item.iItem = items++;
    item.iSubItem = 0;
    item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
    item.iImage = IL_RES;
    item.pszText = "Resource File";
    item.lParam = 11;
    ListView_InsertItem(hwndLV, &item);
    
    item.iItem = items++;
    item.iSubItem = 0;
    item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
    item.iImage = IL_FILES;
    item.pszText = "Module Definition File";
    item.lParam = 5;
    ListView_InsertItem(hwndLV, &item);
    
    item.iItem = items++;
    item.iSubItem = 0;
    item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
    item.iImage = IL_ASM;
    item.pszText = "Assembly Language File";
    item.lParam = 3;
    ListView_InsertItem(hwndLV, &item);
    
    item.iItem = items++;
    item.iSubItem = 0;
    item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
    item.iImage = IL_FILES;
    item.pszText = "Text File";
    item.lParam = 16;
    ListView_InsertItem(hwndLV, &item);
    
    ListView_SetSelectionMark(hwndLV, 0);
    ListView_SetItemState(hwndLV, 0, LVIS_SELECTED, LVIS_SELECTED);

    SendDlgItemMessage(hwnd, IDC_FILENEWFILE, WM_SETTEXT, 0, (LPARAM) "");
    SendDlgItemMessage(hwnd, IDC_FILENEWFILE, EM_SETLIMITTEXT, MAX_PATH, 0);
    return items;
}