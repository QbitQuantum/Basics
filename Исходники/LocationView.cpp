/**
 * Show context menu and handle user selection.
 */
void CLocationView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if (point.x == -1 && point.y == -1)
	{
		//keystroke invocation
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);

		point = rect.TopLeft();
		point.Offset(5, 5);
	}

	CRect rc;
	CPoint pt = point;
	GetClientRect(rc);
	ScreenToClient(&pt);
	BCMenu menu;
	VERIFY(menu.LoadMenu(IDR_POPUP_LOCATIONBAR));
	theApp.TranslateMenu(menu.m_hMenu);

	BCMenu* pPopup = (BCMenu *) menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CCmdUI cmdUI;
	cmdUI.m_pMenu = pPopup;
	cmdUI.m_nIndexMax = cmdUI.m_pMenu->GetMenuItemCount();
	for (cmdUI.m_nIndex = 0 ; cmdUI.m_nIndex < cmdUI.m_nIndexMax ; ++cmdUI.m_nIndex)
	{
		cmdUI.m_nID = cmdUI.m_pMenu->GetMenuItemID(cmdUI.m_nIndex);
		switch (cmdUI.m_nID)
		{
		case ID_DISPLAY_MOVED_NONE:
			cmdUI.SetRadio(m_displayMovedBlocks == DISPLAY_MOVED_NONE);
			break;
		case ID_DISPLAY_MOVED_ALL:
			cmdUI.SetRadio(m_displayMovedBlocks == DISPLAY_MOVED_ALL);
			break;
		case ID_DISPLAY_MOVED_FOLLOW_DIFF:
			cmdUI.SetRadio(m_displayMovedBlocks == DISPLAY_MOVED_FOLLOW_DIFF);
			break;
		}
	}

	CString strItem;
	CString strNum;
	int nLine = -1;
	int bar = IsInsideBar(rc, pt);

	// If cursor over bar, format string with linenumber, else disable item
	if (bar != BAR_NONE)
	{
		// If outside bar area use left bar
		if (bar == BAR_YAREA)
			bar = BAR_LEFT;
		nLine = GetLineFromYPos(pt.y, bar);
		strNum.Format(_T("%d"), nLine + 1); // Show linenumber not lineindex
	}
	else
		pPopup->EnableMenuItem(ID_LOCBAR_GOTODIFF, MF_GRAYED);
	LangFormatString1(strItem, ID_LOCBAR_GOTOLINE_FMT, strNum);
	pPopup->SetMenuText(ID_LOCBAR_GOTODIFF, strItem, MF_BYCOMMAND);

	// invoke context menu
	// we don't want to use the main application handlers, so we use flags TPM_NONOTIFY | TPM_RETURNCMD
	// and handle the command after TrackPopupMenu
	int command = pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_NONOTIFY  | TPM_RETURNCMD, point.x, point.y, AfxGetMainWnd());

	CMergeDoc* pDoc = GetDocument();
	switch (command)
	{
	case ID_LOCBAR_GOTODIFF:
		m_view[MERGE_VIEW_LEFT]->GotoLine(nLine, true, bar);
	if (bar == BAR_LEFT || bar == BAR_RIGHT)
		m_view[bar]->SetFocus();
		break;
	case ID_EDIT_WMGOTO:
		m_view[MERGE_VIEW_LEFT]->WMGoto();
		break;
	case ID_DISPLAY_MOVED_NONE:
		SetConnectMovedBlocks(DISPLAY_MOVED_NONE);
		pDoc->SetDetectMovedBlocks(FALSE);
		break;
	case ID_DISPLAY_MOVED_ALL:
		SetConnectMovedBlocks(DISPLAY_MOVED_ALL);
		pDoc->SetDetectMovedBlocks(TRUE);
		break;
	case ID_DISPLAY_MOVED_FOLLOW_DIFF:
		SetConnectMovedBlocks(DISPLAY_MOVED_FOLLOW_DIFF);
		pDoc->SetDetectMovedBlocks(TRUE);
		break;
	}
}