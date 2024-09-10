void ShellBrowser::UpdateFolderView(IShellFolder* folder)
{
    CONTEXT("ShellBrowser::UpdateFolderView()");

    FOLDERSETTINGS fs;
    IShellView* pLastShellView = _pShellView;

    _folder = folder;

    if (pLastShellView)
        pLastShellView->GetCurrentInfo(&fs);
    else {
        fs.ViewMode = _create_info._open_mode&OWM_DETAILS? FVM_DETAILS: FVM_ICON;
        fs.fFlags = FWF_NOCLIENTEDGE|FWF_BESTFITWINDOW;
    }

#ifndef __MINGW32__	// IShellFolderViewCB missing in MinGW (as of 25.09.2005)
    SFV_CREATE sfv_create;

    sfv_create.cbSize = sizeof(SFV_CREATE);
    sfv_create.pshf = folder;
    sfv_create.psvOuter = NULL;
    sfv_create.psfvcb = this;

    HRESULT hr = SHCreateShellFolderView(&sfv_create, &_pShellView);
#else
    HRESULT hr = folder->CreateViewObject(_hwnd, IID_IShellView, (void**)&_pShellView);
#endif

    if (FAILED(hr)) {
        _pShellView = NULL;
        return;
    }

    RECT rect = {CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT};
    hr = _pShellView->CreateViewWindow(pLastShellView, &fs, static_cast<IShellBrowser*>(this), &rect, &_right_hwnd/*&m_hWndListView*/);

    if (pLastShellView) {
        pLastShellView->GetCurrentInfo(&fs);
        pLastShellView->UIActivate(SVUIA_DEACTIVATE);
        pLastShellView->DestroyViewWindow();
        pLastShellView->Release();
    }

    _pShellView->UIActivate(SVUIA_ACTIVATE_NOFOCUS);
}