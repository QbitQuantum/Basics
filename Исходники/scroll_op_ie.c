static
IDispatch *get_ie_target(HWND hwnd, int x, int y)
{
    IDispatch *top_doc, *elem, *target;
    UINT getobj_msg;
    LRESULT lres, res;
    HRESULT hres;

    getobj_msg = RegisterWindowMessageW(L"WM_HTML_GETOBJECT");
    if(getobj_msg == 0) {
        spr->log_lasterror(
            LOG_LEVEL_NOTIFY,
            L"ie-scroll: Failed to call "
            L"RegisterWindowMessage(\"WM_HTML_GETOBJECT\")", 1);
        return NULL;
    }

    lres = SendMessageTimeout(hwnd, getobj_msg, 0, 0,
                              SMTO_ABORTIFHUNG, 1000,
                              (PDWORD_PTR)&res);
    if(lres == 0) {
        spr->log_lasterror(
            LOG_LEVEL_NOTIFY,
            L"ie-scroll: Failed to call SendMessageTimeout()", 1);
        return NULL;
    }

    hres = ObjectFromLresult(res, &IID_IDispatch, 0,
                             (void **)(void *)&top_doc);
    if(FAILED(hres)) {
        spr->log_hresult(
            LOG_LEVEL_NOTIFY,
            L"ie-scroll: Failed to call ObjectFromLresult()",
            hres, 1);
        return NULL;
    }

    hres = get_ie_elem_at(top_doc, x, y, &elem);
    IDispatch_Release(top_doc);
    if(FAILED(hres)) {
        return NULL;
    }

    hres = get_scrollable_parent(elem, &target);
    IDispatch_Release(elem);
    if(FAILED(hres)) {
        return NULL;
    }

    return target;
}