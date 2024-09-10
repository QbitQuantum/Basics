static char *win_special_path (int folder)
{
    TCHAR dpath[MAX_PATH];
    LPITEMIDLIST id_list;
    DWORD result;
    LPMALLOC allocator;
    char *ret = NULL;

    if (SHGetSpecialFolderLocation(NULL, folder | CSIDL_FLAG_CREATE, 
				   &id_list) != S_OK) {
	return NULL;
    }

    result = SHGetPathFromIDList(id_list, dpath);

    if (result) {
	ret = gretl_strdup(dpath);
    }

    if (SHGetMalloc(&allocator) == S_OK) {
	allocator->lpVtbl->Free(allocator, id_list);
	allocator->lpVtbl->Release(allocator);
    }

    return ret;
}