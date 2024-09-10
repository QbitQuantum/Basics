HRESULT wiasGetDriverItemPrivateContext(
    _In_ BYTE* pWiasContext,
    _Out_ BYTE** ppWiaDriverItemContext)
{
    HRESULT hr = E_INVALIDARG;

    if (pWiasContext && ppWiaDriverItemContext)
    {
        IWiaDrvItem *pIWiaDrvItem = NULL;

        hr = wiasGetDrvItem(pWiasContext, &pIWiaDrvItem);

        if (SUCCEEDED(hr))
        {
            hr = pIWiaDrvItem->GetDeviceSpecContext(ppWiaDriverItemContext);

            //
            // The caller will handle the failure case.  A failure, may mean that
            // the the WIA item does not have a private device specific context
            // stored.  This is OK, because is is not required.
            //
        }
        else
        {
            WIAEX_ERROR((g_hInst, "Failed to get the WIA driver item from the application item, hr = 0x%08X", hr));
        }
    }
    else
    {
        WIAEX_ERROR((g_hInst, "Invalid parameter"));
    }
    return hr;
}