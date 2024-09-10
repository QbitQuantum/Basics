HRESULT GetItemAttributes(LPCITEMIDLIST pidl,SFGAOF *pItemAttributes)
{
	if(pidl == NULL ||
		pItemAttributes == NULL)
	{
		return E_FAIL;
	}

	IShellFolder	*pShellFolder = NULL;
	LPITEMIDLIST	pidlRelative = NULL;
	HRESULT			hr;

	hr = SHBindToParent(pidl, IID_PPV_ARGS(&pShellFolder),
	(LPCITEMIDLIST *)&pidlRelative);

	if(SUCCEEDED(hr))
	{
		hr = pShellFolder->GetAttributesOf(1,(LPCITEMIDLIST *)&pidlRelative,pItemAttributes);

		pShellFolder->Release();
	}

	return hr;
}