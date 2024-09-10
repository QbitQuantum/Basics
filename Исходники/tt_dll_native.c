tt_result_t tt_dll_create_ntv(IN tt_dll_ntv_t *dll,
                              IN const tt_char_t *path,
                              IN OPT tt_dll_attr_t *attr)
{
    void *handle;
    DWORD dwFlags = 0;
    wchar_t *w_path;

    TT_ASSERT(dll != NULL);
    TT_ASSERT(path != NULL);

    // may set mode according to attr;
    // dwFlags |= ...;

    w_path = tt_wchar_create(path, 0, NULL);
    if (w_path == NULL) {
        return TT_FAIL;
    }

    handle = LoadLibraryExW(w_path, NULL, dwFlags);
    tt_wchar_destroy(w_path);
    if (handle == NULL) {
        TT_ERROR_NTV("LoadLibraryExW failed: %s");
        return TT_FAIL;
    }

    dll->handle = handle;
    return TT_SUCCESS;
}