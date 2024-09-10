/*****************************************************************************
 * SIC_IconAppend            [internal]
 *
 * NOTES
 *  appends an icon pair to the end of the cache
 */
static INT SIC_IconAppend (LPCWSTR sSourceFile, INT dwSourceIndex, HICON hSmallIcon, HICON hBigIcon, DWORD dwFlags)
{
    LPSIC_ENTRY lpsice;
    INT ret, index, index1, indexDPA;
    WCHAR path[MAX_PATH];
    TRACE("%s %i %p %p\n", debugstr_w(sSourceFile), dwSourceIndex, hSmallIcon ,hBigIcon);

    lpsice = (LPSIC_ENTRY) SHAlloc (sizeof (SIC_ENTRY));

    GetFullPathNameW(sSourceFile, MAX_PATH, path, NULL);
    lpsice->sSourceFile = (LPWSTR)HeapAlloc( GetProcessHeap(), 0, (wcslen(path)+1)*sizeof(WCHAR) );
    wcscpy( lpsice->sSourceFile, path );

    lpsice->dwSourceIndex = dwSourceIndex;
    lpsice->dwFlags = dwFlags;

    EnterCriticalSection(&SHELL32_SicCS);

    indexDPA = DPA_Search (sic_hdpa, lpsice, 0, SIC_CompareEntries, 0, DPAS_SORTED|DPAS_INSERTAFTER);
    indexDPA = DPA_InsertPtr(sic_hdpa, indexDPA, lpsice);
    if ( -1 == indexDPA )
    {
        ret = INVALID_INDEX;
        goto leave;
    }

    index = ImageList_AddIcon (ShellSmallIconList, hSmallIcon);
    index1= ImageList_AddIcon (ShellBigIconList, hBigIcon);

    /* Something went wrong when allocating a new image in the list. Abort. */
    if((index == -1) || (index1 == -1))
    {
        WARN("Something went wrong when adding the icon to the list: small - 0x%x, big - 0x%x.\n",
            index, index1);
        if(index != -1) ImageList_Remove(ShellSmallIconList, index);
        if(index1 != -1) ImageList_Remove(ShellBigIconList, index1);
        ret = INVALID_INDEX;
        goto leave;
    }

    if (index!=index1)
    {
        FIXME("iconlists out of sync 0x%x 0x%x\n", index, index1);
        /* What to do ???? */
    }
    lpsice->dwListIndex = index;
    ret = lpsice->dwListIndex;

leave:
    if(ret == INVALID_INDEX)
    {
        if(indexDPA != -1) DPA_DeletePtr(sic_hdpa, indexDPA);
        HeapFree(GetProcessHeap(), 0, lpsice->sSourceFile);
        SHFree(lpsice);
    }
    LeaveCriticalSection(&SHELL32_SicCS);
    return ret;
}