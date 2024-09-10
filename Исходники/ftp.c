static HRESULT WINAPI HttpInfo_QueryInfo(IWinInetHttpInfo *iface, DWORD dwOption,
        void *pBuffer, DWORD *pcbBuffer, DWORD *pdwFlags, DWORD *pdwReserved)
{
    FtpProtocol *This = impl_from_IWinInetHttpInfo(iface);
    TRACE("(%p)->(%x %p %p %p %p)\n", This, dwOption, pBuffer, pcbBuffer, pdwFlags, pdwReserved);

    if(!This->base.request)
        return E_FAIL;

    if(!HttpQueryInfoW(This->base.request, dwOption, pBuffer, pcbBuffer, pdwFlags))
        return S_FALSE;
    return S_OK;
}