/*
 * Browse for a folder and update the folder edit box
 */
void BrowseForFolder(void) {

	BROWSEINFOW bi;
	LPITEMIDLIST pidl;
	WCHAR *wpath;
	size_t i;
	HRESULT hr;
	IShellItem *psi = NULL;
	IShellItem *si_path = NULL;	// Automatically freed
	IFileOpenDialog *pfod = NULL;
	WCHAR *fname;
	char* tmp_path = NULL;

	dialog_showing++;
	hr = CoCreateInstance(&CLSID_FileOpenDialog, NULL, CLSCTX_INPROC,
		&IID_IFileOpenDialog, (LPVOID)&pfod);
	if (FAILED(hr)) {
		dprintf("CoCreateInstance for FileOpenDialog failed: error %X", hr);
		pfod = NULL;	// Just in case
		goto fallback;
	}
	hr = pfod->lpVtbl->SetOptions(pfod, FOS_PICKFOLDERS);
	if (FAILED(hr)) {
		dprintf("Failed to set folder option for FileOpenDialog: error %X", hr);
		goto fallback;
	}
	// Set the initial folder (if the path is invalid, will simply use last)
	wpath = utf8_to_wchar(szFolderPath);
	// The new IFileOpenDialog makes us split the path
	fname = NULL;
	if ((wpath != NULL) && (wcslen(wpath) >= 1)) {
		for (i = wcslen(wpath) - 1; i != 0; i--) {
			if (wpath[i] == L'\\') {
				wpath[i] = 0;
				fname = &wpath[i + 1];
				break;
			}
		}
	}

	hr = SHCreateItemFromParsingName(wpath, NULL, &IID_IShellItem, (LPVOID)&si_path);
	if (SUCCEEDED(hr)) {
		if (wpath != NULL) {
			pfod->lpVtbl->SetFolder(pfod, si_path);
		}
		if (fname != NULL) {
			pfod->lpVtbl->SetFileName(pfod, fname);
		}
	}
	safe_free(wpath);

	hr = pfod->lpVtbl->Show(pfod, hMainDialog);
	if (SUCCEEDED(hr)) {
		hr = pfod->lpVtbl->GetResult(pfod, &psi);
		if (SUCCEEDED(hr)) {
			psi->lpVtbl->GetDisplayName(psi, SIGDN_FILESYSPATH, &wpath);
			tmp_path = wchar_to_utf8(wpath);
			CoTaskMemFree(wpath);
			if (tmp_path == NULL) {
				dprintf("Could not convert path");
			} else {
				static_strcpy(szFolderPath, tmp_path);
				safe_free(tmp_path);
			}
		} else {
			dprintf("Failed to set folder option for FileOpenDialog: error %X", hr);
		}
	} else if ((hr & 0xFFFF) != ERROR_CANCELLED) {
		// If it's not a user cancel, assume the dialog didn't show and fallback
		dprintf("Could not show FileOpenDialog: error %X", hr);
		goto fallback;
	}
	pfod->lpVtbl->Release(pfod);
	dialog_showing--;
	return;
fallback:
	if (pfod != NULL) {
		pfod->lpVtbl->Release(pfod);
	}

	memset(&bi, 0, sizeof(BROWSEINFOW));
	bi.hwndOwner = hMainDialog;
	bi.lpszTitle = L"Please select folder";
	bi.lpfn = BrowseInfoCallback;
	// BIF_NONEWFOLDERBUTTON = 0x00000200 is unknown on MinGW
	bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS |
		BIF_DONTGOBELOWDOMAIN | BIF_EDITBOX | 0x00000200;
	pidl = SHBrowseForFolderW(&bi);
	if (pidl != NULL) {
		CoTaskMemFree(pidl);
	}
	dialog_showing--;
}