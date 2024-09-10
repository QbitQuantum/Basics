bool DesktopShellView::DoContextMenu(int x, int y)
{
	IDataObject* selection;

	HRESULT hr = _pShellView->GetItemObject(SVGIO_SELECTION, IID_IDataObject, (void**)&selection);
	if (FAILED(hr))
		return false;

	PIDList pidList;

	hr = pidList.GetData(selection);
	if (FAILED(hr)) {
		selection->Release();
		//CHECKERROR(hr);
		return false;
	}

	LPIDA pida = pidList;
	if (!pida->cidl) {
		selection->Release();
		return false;
	}

	LPCITEMIDLIST parent_pidl = (LPCITEMIDLIST) ((LPBYTE)pida+pida->aoffset[0]);

	LPCITEMIDLIST* apidl = (LPCITEMIDLIST*) alloca(pida->cidl*sizeof(LPCITEMIDLIST));

	for(int i=pida->cidl; i>0; --i)
		apidl[i-1] = (LPCITEMIDLIST) ((LPBYTE)pida+pida->aoffset[i]);

	hr = ShellFolderContextMenu(ShellFolder(parent_pidl), _hwnd, pida->cidl, apidl, x, y, _cm_ifs);

	selection->Release();

	if (SUCCEEDED(hr))
		refresh();
	else
		CHECKERROR(hr);

	return true;
}