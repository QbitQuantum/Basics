void GetExplorerWindows(std::vector<PairHwndPath>& windows, BOOL needPaths) {
    CComPtr<IShellWindows> psw;
    if(!psw.Create(CLSID_ShellWindows, CLSCTX_ALL)) return;
    VARIANT v;
    V_VT(&v) = VT_I4;
    CComPtr<IDispatch> pdisp;
    for(V_I4(&v) = 0; psw->Item(v, &pdisp) == S_OK; V_I4(&v)++) {
        CComPtr<IWebBrowserApp> pwba;
        if(!pwba.QueryFrom(pdisp)) continue;
        PairHwndPath pair;
        if(!SUCCEEDED(pwba->get_HWND((LONG_PTR*)&pair.hwnd))) continue;
        pair.path[0] = 0;

        CComPtr<IServiceProvider> psp;
        CComPtr<IShellBrowser> psb;
        CComPtr<IShellView> psv;
        CComPtr<IFolderView> pfv;
        CComPtr<IPersistFolder2> ppf2;
        CComPtr<IShellFolder> psf;
        LPITEMIDLIST pidlFolder = NULL;
        LPCITEMIDLIST pidlLast = NULL;
        STRRET strret;
        if(needPaths
                && psp.QueryFrom(pwba)
                && SUCCEEDED(psp->QueryService(SID_STopLevelBrowser, IID_IShellBrowser, (void**)&psb))
                && SUCCEEDED(psb->QueryActiveShellView(&psv))
                && pfv.QueryFrom(psv)
                && SUCCEEDED(pfv->GetFolder(IID_IPersistFolder2, (void**)&ppf2))
                && SUCCEEDED(ppf2->GetCurFolder(&pidlFolder))
                && !SHGetPathFromIDList(pidlFolder, pair.path)
                && SUCCEEDED(SHBindToParent(pidlFolder, IID_IShellFolder, (void**)&psf, &pidlLast))
                && SUCCEEDED(psf->GetDisplayNameOf(pidlLast, 0x8000, &strret))) {
            StrRetToBuf(&strret, pidlLast, pair.path, MAX_PATH);
        }
        if(pidlFolder != NULL) CoTaskMemFree(pidlFolder);
        windows.push_back(pair);
    }
}