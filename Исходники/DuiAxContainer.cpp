HRESULT CDuiAxContainer::MonikerBindToStorage(IMoniker *pMk, IBindCtx *pBC,
                                IBindStatusCallback *pBSC, REFIID riid, void **ppvObj)
{
    HRESULT hr = E_FAIL;
    CDuiComPtr<IBindCtx> pBCCtx = pBC;
    if (pBCCtx == NULL)
    {
        // creates it if not present
        hr = CreateBindCtx(0, &pBCCtx);
    }

    if ( pBCCtx != NULL )
    {
        if ( pBSC != NULL )
        {
            hr = RegisterBindStatusCallback(pBCCtx, pBSC, NULL, 0);
        }
        hr = pMk->BindToStorage(pBCCtx, NULL, riid, ppvObj);
    }
    return hr;
}