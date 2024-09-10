BOOL ActiveScriptImpl::AddScriptItem(BSTR namedItem, LPUNKNOWN lpUnknown, DWORD dwFlags)
{
	// Add Top-level Global Named Item
	if (scriptPtr == NULL || lpUnknown == NULL)
		return false;

	HRESULT hr;

	if (namedItems.contains(namedItem))
		return true;	// This item has already been added

	// Need to save the item so that GetItemInfo() will work.
	AtlTrace(L"Adding named item called %s\n", namedItem);
	namedItems.put(namedItem, lpUnknown);
	if (dwFlags & MY_SCRIPTITEM_WEAK)
	{
		int *pInt = new int[1];
		*pInt = 0;
		weakItems.put(namedItem, pInt);
	}

	hr = scriptPtr->AddNamedItem(namedItem, dwFlags & SCRIPTITEM_ALL_FLAGS);
	if (!SUCCEEDED(hr))
	{
		namedItems.remove(namedItem);
		weakItems.remove(namedItem);
		return false;
	}

	// Connected to object sink-interface.
	if (dwFlags & SCRIPTITEM_ISSOURCE)
		needToConnect = true;

	return true;
}