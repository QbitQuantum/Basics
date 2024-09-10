CBrowseFolder::retVal CBrowseFolder::Show(HWND parent, CString& path, const CString& sDefaultPath /* = CString() */)
{
	retVal ret = OK;		//assume OK
	m_sDefaultPath = sDefaultPath;
	if (m_sDefaultPath.IsEmpty() && !path.IsEmpty())
	{
		// if the result path already contains a path, use that as the default path
		m_sDefaultPath = path;
	}

	HRESULT hr;

	// Create a new common open file dialog
	IFileOpenDialog* pfd = NULL;
	hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
	if (SUCCEEDED(hr))
	{
		// Set the dialog as a folder picker
		DWORD dwOptions;
		if (SUCCEEDED(hr = pfd->GetOptions(&dwOptions)))
		{
			hr = pfd->SetOptions(dwOptions | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST);
		}

		// Set a title
		if (SUCCEEDED(hr))
		{
			TCHAR * nl = _tcschr(m_title, '\n');
			if (nl)
				*nl = 0;
			pfd->SetTitle(m_title);
		}

		// set the default folder
		if (SUCCEEDED(hr))
		{
			typedef HRESULT (WINAPI *SHCIFPN)(PCWSTR pszPath, IBindCtx * pbc, REFIID riid, void ** ppv);

			CAutoLibrary hLib = AtlLoadSystemLibraryUsingFullPath(L"shell32.dll");
			if (hLib)
			{
				SHCIFPN pSHCIFPN = (SHCIFPN)GetProcAddress(hLib, "SHCreateItemFromParsingName");
				if (pSHCIFPN)
				{
					IShellItem *psiDefault = 0;
					hr = pSHCIFPN(m_sDefaultPath, NULL, IID_PPV_ARGS(&psiDefault));
					if (SUCCEEDED(hr))
					{
						hr = pfd->SetFolder(psiDefault);
						psiDefault->Release();
					}
				}
			}
		}

		if (m_CheckText[0] != 0)
		{
			IFileDialogCustomize* pfdCustomize = 0;
			hr = pfd->QueryInterface(IID_PPV_ARGS(&pfdCustomize));
			if (SUCCEEDED(hr))
			{
				pfdCustomize->StartVisualGroup(100, L"");
				pfdCustomize->AddCheckButton(101, m_CheckText, FALSE);
				if (m_CheckText2[0] != 0)
				{
					pfdCustomize->AddCheckButton(102, m_CheckText2, FALSE);
				}
				pfdCustomize->EndVisualGroup();
				pfdCustomize->Release();
			}
		}

		// Show the open file dialog
		if (SUCCEEDED(hr) && SUCCEEDED(hr = pfd->Show(parent)))
		{
			// Get the selection from the user
			IShellItem* psiResult = NULL;
			hr = pfd->GetResult(&psiResult);
			if (SUCCEEDED(hr))
			{
				PWSTR pszPath = NULL;
				hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);
				if (SUCCEEDED(hr))
				{
					path = pszPath;
					CoTaskMemFree(pszPath);
				}
				psiResult->Release();

				IFileDialogCustomize* pfdCustomize = 0;
				hr = pfd->QueryInterface(IID_PPV_ARGS(&pfdCustomize));
				if (SUCCEEDED(hr))
				{
					pfdCustomize->GetCheckButtonState(101, &m_bCheck);
					pfdCustomize->GetCheckButtonState(102, &m_bCheck2);
					pfdCustomize->Release();
				}
			}
			else
				ret = CANCEL;
		}
		else
			ret = CANCEL;

		pfd->Release();
	}
	else
	{
		BROWSEINFO browseInfo		= {};
		browseInfo.hwndOwner		= parent;
		browseInfo.pidlRoot			= m_root;
		browseInfo.pszDisplayName	= m_displayName;
		browseInfo.lpszTitle		= m_title;
		browseInfo.ulFlags			= m_style;
		browseInfo.lParam			= (LPARAM)this;

		if ((_tcslen(m_CheckText) > 0)||(!m_sDefaultPath.IsEmpty()))
		{
			browseInfo.lpfn = BrowseCallBackProc;
		}

		PCIDLIST_ABSOLUTE itemIDList = SHBrowseForFolder(&browseInfo);

		//is the dialog canceled?
		if (!itemIDList)
			ret = CANCEL;

		if (ret != CANCEL)
		{
			if (!SHGetPathFromIDList(itemIDList, path.GetBuffer(MAX_PATH)))		// MAX_PATH ok. Explorer can't handle paths longer than MAX_PATH.
				ret = NOPATH;

			path.ReleaseBuffer();

			CoTaskMemFree((LPVOID)itemIDList);
		}
	}

	return ret;
}