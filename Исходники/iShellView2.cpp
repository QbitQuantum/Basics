HRESULT CShellView2::SelectAndPositionItem(LPCITEMIDLIST pidlItem,UINT uFlags,POINT *ppt)
{
	LPITEMIDLIST pidlComplete = NULL;
	LPITEMIDLIST pidlDirectory = NULL;

	/* The idlist passed is only a relative (child) one. Combine
	it with the tabs' current directory to get a full idlist. */
	pidlDirectory = m_pexpp->GetActiveShellBrowser()->QueryCurrentDirectoryIdl();
	pidlComplete = ILCombine(pidlDirectory,pidlItem);

	m_pexpp->GetActiveShellBrowser()->QueueRename(pidlComplete);

	CoTaskMemFree(pidlDirectory);
	CoTaskMemFree(pidlComplete);

	return S_OK;
}