static HRESULT WINAPI MkProtocol_Read(IInternetProtocolEx *iface, void *pv,
        ULONG cb, ULONG *pcbRead)
{
    MkProtocol *This = impl_from_IInternetProtocolEx(iface);

    TRACE("(%p)->(%p %u %p)\n", This, pv, cb, pcbRead);

    if(!This->stream)
        return E_FAIL;

    return IStream_Read(This->stream, pv, cb, pcbRead);
}