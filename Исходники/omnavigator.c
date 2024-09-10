static HRESULT WINAPI OmNavigator_get_userAgent(IOmNavigator *iface, BSTR *p)
{
    OmNavigator *This = impl_from_IOmNavigator(iface);
    char user_agent[512];
    DWORD size;
    HRESULT hres;

    TRACE("(%p)->(%p)\n", This, p);

    size = sizeof(user_agent);
    hres = ObtainUserAgentString(0, user_agent, &size);
    if(FAILED(hres))
        return hres;

    size = MultiByteToWideChar(CP_ACP, 0, user_agent, -1, NULL, 0);
    *p = SysAllocStringLen(NULL, size-1);
    if(!*p)
        return E_OUTOFMEMORY;

    MultiByteToWideChar(CP_ACP, 0, user_agent, -1, *p, size);
    return S_OK;
}