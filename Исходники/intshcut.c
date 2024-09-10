static HRESULT WINAPI UniformResourceLocatorW_InvokeCommand(IUniformResourceLocatorW *url, PURLINVOKECOMMANDINFOW pCommandInfo)
{
    InternetShortcut *This = impl_from_IUniformResourceLocatorW(url);
    WCHAR app[64];
    HKEY hkey;
    static const WCHAR wszURLProtocol[] = {'U','R','L',' ','P','r','o','t','o','c','o','l',0};
    SHELLEXECUTEINFOW sei;
    DWORD res, type;
    HRESULT hres;

    TRACE("%p %p\n", This, pCommandInfo );

    if (pCommandInfo->dwcbSize < sizeof (URLINVOKECOMMANDINFOW))
        return E_INVALIDARG;

    if (pCommandInfo->dwFlags != IURL_INVOKECOMMAND_FL_USE_DEFAULT_VERB)
    {
        FIXME("(%p, %p): non-default verbs not implemented\n", url, pCommandInfo);
        return E_NOTIMPL;
    }

    hres = CoInternetParseUrl(This->url, PARSE_SCHEMA, 0, app, sizeof(app)/sizeof(WCHAR), NULL, 0);
    if(FAILED(hres))
        return E_FAIL;

    res = RegOpenKeyW(HKEY_CLASSES_ROOT, app, &hkey);
    if(res != ERROR_SUCCESS)
        return E_FAIL;

    res = RegQueryValueExW(hkey, wszURLProtocol, NULL, &type, NULL, NULL);
    RegCloseKey(hkey);
    if(res != ERROR_SUCCESS || type != REG_SZ)
        return E_FAIL;

    memset(&sei, 0, sizeof(sei));
    sei.cbSize = sizeof(sei);
    sei.lpFile = This->url;
    sei.nShow = SW_SHOW;

    if( ShellExecuteExW(&sei) )
        return S_OK;
    else
        return E_FAIL;
}