static HRESULT GopherProtocol_open_request(Protocol *prot, IUri *uri, DWORD request_flags,
        HINTERNET internet_session, IInternetBindInfo *bind_info)
{
    GopherProtocol *This = impl_from_Protocol(prot);
    BSTR url;
    HRESULT hres;

    hres = IUri_GetAbsoluteUri(uri, &url);
    if(FAILED(hres))
        return hres;

    This->base.request = InternetOpenUrlW(internet_session, url, NULL, 0,
            request_flags, (DWORD_PTR)&This->base);
    SysFreeString(url);
    if (!This->base.request && GetLastError() != ERROR_IO_PENDING) {
        WARN("InternetOpenUrl failed: %d\n", GetLastError());
        return INET_E_RESOURCE_NOT_FOUND;
    }

    return S_OK;
}