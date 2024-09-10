bool prepareContextMenuForObjects(std::vector<std::wstring> objects, void * parentWindow, HMENU& hmenu, IContextMenu*& imenu)
{
	ComInitializer comInitializer;

	if (objects.empty())
		return false;

	std::vector<ITEMIDLIST*> ids;
	std::vector<LPCITEMIDLIST> relativeIds;
	IShellFolder * ifolder = 0;
	for (size_t i = 0; i < objects.size(); ++i)
	{
		std::replace(objects[i].begin(), objects[i].end(), '/', '\\');
		ids.push_back(0);
		HRESULT result = SHParseDisplayName(objects[i].c_str(), 0, &ids.back(), 0, 0);
		if (!SUCCEEDED(result) || !ids.back())
		{
			ids.pop_back();
			continue;
		}

		relativeIds.push_back(0);
		result = SHBindToParent(ids.back(), IID_IShellFolder, (void**)&ifolder, &relativeIds.back());
		if (!SUCCEEDED(result) || !relativeIds.back())
			relativeIds.pop_back();
		else if (i < objects.size() - 1 && ifolder)
		{
			ifolder->Release();
			ifolder = nullptr;
		}
	}

	CItemIdArrayReleaser arrayReleaser(ids);

	assert_r(parentWindow);
	assert_and_return_message_r(ifolder, "Error getting ifolder", false);
	assert_and_return_message_r(!relativeIds.empty(), "RelativeIds is empty", false);

	imenu = 0;
	HRESULT result = ifolder->GetUIObjectOf((HWND)parentWindow, (UINT)relativeIds.size(), (const ITEMIDLIST **)relativeIds.data(), IID_IContextMenu, 0, (void**)&imenu);
	if (!SUCCEEDED(result) || !imenu)
		return false;

	hmenu = CreatePopupMenu();
	if (!hmenu)
		return false;
	return (SUCCEEDED(imenu->QueryContextMenu(hmenu, 0, 1, 0x7FFF, CMF_NORMAL)));
}