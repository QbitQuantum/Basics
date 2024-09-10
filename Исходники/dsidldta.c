//
// Creates a HDROP (Win 3.1 compatible file list) from DS_HIDA.
//
//
HRESULT CDS_IDLData_GetHDrop(IDataObject *pdtobj, STGMEDIUM *pmedium, BOOL fAltName)
{
    HRESULT hres = E_OUTOFMEMORY;
    LPITEMIDLIST pidl = NULL;   // realloced in HIDA_FillIDList
    STGMEDIUM medium;
    TCHAR szPath[MAX_PATH];
    UINT i, cbAlloc = SIZEOF(DROPFILES) + SIZEOF(TCHAR);        // header + null terminator
    LPIDA pida = DataObj_GetDS_HIDA(pdtobj, &medium);

    Assert(pida && pida->cidl); // we created this

    for (i = 0; i < pida->cidl; i++)
    {
        // HIDA_FillIDList may realloc pidl
        LPITEMIDLIST pidlTemp = HIDA_FillIDList(medium.hGlobal, i, pidl);
        if (pidlTemp == NULL)
        {
            // hres = E_OUTOFMEMORY; // already set
            break;
        }
        pidl = pidlTemp;

        // We may ask for the ALT name even if they did not ask for it in the
        // case where we failed to get the long name...
        if (!SHGetPathFromIDListEx(pidl, szPath, fAltName)
                && !(!fAltName && (SHGetPathFromIDListEx(pidl, szPath, TRUE))))
        {
            // The path probably exceeds the max lenght, lets Bail...
            DebugMsg(DM_TRACE, TEXT("s.CFSIDLData_GetHDrop: SHGetPathFromIDList failed."));
            hres = E_FAIL;
            goto Abort;
        }
        cbAlloc += lstrlen(szPath) * SIZEOF(TCHAR) + SIZEOF(TCHAR);
    }
    pmedium->hGlobal = GlobalAlloc(GPTR, cbAlloc);
    if (pmedium->hGlobal)
    {
        LPDROPFILES pdf = (LPDROPFILES)pmedium->hGlobal;
        LPTSTR pszFiles = (LPTSTR)(pdf + 1);
        pdf->pFiles = SIZEOF(DROPFILES);
        Assert(pdf->pt.x==0);
        Assert(pdf->pt.y==0);
        Assert(pdf->fNC==FALSE);
        Assert(pdf->fWide==FALSE);
#ifdef UNICODE
        pdf->fWide = TRUE;
#endif

        for (i = 0; i < pida->cidl; i++)
        {
            LPITEMIDLIST pidlTemp = HIDA_FillIDList(medium.hGlobal, i, pidl);
            Assert(pidl == pidlTemp);

            // Don't read directly into buffer as we my have been forced to use alternate name and the
            // total path we allocated may be smaller than we would tromp on which will screw up the heap.
            if (!SHGetPathFromIDListEx(pidl, szPath, fAltName))
                SHGetPathFromIDListEx(pidl, szPath, TRUE);

            lstrcpy(pszFiles, szPath);
            pszFiles += lstrlen(pszFiles) + 1;

            Assert((UINT)((LPBYTE)pszFiles - (LPBYTE)pdf) < cbAlloc);
        }
        Assert((LPTSTR)((LPBYTE)pdf + cbAlloc - SIZEOF(TCHAR)) == pszFiles);
        Assert(*pszFiles == 0); // zero init alloc

        pmedium->tymed = TYMED_HGLOBAL;
        pmedium->pUnkForRelease = NULL;

        hres = S_OK;
    }
Abort:
    HIDA_ReleaseStgMedium(pida, &medium);

    ILFree(pidl);

    return hres;
}