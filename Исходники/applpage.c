void ApplicationPage_OnWindowsCascade(void)
{
    LPAPPLICATION_PAGE_LIST_ITEM  pAPLI = NULL;
    LV_ITEM                       item;
    int                           i;
    HWND*                         hWndArray;
    int                           nWndCount;

    hWndArray = (HWND*)HeapAlloc(GetProcessHeap(), 0, sizeof(HWND) * ListView_GetItemCount(hApplicationPageListCtrl));
    nWndCount = 0;

    for (i=0; i<ListView_GetItemCount(hApplicationPageListCtrl); i++) {
        memset(&item, 0, sizeof(LV_ITEM));
        item.mask = LVIF_STATE|LVIF_PARAM;
        item.iItem = i;
        item.stateMask = (UINT)-1;
        (void)ListView_GetItem(hApplicationPageListCtrl, &item);
        if (item.state & LVIS_SELECTED) {
            pAPLI = (LPAPPLICATION_PAGE_LIST_ITEM)item.lParam;
            if (pAPLI) {
                hWndArray[nWndCount] = pAPLI->hWnd;
                nWndCount++;
            }
        }
    }
    CascadeWindows(NULL, 0, NULL, nWndCount, hWndArray);
    HeapFree(GetProcessHeap(), 0, hWndArray);
}