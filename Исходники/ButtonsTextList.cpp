void CButtonsTextList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CListBox::OnLButtonDown(nFlags, point);

	int iIndex = GetCurSel ();
	if (iIndex == LB_ERR)
	{
		return;
	}

	//-------------------------------------------
	// Be sure that we realy click into the item!
	//-------------------------------------------
	CRect rect;
	GetItemRect (iIndex, &rect);

	if (!rect.PtInRect (point))
	{
		return;
	}

	//-----------------------------------------------------------
	// Trigger mouse up event (to change selection notification):
	//-----------------------------------------------------------
	SendMessage (WM_LBUTTONUP, nFlags, MAKELPARAM (point.x, point.y));

	//---------------------
	// Get selected button:
	//---------------------
	CBCGPToolbarButton* pButton = (CBCGPToolbarButton*) GetItemData (iIndex);
	ASSERT_VALID(pButton);

	//--------------------------------------
	// Prepare clipboard data and start drag:
	//--------------------------------------
	COleDataSource* pSrcItem = new COleDataSource();

	pButton->m_bDragFromCollection = TRUE;
	pButton->PrepareDrag (*pSrcItem);
	pButton->m_bDragFromCollection = FALSE;

	{
		CBCGPLocalResource locaRes;
		::SetCursor (AfxGetApp ()->LoadCursor (IDC_BCGBARRES_DELETE));
	}

	pSrcItem->DoDragDrop(DROPEFFECT_COPY|DROPEFFECT_MOVE, &rect, &CBCGPToolBar::m_DropSource);
	pSrcItem->InternalRelease();
}