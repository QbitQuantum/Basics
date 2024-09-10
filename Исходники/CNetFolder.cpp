/**************************************************************************
*    CNetFolder::GetUIObjectOf
*
* PARAMETERS
*  hwndOwner [in]  Parent window for any output
*  cidl      [in]  array size
*  apidl     [in]  simple pidl array
*  riid      [in]  Requested Interface
*  prgfInOut [   ] reserved
*  ppvObject [out] Resulting Interface
*
*/
HRESULT WINAPI CNetFolder::GetUIObjectOf(HWND hwndOwner, UINT cidl, PCUITEMID_CHILD_ARRAY apidl, REFIID riid,
        UINT * prgfInOut, LPVOID * ppvOut)
{
    LPVOID pObj = NULL;
    HRESULT hr = E_INVALIDARG;

    TRACE("(%p)->(%p,%u,apidl=%p,%s,%p,%p)\n", this,
          hwndOwner, cidl, apidl, shdebugstr_guid (&riid), prgfInOut, ppvOut);

    if (!ppvOut)
        return hr;

    *ppvOut = NULL;

    if (IsEqualIID(riid, IID_IContextMenu) && (cidl >= 1))
    {
        IContextMenu * pCm = NULL;
        HKEY hkey;
        UINT cKeys = 0;
        AddClassKeyToArray(L"Folder", &hkey, &cKeys);
        hr = CDefFolderMenu_Create2(pidlRoot, hwndOwner, cidl, apidl, this, NetFolderMenuCallback, cKeys, &hkey, &pCm);
        pObj = pCm;
    }
    else if (IsEqualIID(riid, IID_IDataObject) && (cidl >= 1))
    {
        IDataObject * pDo = NULL;
        hr = IDataObject_Constructor (hwndOwner, pidlRoot, apidl, cidl, &pDo);
        pObj = pDo;
    }
    else if ((IsEqualIID(riid, IID_IExtractIconA) || IsEqualIID(riid, IID_IExtractIconW)) && (cidl == 1))
    {
        hr = CNetFolderExtractIcon_CreateInstance(apidl[0], riid, &pObj);
    }
    else if (IsEqualIID(riid, IID_IDropTarget) && (cidl >= 1))
    {
        IDropTarget * pDt = NULL;
        hr = this->QueryInterface(IID_PPV_ARG(IDropTarget, &pDt));
        pObj = pDt;
    }
    else
        hr = E_NOINTERFACE;

    if (SUCCEEDED(hr) && !pObj)
        hr = E_OUTOFMEMORY;

    *ppvOut = pObj;
    TRACE("(%p)->hr=0x%08x\n", this, hr);
    return hr;
}