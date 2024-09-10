static HRESULT WINAPI DocObjectService_FireBeforeNavigate2(
        IDocObjectService* iface,
        IDispatch *pDispatch,
        LPCWSTR lpszUrl,
        DWORD dwFlags,
        LPCWSTR lpszFrameName,
        BYTE *pPostData,
        DWORD cbPostData,
        LPCWSTR lpszHeaders,
        BOOL fPlayNavSound,
        BOOL *pfCancel)
{
    ShellBrowser *This = impl_from_IDocObjectService(iface);
    VARIANT var_url, var_flags, var_frame_name, var_post_data, var_post_data2, var_headers;
    VARIANTARG params[7];
    DISPPARAMS dp = {params, NULL, 7, 0};
    VARIANT_BOOL cancel = VARIANT_FALSE;
    SAFEARRAY *post_data;
    WCHAR file_path[MAX_PATH];
    DWORD file_path_len = sizeof(file_path) / sizeof(*file_path);

    TRACE("%p %p %s %x %s %p %d %s %d %p\n", This, pDispatch, debugstr_w(lpszUrl),
            dwFlags, debugstr_w(lpszFrameName), pPostData, cbPostData,
            debugstr_w(lpszHeaders), fPlayNavSound, pfCancel);

    if(cbPostData) {
        post_data = SafeArrayCreateVector(VT_UI1, 0, cbPostData);
        if(!post_data)
            return E_OUTOFMEMORY;
        memcpy(post_data->pvData, pPostData, cbPostData);
    }else {
        post_data = NULL;
    }

    V_VT(params) = VT_BOOL|VT_BYREF;
    V_BOOLREF(params) = &cancel;

    V_VT(params+1) = (VT_BYREF|VT_VARIANT);
    V_VARIANTREF(params+1) = &var_headers;
    V_VT(&var_headers) = VT_BSTR;
    V_BSTR(&var_headers) = lpszHeaders ? SysAllocString(lpszHeaders) : NULL;

    V_VT(params+2) = (VT_BYREF|VT_VARIANT);
    V_VARIANTREF(params+2) = &var_post_data2;
    V_VT(&var_post_data2) = (VT_BYREF|VT_VARIANT);
    V_VARIANTREF(&var_post_data2) = &var_post_data;

    if(post_data) {
        V_VT(&var_post_data) = VT_UI1|VT_ARRAY;
        V_ARRAY(&var_post_data) = post_data;
    }else {
        V_VT(&var_post_data) = VT_EMPTY;
    }

    V_VT(params+3) = (VT_BYREF|VT_VARIANT);
    V_VARIANTREF(params+3) = &var_frame_name;
    V_VT(&var_frame_name) = VT_BSTR;
    V_BSTR(&var_frame_name) = lpszFrameName ? SysAllocString(lpszFrameName) : NULL;

    V_VT(params+4) = (VT_BYREF|VT_VARIANT);
    V_VARIANTREF(params+4) = &var_flags;
    V_VT(&var_flags) = VT_I4;
    V_I4(&var_flags) = 0;

    V_VT(params+5) = (VT_BYREF|VT_VARIANT);
    V_VARIANTREF(params+5) = &var_url;
    V_VT(&var_url) = VT_BSTR;
    if(PathCreateFromUrlW(lpszUrl, file_path, &file_path_len, 0) == S_OK)
        V_BSTR(&var_url) = SysAllocString(file_path);
    else
        V_BSTR(&var_url) = SysAllocString(lpszUrl);

    V_VT(params+6) = (VT_DISPATCH);
    V_DISPATCH(params+6) = (IDispatch*)This->doc_host->wb;

    /* Keep reference to This. It may be released in event handler. */
    IShellBrowser_AddRef(&This->IShellBrowser_iface);

    TRACE(">>>\n");
    call_sink(This->doc_host->cps.wbe2, DISPID_BEFORENAVIGATE2, &dp);
    TRACE("<<<\n");

    IShellBrowser_Release(&This->IShellBrowser_iface);

    SysFreeString(V_BSTR(&var_url));
    SysFreeString(V_BSTR(&var_headers));
    SysFreeString(V_BSTR(&var_frame_name));
    SafeArrayDestroy(post_data);

    *pfCancel = !!cancel;
    return S_OK;
}