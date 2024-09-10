void CWin7::SetAppID(HWND hWnd, bool bDestory )
{
    IPropertyStore *pps;
    HRESULT hr = SHGetPropertyStoreForWindow2(hWnd, IID_PPV_ARGS(&pps));
    if (SUCCEEDED(hr))
    {
        PROPVARIANT pv;
		if ( !bDestory )
			hr = InitPropVariantFromString(g_wszAppID, &pv);
		else
			PropVariantInit(&pv);

        if (SUCCEEDED(hr))
        {
            hr = pps->SetValue(PKEY_AppUserModel_ID, pv);
            PropVariantClear(&pv);
        }
        pps->Release();
    }
}