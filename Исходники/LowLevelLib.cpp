//local helpers:
static FC_ARSTAT NodeListToSafeArray(FC_CGArray<FC_CArNode*>* pNList, SAFEARRAY** ppsa)
{
    HRESULT       hr;
    SAFEARRAY*    psa;
    long          i;
    long          nNodes;
    FC_CArNode*   pNode;
    const TCHAR*  pId;
    BSTR          bstr;

    if(!ppsa)
        return FC_AR_OK;

    *ppsa = NULL;

    nNodes = pNList->getUsed();
    psa = SafeArrayCreateVector(VT_BSTR, 0, nNodes);
    if(!psa)
        return FC_AR_OUTOFMEM;

    for(i=0; i<nNodes; i++)
    {
        pNode = pNList->get(i);
        pId   = pNode->getName();
#ifdef UNICODE
        bstr = SysAllocString(pId);
        hr = SafeArrayPutElement(psa, &i, bstr);
        SysFreeString(bstr);
#else
        wchar_t wBuffer[3*MAX_PATH];
        int iOk = FC_StringToWideChar(pId, wBuffer, FC_ARRAY_LEN(wBuffer));
        assert(iOk>0);
        bstr = SysAllocString(wBuffer);
        hr = SafeArrayPutElement(psa, &i, bstr);
        SysFreeString(bstr);
#endif
        if(FAILED(hr))
        {
            SafeArrayDestroy(psa);
            return FC_AR_OUTOFMEM;
        }
    }

    *ppsa = psa;
    return FC_AR_OK;
}