HRESULT STDMETHODCALLTYPE CSHEnumClassesOfCategories::Next(ULONG cElt, CLSID *pElts, ULONG *pFetched)
{
    ULONG i;
    ULONG read;
    GUID *tmp;

    if (!pElts)
        return E_INVALIDARG;
    read = 0;
    for (i = 0; i < cElt && (fCursor < (ULONG)DSA_GetItemCount(fDsa)); i++)
    {
        tmp = (GUID*)DSA_GetItemPtr(fDsa, fCursor + i);
        if (!tmp)
            break;
        pElts[i] = *tmp;
        read++;
    }
    fCursor += read;
    if (pFetched)
        *pFetched = read;
    return S_OK;
}