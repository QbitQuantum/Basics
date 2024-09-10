/***********************************************************************
 *           AtlRegisterTypeLib         [atl80.18]
 */
HRESULT WINAPI AtlComModuleRegisterServer(_ATL_COM_MODULE *mod, BOOL bRegTypeLib, const CLSID *clsid)
{
    const struct _ATL_CATMAP_ENTRY *catmap;
    _ATL_OBJMAP_ENTRY **iter;
    HRESULT hres;

    TRACE("(%p %x %s)\n", mod, bRegTypeLib, debugstr_guid(clsid));

    for(iter = mod->m_ppAutoObjMapFirst; iter < mod->m_ppAutoObjMapLast; iter++) {
        if(!*iter || (clsid && !IsEqualCLSID((*iter)->pclsid, clsid)))
            continue;

        TRACE("Registering clsid %s\n", debugstr_guid((*iter)->pclsid));
        hres = (*iter)->pfnUpdateRegistry(TRUE);
        if(FAILED(hres))
            return hres;

        catmap = (*iter)->pfnGetCategoryMap();
        if(catmap) {
            hres = AtlRegisterClassCategoriesHelper((*iter)->pclsid, catmap, TRUE);
            if(FAILED(hres))
                return hres;
        }
    }

    if(bRegTypeLib) {
        hres = AtlRegisterTypeLib(mod->m_hInstTypeLib, NULL);
        if(FAILED(hres))
            return hres;
    }

    return S_OK;
}