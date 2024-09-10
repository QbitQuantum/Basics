bool PEFileDiscoverWindow(
	HWND hParent,
	std::wstring &filename,
	const wchar_t *pszWindowTitle)
{
	HRESULT hr;
	bool br = false;
	CComPtr<IFileOpenDialog> pWindow;
	// Create the file-open dialog COM object.
	hr = pWindow.CoCreateInstance(__uuidof(FileOpenDialog));
	if (FAILED(hr)) {
		ReportErrorMessage(L"FileOpenWindowProvider", hr);
		return false;
	}

	// Set the dialog's caption text and the available file types.
	// NOTE: Error handling omitted here for clarity.
	hr = pWindow->SetFileTypes(sizeof(filterSpec) / sizeof(filterSpec[0]), filterSpec);
	hr = pWindow->SetFileTypeIndex(1);
	pWindow->SetTitle(pszWindowTitle ? pszWindowTitle : L"Open File Provider");
	hr = pWindow->Show(hParent);
	if (SUCCEEDED(hr)) {
		CComPtr<IShellItem> pItem;
		hr = pWindow->GetResult(&pItem);
		if (SUCCEEDED(hr)) {
			PWSTR pwsz = NULL;
			hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pwsz);
			if (SUCCEEDED(hr)) {
				filename = pwsz;
				br = true;
				CoTaskMemFree(pwsz);
			}
		}
	}
	return br;
}