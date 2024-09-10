static HRESULT WINAPI xmldoc_IPersistStreamInit_Load(
    IPersistStreamInit *iface, LPSTREAM pStm)
{
    xmldoc *This = impl_from_IPersistStreamInit(iface);
    HRESULT hr;
    HGLOBAL hglobal;
    DWORD read, written, len;
    BYTE buf[4096];
    char *ptr;

    TRACE("(%p, %p)\n", iface, pStm);

    if (!pStm)
        return E_INVALIDARG;

    /* release previously allocated stream */
    if (This->stream) IStream_Release(This->stream);
    hr = CreateStreamOnHGlobal(NULL, TRUE, &This->stream);
    if (FAILED(hr))
        return hr;

    do
    {
        IStream_Read(pStm, buf, sizeof(buf), &read);
        hr = IStream_Write(This->stream, buf, read, &written);
    } while(SUCCEEDED(hr) && written != 0 && read != 0);

    if (FAILED(hr))
    {
        ERR("Failed to copy stream\n");
        return hr;
    }

    hr = GetHGlobalFromStream(This->stream, &hglobal);
    if (FAILED(hr))
        return hr;

    len = GlobalSize(hglobal);
    ptr = GlobalLock(hglobal);
    if (len != 0)
    {
        xmlFreeDoc(This->xmldoc);
        This->xmldoc = parse_xml(ptr, len);
    }
    GlobalUnlock(hglobal);

    if (!This->xmldoc)
    {
        ERR("Failed to parse xml\n");
        return E_FAIL;
    }

    return S_OK;
}