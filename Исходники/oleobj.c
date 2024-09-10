static HRESULT WINAPI OleObject_Advise(IOleObject *iface, IAdviseSink *pAdvSink, DWORD *pdwConnection)
{
    HTMLDocument *This = impl_from_IOleObject(iface);
    TRACE("(%p)->(%p %p)\n", This, pAdvSink, pdwConnection);

    if(!pdwConnection)
        return E_INVALIDARG;

    if(!pAdvSink) {
        *pdwConnection = 0;
        return E_INVALIDARG;
    }

    if(!This->advise_holder) {
        CreateOleAdviseHolder(&This->advise_holder);
        if(!This->advise_holder)
            return E_OUTOFMEMORY;
    }

    return IOleAdviseHolder_Advise(This->advise_holder, pAdvSink, pdwConnection);
}