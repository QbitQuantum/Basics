/***********************************************************************
 *           CopyBindInfo (URLMON.@)
 */
HRESULT WINAPI CopyBindInfo(const BINDINFO *pcbiSrc, BINDINFO *pcbiDest)
{
    DWORD size;
    HRESULT hres;

    TRACE("(%p %p)\n", pcbiSrc, pcbiDest);

    if(!pcbiSrc || !pcbiDest)
        return E_POINTER;
    if(!pcbiSrc->cbSize || !pcbiDest->cbSize)
        return E_INVALIDARG;

    size = pcbiDest->cbSize;
    if(size > pcbiSrc->cbSize) {
        memcpy(pcbiDest, pcbiSrc, pcbiSrc->cbSize);
        memset((char*)pcbiDest+pcbiSrc->cbSize, 0, size-pcbiSrc->cbSize);
    } else {
        memcpy(pcbiDest, pcbiSrc, size);
    }
    pcbiDest->cbSize = size;

    size = FIELD_OFFSET(BINDINFO, szExtraInfo)+sizeof(void*);
    if(pcbiSrc->cbSize>=size && pcbiDest->cbSize>=size && pcbiSrc->szExtraInfo) {
        size = (strlenW(pcbiSrc->szExtraInfo)+1)*sizeof(WCHAR);
        pcbiDest->szExtraInfo = CoTaskMemAlloc(size);
        if(!pcbiDest->szExtraInfo)
            return E_OUTOFMEMORY;
        memcpy(pcbiDest->szExtraInfo, pcbiSrc->szExtraInfo, size);
    }

    size = FIELD_OFFSET(BINDINFO, stgmedData)+sizeof(STGMEDIUM);
    if(pcbiSrc->cbSize>=size && pcbiDest->cbSize>=size) {
        hres = CopyStgMedium(&pcbiSrc->stgmedData, &pcbiDest->stgmedData);
        if(FAILED(hres)) {
            CoTaskMemFree(pcbiDest->szExtraInfo);
            return hres;
        }
    }

    size = FIELD_OFFSET(BINDINFO, szCustomVerb)+sizeof(void*);
    if(pcbiSrc->cbSize>=size && pcbiDest->cbSize>=size && pcbiSrc->szCustomVerb) {
        size = (strlenW(pcbiSrc->szCustomVerb)+1)*sizeof(WCHAR);
        pcbiDest->szCustomVerb = CoTaskMemAlloc(size);
        if(!pcbiDest->szCustomVerb) {
            CoTaskMemFree(pcbiDest->szExtraInfo);
            ReleaseStgMedium(&pcbiDest->stgmedData);
            return E_OUTOFMEMORY;
        }
        memcpy(pcbiDest->szCustomVerb, pcbiSrc->szCustomVerb, size);
    }

    size = FIELD_OFFSET(BINDINFO, securityAttributes)+sizeof(SECURITY_ATTRIBUTES);
    if(pcbiDest->cbSize >= size)
        memset(&pcbiDest->securityAttributes, 0, sizeof(SECURITY_ATTRIBUTES));

    if(pcbiSrc->pUnk)
        IUnknown_AddRef(pcbiDest->pUnk);

    return S_OK;
}