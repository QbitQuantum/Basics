void CInputDocView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// make sure window is active
	GetParentFrame()->ActivateFrame();

	CMenu menu;
	if (menu.LoadMenu(IDR_InputDocPopup))
	{
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERTX(pPopup != NULL);

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			point.x, point.y,
			AfxGetMainWnd()); // use main window for cmds
	}
}