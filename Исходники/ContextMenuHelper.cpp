HRESULT CContextMenuHelper::SHGetContextMenu(std::vector<LPCTSTR> files) {
    HRESULT hr;
    IMalloc *pm = NULL;
    IShellFolder *pDesktop = NULL;
    IShellFolder *psf = NULL;
    LPITEMIDLIST pidl = NULL;
    WCHAR fwname[MAX_PATH + 1];

    if (SUCCEEDED(hr = SHGetMalloc(&pm))) {
        if (SUCCEEDED(hr = SHGetDesktopFolder(&pDesktop))) {
            std::vector<LPITEMIDLIST> pidls;
            IShellFolder* psfFolder = NULL;
            for (UINT i = 0; SUCCEEDED(hr) && i < files.size(); i++) {
                LPCTSTR lpszFilePath = files[i];

                ULONG cch;
                ULONG attrs;

                // Convert to Unicode
                memset(fwname, L'\0', (MAX_PATH + 1) * sizeof(WCHAR));
                MultiByteToWideChar(CP_THREAD_ACP, 0, lpszFilePath, -1, fwname, MAX_PATH);
                if (SUCCEEDED(hr = pDesktop->ParseDisplayName(m_hWnd, NULL, fwname, &cch, &pidl, &attrs))) {
                    LPITEMIDLIST pidlItem = NULL;
                    if (SUCCEEDED(hr = SHBindToParentEx((LPCITEMIDLIST)pidl, IID_IShellFolder, (void **)&psf, (LPCITEMIDLIST *) &pidlItem, pDesktop, pm))) {
                        pidls.push_back(CopyPIDL(pidlItem, pm));
                        pm->Free(pidlItem);
                        if (psfFolder == NULL) {
                            // Remember first folder and we wiil show menu for this one
                            // All other folder will be ignored
                            psfFolder = psf;
                        } else {
                            psf->Release();
                        }
                    }
                    pm->Free(pidl);
                }
            }
            if (SUCCEEDED(hr) && psfFolder != NULL) {
                hr = psfFolder->GetUIObjectOf(m_hWnd, pidls.size(), const_cast<LPCITEMIDLIST*>(pidls.begin()), IID_IContextMenu, NULL, (void**)&m_lpcm);
                psfFolder->Release();
            }
            FreeItemIDList(pidls, pm);
            pDesktop->Release();
        }
        pm->Release();
    }

    return hr;
}