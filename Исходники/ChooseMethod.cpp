bool SelectFolder(HWND hOwner)
{
	BROWSEINFO info;
	LPITEMIDLIST pidlist;
	TCHAR path[MAX_PATH];

	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
	{
		return false;
	}
	
	info.hwndOwner = hOwner;
	info.pidlRoot = NULL;
	info.pszDisplayName = path;
	info.lpszTitle = _T("Select a game/mod folder");
	info.ulFlags = BIF_EDITBOX | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	info.lpfn = NULL;
	info.lParam = 0;
	info.iImage = 0;

	if ((pidlist = SHBrowseForFolder(&info)) == NULL)
	{
		CoUninitialize();
		return false;
	}

	/* This hellish code is from MSDN and translate shortcuts to real targets.
	 * God almighty, I wish Window used real symlinks.
	 */
	bool acquire_success = false;
	bool is_link = false;
	IShellFolder *psf = NULL;
	LPCITEMIDLIST new_item_list;
	HRESULT hr;
	
	hr = SHBindToParent(pidlist, IID_IShellFolder, (void **)&psf, &new_item_list);
	if (SUCCEEDED(hr))
	{
		IShellLink *psl = NULL;

		hr = psf->GetUIObjectOf(hOwner, 1, &new_item_list, IID_IShellLink, NULL, (void **)&psl);
		if (SUCCEEDED(hr))
		{
			LPITEMIDLIST new_item_list;

			hr = psl->GetIDList(&new_item_list);
			if (SUCCEEDED(hr))
			{
				is_link = true;

				hr = SHGetPathFromIDList(new_item_list, method_path);
				if (SUCCEEDED(hr))
				{
					acquire_success = true;
				}

				CoTaskMemFree(new_item_list);
			}
			psl->Release();
		}
		psf->Release();
	}

	if (!acquire_success && !is_link)
	{
		hr = SHGetPathFromIDList(pidlist, method_path);
		if (SUCCEEDED(hr))
		{
			acquire_success = true;
		}
	}

	/* That was awful.  shoo, shoo, COM */
	CoTaskMemFree(pidlist);
	CoUninitialize();

	return acquire_success;
}