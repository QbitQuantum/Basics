/**************************************************************************
 *  CPrintersExtractIconW_CreateInstane
 *
 *  There is no CPrintersExtractIconW. We just initialize CExtractIcon properly to do our job.
 */
HRESULT WINAPI CPrintersExtractIconW_CreateInstane(LPCITEMIDLIST pidl, REFIID riid, LPVOID *ppv)
{
    CComPtr<IDefaultExtractIconInit> initIcon;
    HRESULT hr = SHCreateDefaultExtractIcon(IID_PPV_ARG(IDefaultExtractIconInit,&initIcon));
    if (FAILED_UNEXPECTEDLY(hr))
        return hr;

    /* FIXME: other icons for default, network, print to file */
    initIcon->SetNormalIcon(swShell32Name, -IDI_SHELL_PRINTER);

    return initIcon->QueryInterface(riid,ppv);
}