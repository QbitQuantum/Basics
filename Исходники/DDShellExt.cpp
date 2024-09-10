STDMETHODIMP CDDShellExt::QueryContextMenu(HMENU hmenu,UINT uMenuIndex,UINT uidFirstCmd,UINT uidLastCmd,UINT uFlags)
{
	(void)uidLastCmd;
	if(!m_ac.isConnected())
	{
		if(!m_ac.connectToServer())
			return E_FAIL;
	}
	if (uFlags&CMF_DEFAULTONLY)
		return MAKE_HRESULT(SEVERITY_SUCCESS,FACILITY_NULL,0);

	int x=uidFirstCmd;

	InsertMenu(hmenu,uMenuIndex++,MF_STRING|MF_BYPOSITION,x++,_T("Copy") _T(" - ") _T(CATCHCOPY_EXPLORER_PLUGIN_SOFTWARE_NAME));
	InsertMenu(hmenu,uMenuIndex++,MF_STRING|MF_BYPOSITION,x++,_T("Move") _T(" - ") _T(CATCHCOPY_EXPLORER_PLUGIN_SOFTWARE_NAME));

	int defItem=GetMenuDefaultItem(hmenu,false,0);
	if (defItem==1) // 1: Copy
	{
		if (fFromExplorer)
			SetMenuDefaultItem(hmenu,uidFirstCmd,false);
	}
	else if (defItem==2) //2: Move
	{
		SetMenuDefaultItem(hmenu,uidFirstCmd+1,false);
	}
	return MAKE_HRESULT(SEVERITY_SUCCESS,FACILITY_NULL,2);
}