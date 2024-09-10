HRESULT STDAPICALLTYPE 
ClassTableRegisterClassObjects(COCLASS_ENTRY *pTable, 
                               DWORD dwClsCtx,
                               DWORD dwRegCls,
                               BOOL bResumeClassObjects )
{
    HRESULT hr = E_FAIL;
#ifdef _WIN32_DCOM
    dwRegCls |= REGCLS_SUSPENDED;
#else
    assert(bResumeClassObjects);
#endif
    if (pTable)
    {
        hr = S_OK;
        COCLASS_ENTRY *pHead = pTable;
        for (; SUCCEEDED(hr) && pTable->pclsid != &GUID_NULL; pTable++)
        {
            if (pTable->pfnGetClassObject)
            {
                IUnknown *pUnk = 0;
                hr = pTable->pfnGetClassObject(IID_IUnknown, (void**)&pUnk);
                if (SUCCEEDED(hr))
                {
                    hr = CoRegisterClassObject(*pTable->pclsid,
                                               pUnk,
                                               dwClsCtx,
                                               dwRegCls,
                                               &pTable->dwReg);
                    pUnk->Release();
                }
            }
        }
        
        if (SUCCEEDED(hr) && bResumeClassObjects)
            hr = CoResumeClassObjects();

        if (FAILED(hr)) // unwind if failed
            for (pTable--; pTable >= pHead; pTable--)
                if (pTable->pfnGetClassObject)
                    CoRevokeClassObject(pTable->dwReg);
        
    }
    return hr;
}