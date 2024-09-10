static HRESULT WINAPI PHBindHost_CreateMoniker(IBindHost *iface, LPOLESTR szName, IBindCtx *pBC, IMoniker **ppmk, DWORD dwReserved)
{
    PluginHost *This = impl_from_IBindHost(iface);

    TRACE("(%p)->(%s %p %p %x)\n", This, debugstr_w(szName), pBC, ppmk, dwReserved);

    if(!This->doc || !This->doc->window || !This->doc->window->mon) {
        FIXME("no moniker\n");
        return E_UNEXPECTED;
    }

    return CreateURLMoniker(This->doc->window->mon, szName, ppmk);
}