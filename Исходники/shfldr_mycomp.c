/**************************************************************************
*    ISF_MyComputer_fnParseDisplayName
*/
static HRESULT WINAPI ISF_MyComputer_fnParseDisplayName (IShellFolder2 *iface,
               HWND hwndOwner, LPBC pbc, LPOLESTR lpszDisplayName,
               DWORD * pchEaten, LPITEMIDLIST * ppidl, DWORD * pdwAttributes)
{
    IMyComputerFolderImpl *This = impl_from_IShellFolder2(iface);
    HRESULT hr = E_INVALIDARG;
    LPCWSTR szNext = NULL;
    WCHAR szElement[MAX_PATH];
    LPITEMIDLIST pidlTemp = NULL;
    CLSID clsid;

    TRACE("(%p)->(HWND=%p,%p,%p=%s,%p,pidl=%p,%p)\n", This,
          hwndOwner, pbc, lpszDisplayName, debugstr_w (lpszDisplayName),
          pchEaten, ppidl, pdwAttributes);

    *ppidl = 0;
    if (pchEaten)
        *pchEaten = 0;        /* strange but like the original */

    /* handle CLSID paths */
    if (lpszDisplayName[0] == ':' && lpszDisplayName[1] == ':')
    {
        szNext = GetNextElementW (lpszDisplayName, szElement, MAX_PATH);
        TRACE ("-- element: %s\n", debugstr_w (szElement));
        SHCLSIDFromStringW (szElement + 2, &clsid);
        pidlTemp = _ILCreateGuid (PT_GUID, &clsid);
    }
    /* do we have an absolute path name ? */
    else if (PathGetDriveNumberW (lpszDisplayName) >= 0 &&
              lpszDisplayName[2] == (WCHAR) '\\')
    {
        szNext = GetNextElementW (lpszDisplayName, szElement, MAX_PATH);
        /* make drive letter uppercase to enable PIDL comparison */
        szElement[0] = toupper(szElement[0]);
        pidlTemp = _ILCreateDrive (szElement);
    }

    if (szNext && *szNext)
    {
        hr = SHELL32_ParseNextElement (iface, hwndOwner, pbc, &pidlTemp,
                              (LPOLESTR) szNext, pchEaten, pdwAttributes);
    }
    else
    {
        if (pdwAttributes && *pdwAttributes)
            SHELL32_GetItemAttributes ((IShellFolder*)&This->IShellFolder2_iface, pidlTemp,
                    pdwAttributes);
        hr = S_OK;
    }

    *ppidl = pidlTemp;

    TRACE ("(%p)->(-- ret=0x%08x)\n", This, hr);

    return hr;
}