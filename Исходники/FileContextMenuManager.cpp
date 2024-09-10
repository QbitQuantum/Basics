CFileContextMenuManager::CFileContextMenuManager(HWND hwnd,
	LPITEMIDLIST pidlParent,std::list<LPITEMIDLIST> pidlItemList) :
m_hwnd(hwnd),
m_pidlParent(ILClone(pidlParent)),
m_pShellContext3(NULL),
m_pShellContext2(NULL),
m_pShellContext(NULL)
{
	IContextMenu *pContextMenu = NULL;
	HRESULT hr;

	for each(auto pidl in pidlItemList)
	{
		m_pidlItemList.push_back(ILClone(pidl));
	}