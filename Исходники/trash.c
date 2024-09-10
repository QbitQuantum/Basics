HRESULT TRASH_EnumItems(const WCHAR *path, LPITEMIDLIST **pidls, int *count)
{
    int ti_count;
    int pos=0, i;
    HRESULT err = E_OUTOFMEMORY;
    HDPA tinfs;

    if(path)
        FIXME("Ignoring path = %s\n", debugstr_w(path));
    
    if (!TRASH_EnsureInitialized()) return E_FAIL;
    tinfs = enum_bucket_trashinfos(home_trash, &ti_count);
    if (tinfs == NULL) return E_FAIL;
    *pidls = SHAlloc(sizeof(LPITEMIDLIST)*ti_count);
    if (!*pidls) goto failed;
    for (i=0; i<ti_count; i++)
    {
        WIN32_FIND_DATAW data;
        LPCSTR filename;
        
        filename = DPA_GetPtr(tinfs, i);
        if (FAILED(err = TRASH_GetDetails(home_trash, filename, &data)))
            goto failed;
        if (err == S_FALSE)
            continue;
        if (FAILED(err = TRASH_CreateSimplePIDL(filename, &data, &(*pidls)[pos])))
            goto failed;
        pos++;
    }
    *count = pos;
    DPA_DestroyCallback(tinfs, free_item_callback, NULL);
    return S_OK;
failed:
    if (*pidls != NULL)
    {
        int j;
        for (j=0; j<pos; j++)
            SHFree((*pidls)[j]);
        SHFree(*pidls);
    }
    DPA_DestroyCallback(tinfs, free_item_callback, NULL);
    
    return err;
}