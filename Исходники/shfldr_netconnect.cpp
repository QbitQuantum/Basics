/**************************************************************************
*	ISF_NetConnect_fnCreateViewObject
*/
HRESULT WINAPI CNetworkConnections::CreateViewObject(
               HWND hwndOwner, REFIID riid, LPVOID * ppvOut)
{
    CSFV cvf;
    HRESULT hr = E_NOINTERFACE;

    if (!ppvOut)
        return hr;

    *ppvOut = NULL;

    if (IsEqualIID(riid, IID_IShellView))
    {
        ZeroMemory(&cvf, sizeof(cvf));
        cvf.cbSize = sizeof(cvf);
        cvf.pshf = static_cast<IShellFolder*>(this);

        IShellView* pShellView;
        hr = SHCreateShellFolderViewEx(&cvf, &pShellView);
        if (SUCCEEDED(hr))
        {
            hr = pShellView->QueryInterface(riid, ppvOut);
            pShellView->Release();
        }
    }

    return hr;
}