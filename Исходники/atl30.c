/***********************************************************************
 *           AtlModuleRegisterServer         [ATL.@]
 *
 */
HRESULT WINAPI AtlModuleRegisterServer(_ATL_MODULEW* pM, BOOL bRegTypeLib, const CLSID* clsid)
{
    const _ATL_OBJMAP_ENTRYW_V1 *obj;
    int i;
    HRESULT hRes;

    TRACE("%p %d %s\n", pM, bRegTypeLib, debugstr_guid(clsid));

    if (pM == NULL)
        return E_INVALIDARG;

    for (i = 0; (obj = get_objmap_entry( pM, i )) != NULL; i++) /* register CLSIDs */
    {
        if (!clsid || IsEqualCLSID(obj->pclsid, clsid))
        {
            TRACE("Registering clsid %s\n", debugstr_guid(obj->pclsid));
            hRes = obj->pfnUpdateRegistry(TRUE); /* register */
            if (FAILED(hRes))
                return hRes;

            if(pM->cbSize > ATLVer1Size) {
                const struct _ATL_CATMAP_ENTRY *catmap;

                catmap = ((const _ATL_OBJMAP_ENTRYW*)obj)->pfnGetCategoryMap();
                if(catmap) {
                    hRes = AtlRegisterClassCategoriesHelper(obj->pclsid, catmap, TRUE);
                    if(FAILED(hRes))
                        return hRes;
                }
            }
        }
    }

    if (bRegTypeLib)
    {
        hRes = AtlRegisterTypeLib(pM->m_hInstTypeLib, NULL);
        if (FAILED(hRes))
            return hRes;
    }

    return S_OK;
}