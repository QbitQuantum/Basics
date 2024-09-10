HRESULT
WINAPI
IDirectSoundCaptureBufferImpl_QueryInterface(
    LPDIRECTSOUNDCAPTUREBUFFER8 iface,
    IN REFIID riid,
    LPVOID* ppobj)
{
    LPOLESTR pStr;
    LPCDirectSoundCaptureBufferImpl This = (LPCDirectSoundCaptureBufferImpl)CONTAINING_RECORD(iface, CDirectSoundCaptureBufferImpl, lpVtbl);

    /* check if requested interface is supported */
    if (IsEqualIID(riid, &IID_IUnknown) ||
        IsEqualIID(riid, &IID_IDirectSoundCaptureBuffer) ||
        IsEqualIID(riid, &IID_IDirectSoundCaptureBuffer8))
    {
        *ppobj = (LPVOID)&This->lpVtbl;
        InterlockedIncrement(&This->ref);
        return S_OK;
    }

    /* check if the interface is supported */
    if (IsEqualIID(riid, &IID_IDirectSoundNotify))
    {
        if (!This->Notify)
        {
            HRESULT hr = NewDirectSoundNotify(&This->Notify, This->bLoop, This->bMix, This->hPin, This->BufferSize);
            if (FAILED(hr))
                return hr;

            *ppobj = (LPVOID)This->Notify;
            return S_OK;
        }

        /* increment reference count on existing notify object */
        IDirectSoundNotify_AddRef(This->Notify);
        *ppobj = (LPVOID)This->Notify;
        return S_OK;
    }

    /* interface not supported */
    if (SUCCEEDED(StringFromIID(riid, &pStr)))
    {
        DPRINT("No Interface for class %s\n", pStr);
        CoTaskMemFree(pStr);
    }
    return E_NOINTERFACE;
}