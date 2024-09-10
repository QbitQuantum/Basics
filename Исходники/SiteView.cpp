void CSiteView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndSiteView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// Select clicked item:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}
	HTREEITEM item = pWndTree->GetSelectedItem();
	TREE_T * item_data = (TREE_T*)pWndTree->GetItemData(item);
	pWndTree->SetFocus();

	if (item_data == NULL)
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_ROOT, point.x, point.y, this, TRUE);
	else if (item_data->tree_level == TREE_LEVEL_SITE)
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_SITES, point.x, point.y, this, TRUE);
	else if (item_data->tree_level == TREE_LEVEL_RECORDER)
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_RECORDER, point.x, point.y, this, TRUE);
	else if (item_data->tree_level==TREE_LEVEL_CAMERA)
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_CAMERA, point.x, point.y, this, TRUE);

}