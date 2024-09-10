IFACEMETHODIMP OCContextMenu::QueryContextMenu(HMENU hMenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
	HRESULT hr;

	if (!(CMF_DEFAULTONLY & uFlags))
	{
		InsertMenu(hMenu, indexMenu, MF_STRING | MF_BYPOSITION,	idCmdFirst + IDM_SHARE,	L"&Share with ownCloud");
	}
	hr = StringCbCopyW(m_pwszVerb, sizeof(m_pwszVerb), L"ownCloudShare");

	return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(IDM_SHARE + 1));
}