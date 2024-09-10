/******************************************************************************
 *        ClassMoniker_Save
 ******************************************************************************/
static HRESULT WINAPI ClassMoniker_Save(IMoniker* iface, IStream* pStm, BOOL fClearDirty)
{
    ClassMoniker *This = impl_from_IMoniker(iface);
    HRESULT hr;
    DWORD zero = 0;

    TRACE("(%p, %s)\n", pStm, fClearDirty ? "TRUE" : "FALSE");

    hr = IStream_Write(pStm, &This->clsid, sizeof(This->clsid), NULL);
    if (FAILED(hr)) return hr;

    return IStream_Write(pStm, &zero, sizeof(zero), NULL);
}