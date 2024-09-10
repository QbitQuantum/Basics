/**
 * @brief Offer a context menu
 */
void CMergeDiffDetailView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// Create the menu and populate it with the available functions
	BCMenu menu;
	VERIFY(menu.LoadMenu(IDR_POPUP_MERGEDETAILVIEW));
	VERIFY(menu.LoadToolbar(IDR_MAINFRAME));
	theApp.TranslateMenu(menu.m_hMenu);

	BCMenu *pSub = (BCMenu *)menu.GetSubMenu(0);
	ASSERT(pSub != NULL);

	// Context menu opened using keyboard has no coordinates
	if (point.x == -1 && point.y == -1)
	{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);

		point = rect.TopLeft();
		point.Offset(5, 5);
	}

	pSub->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, AfxGetMainWnd());
}