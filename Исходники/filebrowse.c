void FileBrowseMenu(int x, int y, HWND hwndToolbar)
{
    if (fileBrowseInfo)
    {
        FILEBROWSE *p = fileBrowseInfo;
        HMENU popup = CreatePopupMenu();    
        int i = 0, j;
        memset(ordered, 0, sizeof(ordered));
        while (p && i < MAX_BROWSE)
        {
            ordered[i++] = p;
            p = p->next;
        }
        qsort(ordered, i, sizeof(FILEBROWSE *), fbcomp);
    
        for (j=0; j < i;)
        {
            FILEBROWSE *cur = ordered[j];
            HMENU internalPop = CreatePopupMenu();
            for ( ;j < i && cur->info == ordered[j]->info; j++)
            {
                InsertMenu(internalPop, -1, MF_BYPOSITION | MF_STRING, j + ID_FILEBROWSE_LIST, GetName(j));
            }
            InsertMenu(popup, -1, MF_BYPOSITION | MF_POPUP | MF_STRING, (UINT_PTR)internalPop, cur->info->dwTitle);
        }
        InsertBitmapsInMenu(popup);
        TrackPopupMenuEx(popup, TPM_TOPALIGN | TPM_LEFTBUTTON, x, y, hwndFrame, NULL);
        DestroyMenu(popup);
    }
} 