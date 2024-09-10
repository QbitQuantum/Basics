BOOL COXShellNamespaceNavigator::InvokeDefaultCommand(const LPSHELLFOLDER lpParentFolder, 
													  const LPITEMIDLIST lpRelativeIDL) const
{
	// retrieve the default command ID
	HMENU hMenu=GetObjectContextMenu(lpParentFolder,lpRelativeIDL,CMF_DEFAULTONLY);
	if(hMenu==NULL)
	{
		TRACE(_T("COXShellNamespaceNavigator::InvokeDefaultCommand: GetObjectContextMenu() failed\n"));
		return FALSE;
	}

	CMenu menuPopup;
	VERIFY(menuPopup.Attach(hMenu));
	if(menuPopup.GetMenuItemCount()==0)
	{
		TRACE(_T("COXShellNamespaceNavigator::InvokeDefaultCommand: there is no context menu for the specified object\n"));
		return FALSE;
	}

	int nDefaultCmdID=-1;
#if _MFC_VER > 0x0421
	nDefaultCmdID=menuPopup.GetDefaultItem(GMDI_GOINTOPOPUPS,FALSE);
#else
	nDefaultCmdID=::GetMenuDefaultItem(menuPopup.GetSafeHmenu(),
		FALSE,GMDI_GOINTOPOPUPS);
#endif
	if(nDefaultCmdID==-1)
	{
		TRACE(_T("COXShellNamespaceNavigator::InvokeDefaultCommand: there is no default menu item for the specified object\n"));
		return FALSE;
	}
	VERIFY(menuPopup.DestroyMenu());

	return InvokeCommand(lpParentFolder,lpRelativeIDL,nDefaultCmdID,CMF_DEFAULTONLY);
}