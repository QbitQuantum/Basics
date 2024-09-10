HRESULT navigate_url(DocHost *This, LPCWSTR url, const VARIANT *Flags,
                     const VARIANT *TargetFrameName, VARIANT *PostData, VARIANT *Headers)
{
    SAFEARRAY *post_array = NULL;
    PBYTE post_data = NULL;
    ULONG post_data_len = 0;
    LPWSTR headers = NULL;
    HRESULT hres = S_OK;

    TRACE("navigating to %s\n", debugstr_w(url));

    if((Flags && V_VT(Flags) != VT_EMPTY && V_VT(Flags) != VT_ERROR)
       || (TargetFrameName && V_VT(TargetFrameName) != VT_EMPTY && V_VT(TargetFrameName) != VT_ERROR))
        FIXME("Unsupported args (Flags %s; TargetFrameName %s)\n", debugstr_variant(Flags), debugstr_variant(TargetFrameName));

    if(PostData) {
        if(V_VT(PostData) & VT_ARRAY)
            post_array = V_ISBYREF(PostData) ? *V_ARRAYREF(PostData) : V_ARRAY(PostData);
        else
            WARN("Invalid post data %s\n", debugstr_variant(PostData));
    }

    if(post_array) {
        LONG elem_max;
        SafeArrayAccessData(post_array, (void**)&post_data);
        SafeArrayGetUBound(post_array, 1, &elem_max);
        post_data_len = (elem_max+1) * SafeArrayGetElemsize(post_array);
    }

    if(Headers && V_VT(Headers) == VT_BSTR) {
        headers = V_BSTR(Headers);
        TRACE("Headers: %s\n", debugstr_w(headers));
    }

    set_doc_state(This, READYSTATE_LOADING);
    This->ready_state = READYSTATE_LOADING;

    if(This->doc_navigate) {
        WCHAR new_url[INTERNET_MAX_URL_LENGTH];

        if(PathIsURLW(url)) {
            new_url[0] = 0;
        }else {
            DWORD size;

            size = sizeof(new_url)/sizeof(WCHAR);
            hres = UrlApplySchemeW(url, new_url, &size,
                    URL_APPLY_GUESSSCHEME | URL_APPLY_GUESSFILE | URL_APPLY_DEFAULT);
            if(FAILED(hres)) {
                WARN("UrlApplyScheme failed: %08x\n", hres);
                new_url[0] = 0;
            }
        }

        hres = async_doc_navigate(This, *new_url ? new_url : url, headers, post_data,
                post_data_len, TRUE);
    }else {
        task_navigate_bsc_t *task;

        task = heap_alloc(sizeof(*task));
        task->bsc = create_callback(This, url, post_data, post_data_len, headers);
        push_dochost_task(This, &task->header, navigate_bsc_proc, navigate_bsc_task_destr, This->url == NULL);
    }

    if(post_data)
        SafeArrayUnaccessData(post_array);

    return hres;
}