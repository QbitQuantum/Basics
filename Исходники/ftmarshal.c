static HRESULT WINAPI
FTMarshalImpl_MarshalInterface (LPMARSHAL iface, IStream * pStm, REFIID riid, void *pv,
			       DWORD dwDestContext, void *pvDestContext, DWORD mshlflags)
{

    IMarshal *pMarshal = NULL;
    HRESULT hres;

    TRACE("(%p, %s, %p, 0x%x, %p, 0x%x)\n", pStm, debugstr_guid(riid), pv,
        dwDestContext, pvDestContext, mshlflags);

    /* if the marshalling happens inside the same process the interface pointer is
       copied between the apartments */
    if (dwDestContext == MSHCTX_INPROC || dwDestContext == MSHCTX_CROSSCTX) {
        void *object;
        DWORD constant = 0;
        GUID unknown_guid = { 0 };

        hres = IUnknown_QueryInterface((IUnknown *)pv, riid, &object);
        if (FAILED(hres))
            return hres;

        /* don't hold a reference to table-weak marshaled interfaces */
        if (mshlflags & MSHLFLAGS_TABLEWEAK)
            IUnknown_Release((IUnknown *)object);

        hres = IStream_Write (pStm, &mshlflags, sizeof (mshlflags), NULL);
        if (hres != S_OK) return STG_E_MEDIUMFULL;

        hres = IStream_Write (pStm, &object, sizeof (object), NULL);
        if (hres != S_OK) return STG_E_MEDIUMFULL;

        if (sizeof(object) == sizeof(DWORD))
        {
            hres = IStream_Write (pStm, &constant, sizeof (constant), NULL);
            if (hres != S_OK) return STG_E_MEDIUMFULL;
        }

        hres = IStream_Write (pStm, &unknown_guid, sizeof (unknown_guid), NULL);
        if (hres != S_OK) return STG_E_MEDIUMFULL;

        return S_OK;
    }

    /* use the standard marshaler to handle all other cases */
    CoGetStandardMarshal (riid, pv, dwDestContext, pvDestContext, mshlflags, &pMarshal);
    hres = IMarshal_MarshalInterface (pMarshal, pStm, riid, pv, dwDestContext, pvDestContext, mshlflags);
    IMarshal_Release (pMarshal);
    return hres;
}