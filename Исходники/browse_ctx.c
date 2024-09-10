static HRESULT WINAPI IHlinkBC_UpdateHlink(IHlinkBrowseContext* iface,
        ULONG hlid, IMoniker *target, LPCWSTR location, LPCWSTR friendly_name)
{
    HlinkBCImpl *This = impl_from_IHlinkBrowseContext(iface);
    struct link_entry *entry = context_get_entry(This, hlid);
    IHlink *link;
    HRESULT hr;

    TRACE("(%p)->(0x%x %p %s %s)\n", This, hlid, target, debugstr_w(location), debugstr_w(friendly_name));

    if (!entry)
        return E_INVALIDARG;

    hr = HlinkCreateFromMoniker(target, location, friendly_name, NULL, 0, NULL, &IID_IHlink, (void**)&link);
    if (FAILED(hr))
        return hr;

    IHlink_Release(entry->link);
    entry->link = link;

    return S_OK;
}