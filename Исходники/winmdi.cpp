HMENU CMDIFrameWnd::GetWindowMenuPopup(HMENU hMenuBar)
	// find which popup is the "Window" menu
{
	if (hMenuBar == NULL)
		return NULL;

	ASSERT(::IsMenu(hMenuBar));

	int iItem = ::GetMenuItemCount(hMenuBar);
	while (iItem--)
	{
		HMENU hMenuPop = ::GetSubMenu(hMenuBar, iItem);
		if (hMenuPop != NULL)
		{
			int iItemMax = ::GetMenuItemCount(hMenuPop);
			for (int iItemPop = 0; iItemPop < iItemMax; iItemPop++)
			{
				UINT nID = GetMenuItemID(hMenuPop, iItemPop);
				if (nID >= AFX_IDM_WINDOW_FIRST && nID <= AFX_IDM_WINDOW_LAST)
					return hMenuPop;
			}
		}
	}

	// no default menu found
	TRACE(traceAppMsg, 0, "Warning: GetWindowMenuPopup failed!\n");
	return NULL;
}