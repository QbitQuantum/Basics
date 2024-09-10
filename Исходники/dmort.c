/***********************************************************************
 *        MoDuplicateMediaType    (MSDMO.@)
 *
 * Duplicates a media type structure
 */
HRESULT WINAPI MoDuplicateMediaType(DMO_MEDIA_TYPE** ppdst,
                                    const DMO_MEDIA_TYPE* psrc)
{
    HRESULT r;

    TRACE("%p %p\n", ppdst, psrc);

    if (!ppdst || !psrc)
        return E_POINTER;

    *ppdst = CoTaskMemAlloc(sizeof(DMO_MEDIA_TYPE));
    if (!*ppdst)
        return E_OUTOFMEMORY;

    r = MoCopyMediaType(*ppdst, psrc);
    if (FAILED(r))
    {
        MoFreeMediaType(*ppdst);
        *ppdst = NULL;
    }

    return r;
}