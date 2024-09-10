static HRESULT WINAPI XMLView_BindStatusCallback_OnDataAvailable(
        IBindStatusCallback *iface, DWORD grfBSCF, DWORD dwSize,
        FORMATETC *pformatetc, STGMEDIUM *pstgmed)
{
    BindStatusCallback *This = impl_from_IBindStatusCallback(iface);
    char buf[1024];
    DWORD size;
    HRESULT hres;

    TRACE("(%p)->(%x %d %p %p)\n", This, grfBSCF, dwSize, pformatetc, pstgmed);

    if(!This->stream)
        return E_FAIL;

    do {
        hres = IStream_Read(pstgmed->u.pstm, buf, sizeof(buf), &size);
        IStream_Write(This->stream, buf, size, &size);
    } while(hres==S_OK && size);

    if(FAILED(hres) && hres!=E_PENDING)
        return hres;
    if(hres != S_FALSE)
        return S_OK;

    return handle_xml_load(This);
}