STDMETHODIMP ShellExt::Initialize_Wrap(LPCITEMIDLIST folder,
                                        LPDATAOBJECT data,
                                        HKEY /* hRegKey */)
{
    FORMATETC format = {CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
    STGMEDIUM stg = {TYMED_HGLOBAL, {L'\0'}, NULL};
    HDROP drop;
    UINT count;
    UINT size;
    HRESULT result = S_OK;
    wchar_t path_dir_w[4096];
    std::unique_ptr<wchar_t[]> path_w;

    active_menu_items_.clear();

    /* 'folder' param is not null only when clicking at the foler background;
       When right click on a file, it's NULL */
    if (folder) {
        if (SHGetPathFromIDListW(folder, path_dir_w)) {
            path_ = utils::normalizedPath(utils::wStringToUtf8(path_dir_w));
        }
    }

    /* if 'data' is NULL, then it's a background click, we have set
     * path_ to folder's name above, and the Init work is done */
    if (!data)
        return S_OK;

    /* 'data' is no null, which means we are operating on a file. The
     * following lines until the end of the function is used to extract the
     * filename of the current file. */
    if (FAILED(data->GetData(&format, &stg)))
        return E_INVALIDARG;

    drop = (HDROP)GlobalLock(stg.hGlobal);
    if (!drop)
        return E_INVALIDARG;

    // When the function copies a file name to the buffer, the return value is a
    // count of the characters copied, not including the terminating null
    // character.
    count = DragQueryFileW(drop, 0xFFFFFFFF, NULL, 0);
    if (count == 0) {
        result = E_INVALIDARG;
    } else if (count > 1) {
        result = S_FALSE;
    } else {
        size = DragQueryFileW(drop, 0, NULL, 0);
        if (!size) {
            result = E_INVALIDARG;
        } else {
            path_w.reset(new wchar_t[size+1]);
            if (!DragQueryFileW(drop, 0, path_w.get(), size+1))
                result = E_INVALIDARG;
        }
    }

    GlobalUnlock(stg.hGlobal);
    ReleaseStgMedium(&stg);

    if (result == S_OK) {
        path_ = utils::normalizedPath(utils::wStringToUtf8(path_w.get()));
    }

    return result;
}