void CShellBrowser::BrowseVirtualFolder(LPITEMIDLIST pidlDirectory)
{
	IShellFolder	*pShellFolder = NULL;
	IEnumIDList		*pEnumIDList = NULL;
	LPITEMIDLIST	rgelt = NULL;
	STRRET			str;
	SHCONTF			EnumFlags;
	TCHAR			szFileName[MAX_PATH];
	ULONG			uFetched;
	HRESULT			hr;

	DetermineFolderVirtual(pidlDirectory);

	hr = BindToIdl(pidlDirectory, IID_PPV_ARGS(&pShellFolder));

	if(SUCCEEDED(hr))
	{
		m_pidlDirectory = ILClone(pidlDirectory);

		EnumFlags = SHCONTF_FOLDERS|SHCONTF_NONFOLDERS;

		if(m_bShowHidden)
			EnumFlags |= SHCONTF_INCLUDEHIDDEN;

		hr = pShellFolder->EnumObjects(m_hOwner,EnumFlags,&pEnumIDList);

		if(SUCCEEDED(hr) && pEnumIDList != NULL)
		{
			uFetched = 1;
			while(pEnumIDList->Next(1,&rgelt,&uFetched) == S_OK && (uFetched == 1))
			{
				ULONG uAttributes = SFGAO_FOLDER;

				pShellFolder->GetAttributesOf(1,(LPCITEMIDLIST *)&rgelt,&uAttributes);

				/* If this is a virtual folder, only use SHGDN_INFOLDER. If this is
				a real folder, combine SHGDN_INFOLDER with SHGDN_FORPARSING. This is
				so that items in real folders can still be shown with extensions, even
				if the global, Explorer option is disabled.
				Also use only SHGDN_INFOLDER if this item is a folder. This is to ensure
				that specific folders in Windows 7 (those under C:\Users\Username) appear
				correctly. */
				if(m_bVirtualFolder || (uAttributes & SFGAO_FOLDER))
					hr = pShellFolder->GetDisplayNameOf(rgelt,SHGDN_INFOLDER,&str);
				else
					hr = pShellFolder->GetDisplayNameOf(rgelt,SHGDN_INFOLDER|SHGDN_FORPARSING,&str);

				if(SUCCEEDED(hr))
				{
					StrRetToBuf(&str,rgelt,szFileName,MAX_PATH);

					AddItemInternal(pidlDirectory,rgelt,szFileName,-1,FALSE);
				}

				CoTaskMemFree((LPVOID)rgelt);
			}

			pEnumIDList->Release();
		}

		pShellFolder->Release();
	}
}