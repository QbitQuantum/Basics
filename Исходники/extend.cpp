STDMETHODIMP CWiaUIExtension::GetDeviceIcon( BSTR bstrDeviceId, HICON *phIcon, ULONG nSize )
{
    UNREFERENCED_PARAMETER(bstrDeviceId);

    //
    // Load an icon, and copy it, using CopyIcon, so it will still be valid if our interface is freed
    //
    HICON hIcon = reinterpret_cast<HICON>(LoadImage( _Module.m_hInst, MAKEINTRESOURCE(IDI_TESTDEVICE), IMAGE_ICON, nSize, nSize, LR_DEFAULTCOLOR ));
    if (hIcon)
    {
        *phIcon = CopyIcon(hIcon);
        DestroyIcon(hIcon);
        return S_OK;
    }
    return E_NOTIMPL;
}