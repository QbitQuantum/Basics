//
// A helper function to be called from ISF::GetDisplayNameOf implementation
//
HRESULT SHGetPathHelper(LPCITEMIDLIST pidlFolder, LPCITEMIDLIST pidl, LPSTRRET pStrRet)
{
    HRESULT hres;
    LPITEMIDLIST pidlFull = ILCombine(pidlFolder, pidl);
    if (pidlFull)
    {
#ifdef UNICODE
        TCHAR   szName[MAX_PATH];
#endif

        pStrRet->uType = STRRET_CSTR;       // Return no name if failure
        pStrRet->cStr[0] = '\0';

#ifdef UNICODE
        if (SHGetPathFromIDList(pidlFull, szName))
        {
            pStrRet->pOleStr = (LPOLESTR)SHAlloc((lstrlen(szName)+1)*SIZEOF(TCHAR));
            if ( pStrRet->pOleStr != NULL ) {
                lstrcpy(pStrRet->pOleStr, szName);
                pStrRet->uType = STRRET_OLESTR;
                hres = S_OK;
            } else {
                hres = E_OUTOFMEMORY;
            }
        }
#else
        if (SHGetPathFromIDList(pidlFull, pStrRet->cStr))
        {
            hres = NOERROR;
        }
#endif
        else
        {
            hres = E_INVALIDARG;
        }
        ILFree(pidlFull);
    }
    else
    {
        hres = E_OUTOFMEMORY;
    }
    return hres;
}