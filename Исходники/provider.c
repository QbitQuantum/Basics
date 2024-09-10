static HRESULT DXDiag_InitDXDiagDirectShowFiltersContainer(IDxDiagContainer* pSubCont) {
    HRESULT hr = S_OK;
    static const WCHAR szName[] = {'s','z','N','a','m','e',0};
    static const WCHAR szCatName[] = {'s','z','C','a','t','N','a','m','e',0};
    static const WCHAR szClsidCat[] = {'s','z','C','l','s','i','d','C','a','t',0};
    static const WCHAR szClsidFilter[] = {'s','z','C','l','s','i','d','F','i','l','t','e','r',0};
    static const WCHAR dwInputs[] = {'d','w','I','n','p','u','t','s',0};
    static const WCHAR dwOutputs[] = {'d','w','O','u','t','p','u','t','s',0};
    static const WCHAR dwMerit[] = {'d','w','M','e','r','i','t',0};
    /*
    static const WCHAR szFileName[] = {'s','z','F','i','l','e','N','a','m','e',0};
    static const WCHAR szFileVersion[] = {'s','z','F','i','l','e','V','e','r','s','i','o','n',0};
    */
    VARIANT v;

    static const WCHAR wszClsidName[] = {'C','L','S','I','D',0};
    static const WCHAR wszFriendlyName[] = {'F','r','i','e','n','d','l','y','N','a','m','e',0};
    static const WCHAR wszFilterDataName[] = {'F','i','l','t','e','r','D','a','t','a',0};
    /*static const WCHAR wszMeritName[] = {'M','e','r','i','t',0};*/

    ICreateDevEnum* pCreateDevEnum = NULL;
    IEnumMoniker* pEmCat = NULL;
    IMoniker* pMCat = NULL;
    /** */
    hr = CoCreateInstance(&CLSID_SystemDeviceEnum,
                          NULL,
                          CLSCTX_INPROC_SERVER,
                          &IID_ICreateDevEnum,
                          (void**) &pCreateDevEnum);
    if (FAILED(hr)) return hr;

    hr = ICreateDevEnum_CreateClassEnumerator(pCreateDevEnum, &CLSID_ActiveMovieCategories, &pEmCat, 0);
    if (FAILED(hr)) goto out_show_filters;

    VariantInit(&v);

    while (S_OK == IEnumMoniker_Next(pEmCat, 1, &pMCat, NULL)) {
        IPropertyBag* pPropBag = NULL;
        CLSID clsidCat;
        hr = IMoniker_BindToStorage(pMCat, NULL, NULL, &IID_IPropertyBag, (void**) &pPropBag);
        if (SUCCEEDED(hr)) {
            WCHAR* wszCatName = NULL;
            WCHAR* wszCatClsid = NULL;

            hr = IPropertyBag_Read(pPropBag, wszFriendlyName, &v, 0);
            wszCatName = SysAllocString(V_BSTR(&v));
            VariantClear(&v);

            hr = IPropertyBag_Read(pPropBag, wszClsidName, &v, 0);
            wszCatClsid = SysAllocString(V_BSTR(&v));
            hr = CLSIDFromString(V_UNION(&v, bstrVal), &clsidCat);
            VariantClear(&v);

            /*
            hr = IPropertyBag_Read(pPropBag, wszMeritName, &v, 0);
            hr = IDxDiagContainerImpl_AddProp(pSubCont, dwMerit, &v);
            VariantClear(&v);
            */

            if (SUCCEEDED(hr)) {
                IEnumMoniker* pEnum = NULL;
                IMoniker* pMoniker = NULL;
                hr = ICreateDevEnum_CreateClassEnumerator(pCreateDevEnum, &clsidCat, &pEnum, 0);
                FIXME("\tClassEnumerator for clsid(%s) pEnum(%p)\n", debugstr_guid(&clsidCat), pEnum);
                if (FAILED(hr) || pEnum == NULL) {
                    goto class_enum_failed;
                }
                while (NULL != pEnum && S_OK == IEnumMoniker_Next(pEnum, 1, &pMoniker, NULL)) {
                    IPropertyBag* pPropFilterBag = NULL;
                    FIXME("\tIEnumMoniker_Next(%p, 1, %p)\n", pEnum, pMoniker);
                    hr = IMoniker_BindToStorage(pMoniker, NULL, NULL, &IID_IPropertyBag, (void**) &pPropFilterBag);
                    if (SUCCEEDED(hr)) {
                        LPBYTE pData = NULL;
                        LPBYTE pCurrent = NULL;
                        struct REG_RF* prrf = NULL;
                        VARIANT v_data;
                        DWORD it;
                        DWORD dwNOutputs = 0;
                        DWORD dwNInputs = 0;

                        V_VT(&v) = VT_BSTR;
                        V_BSTR(&v) = SysAllocString(wszCatName);
                        hr = IDxDiagContainerImpl_AddProp(pSubCont, szCatName, &v);
                        VariantClear(&v);

                        V_VT(&v) = VT_BSTR;
                        V_BSTR(&v) = SysAllocString(wszCatClsid);
                        hr = IDxDiagContainerImpl_AddProp(pSubCont, szClsidCat, &v);
                        VariantClear(&v);

                        hr = IPropertyBag_Read(pPropFilterBag, wszFriendlyName, &v, 0);
                        hr = IDxDiagContainerImpl_AddProp(pSubCont, szName, &v);
                        FIXME("\tName:%s\n", debugstr_w(V_BSTR(&v)));
                        VariantClear(&v);

                        hr = IPropertyBag_Read(pPropFilterBag, wszClsidName, &v, 0);
                        FIXME("\tClsid:%s\n", debugstr_w(V_BSTR(&v)));
                        hr = IDxDiagContainerImpl_AddProp(pSubCont, szClsidFilter, &v);
                        VariantClear(&v);

                        hr = IPropertyBag_Read(pPropFilterBag, wszFilterDataName, &v, NULL);
                        hr = SafeArrayAccessData(V_UNION(&v, parray), (LPVOID*) &pData);
                        prrf = (struct REG_RF*) pData;
                        pCurrent = pData;

                        VariantInit(&v_data);
                        V_VT(&v_data) = VT_UI4;
                        V_UI4(&v_data) = prrf->dwVersion;
                        hr = IDxDiagContainerImpl_AddProp(pSubCont, szName, &v_data);
                        VariantClear(&v_data);
                        V_VT(&v_data) = VT_UI4;
                        V_UI4(&v_data) = prrf->dwMerit;
                        hr = IDxDiagContainerImpl_AddProp(pSubCont, dwMerit, &v_data);
                        VariantClear(&v_data);

                        pCurrent += sizeof(struct REG_RF);
                        for (it = 0; it < prrf->dwPins; ++it) {
                            struct REG_RFP* prrfp = (struct REG_RFP*) pCurrent;
                            UINT j;

                            if (prrfp->dwFlags & REG_PINFLAG_B_OUTPUT) ++dwNOutputs;
                            else ++dwNInputs;

                            pCurrent += sizeof(struct REG_RFP);
                            if (prrfp->bCategory) {
                                pCurrent += sizeof(DWORD);
                            }
                            for (j = 0; j < prrfp->dwMediaTypes; ++j) {
                                struct REG_TYPE* prt = (struct REG_TYPE *)pCurrent;
                                pCurrent += sizeof(*prt);
                            }
                            for (j = 0; j < prrfp->dwMediums; ++j) {
                                DWORD dwOffset = *(DWORD*) pCurrent;
                                pCurrent += sizeof(dwOffset);
                            }
                        }

                        V_VT(&v_data) = VT_UI4;
                        V_UI4(&v_data) = dwNInputs;
                        hr = IDxDiagContainerImpl_AddProp(pSubCont, dwInputs, &v_data);
                        VariantClear(&v_data);
                        V_VT(&v_data) = VT_UI4;
                        V_UI4(&v_data) = dwNOutputs;
                        hr = IDxDiagContainerImpl_AddProp(pSubCont, dwOutputs, &v_data);
                        VariantClear(&v_data);

                        SafeArrayUnaccessData(V_UNION(&v, parray));
                        VariantClear(&v);
                    }
                    IPropertyBag_Release(pPropFilterBag);
                    pPropFilterBag = NULL;
                }
                IEnumMoniker_Release(pEnum);
                pEnum = NULL;
            }
class_enum_failed:
            SysFreeString(wszCatName);
            SysFreeString(wszCatClsid);
            IPropertyBag_Release(pPropBag);
            pPropBag = NULL;
        }
        IEnumMoniker_Release(pMCat);
        pMCat = NULL;
    }

out_show_filters:
    if (NULL != pEmCat) {
        IEnumMoniker_Release(pEmCat);
        pEmCat = NULL;
    }
    if (NULL != pCreateDevEnum) {
        ICreateDevEnum_Release(pCreateDevEnum);
        pCreateDevEnum = NULL;
    }
    return hr;
}