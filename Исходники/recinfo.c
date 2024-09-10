static HRESULT WINAPI IRecordInfoImpl_RecordCopy(IRecordInfo *iface, PVOID pvExisting,
                                                PVOID pvNew)
{
    IRecordInfoImpl *This = impl_from_IRecordInfo(iface);
    HRESULT hr = S_OK;
    int i;

    TRACE("(%p)->(%p %p)\n", This, pvExisting, pvNew);

    if(!pvExisting || !pvNew)
        return E_INVALIDARG;

    /* release already stored data */
    IRecordInfo_RecordClear(iface, pvNew);

    for (i = 0; i < This->n_vars; i++)
    {
        void *src, *dest;

        if (This->fields[i].varkind != VAR_PERINSTANCE) {
            ERR("varkind != VAR_PERINSTANCE\n");
            continue;
        }

        src  = ((BYTE*)pvExisting) + This->fields[i].offset;
        dest = ((BYTE*)pvNew) + This->fields[i].offset;
        switch (This->fields[i].vt)
        {
            case VT_BSTR:
            {
                BSTR src_str = *(BSTR*)src;

                if (src_str)
                {
                    BSTR str = SysAllocString(*(BSTR*)src);
                    if (!str) hr = E_OUTOFMEMORY;

                    *(BSTR*)dest = str;
                }
                else
                    *(BSTR*)dest = NULL;
                break;
            }
            case VT_UNKNOWN:
            case VT_DISPATCH:
            {
                IUnknown *unk = *(IUnknown**)src;
                *(IUnknown**)dest = unk;
                if (unk) IUnknown_AddRef(unk);
                break;
            }
            case VT_SAFEARRAY:
                hr = SafeArrayCopy(src, dest);
                break;
            default:
            {
                /* copy directly for types that don't need deep copy */
                int len = get_type_size(NULL, This->fields[i].vt);
                memcpy(dest, src, len);
                break;
            }
        }

        if (FAILED(hr)) break;
    }

    if (FAILED(hr))
        IRecordInfo_RecordClear(iface, pvNew);

    return hr;
}