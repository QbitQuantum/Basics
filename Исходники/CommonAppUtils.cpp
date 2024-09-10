void CCommonAppUtils::MarkWindowAsUnpinnable( HWND hWnd )
{
    typedef HRESULT (WINAPI *SHGPSFW) (HWND hwnd,REFIID riid,void** ppv);

    CAutoLibrary hShell = AtlLoadSystemLibraryUsingFullPath(L"Shell32.dll");

    if (!hShell.IsValid())
        return;

    SHGPSFW pfnSHGPSFW = (SHGPSFW)::GetProcAddress(hShell, "SHGetPropertyStoreForWindow");
    if (pfnSHGPSFW == 0)
         return;

    IPropertyStore *pps = 0;
    HRESULT hr = pfnSHGPSFW(hWnd, IID_PPV_ARGS(&pps));
    if (SUCCEEDED(hr))
    {
        PROPVARIANT var;
        var.vt = VT_BOOL;
        var.boolVal = VARIANT_TRUE;
        hr = pps->SetValue(PKEY_AppUserModel_PreventPinning, var);
        pps->Release();
    }
}