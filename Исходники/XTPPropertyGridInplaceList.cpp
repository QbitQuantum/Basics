void CXTPPropertyGridInplaceList::Create(CXTPPropertyGridItem* pItem, CRect rect)
{
	ASSERT(pItem && pItem->GetGrid());
	if (!pItem)
		return;

	CRect rcValue(rect);
	rcValue.left = pItem->GetGrid()->GetDividerPos() + 1;

	CWnd* pParent = (CWnd*)pItem->GetGrid();
	m_pItem = pItem;

	DestroyWindow();

	if (!m_hWnd)
	{
		CListBox::CreateEx(WS_EX_TOOLWINDOW | (pParent->GetExStyle() & WS_EX_LAYOUTRTL), _T("LISTBOX"), _T(""),
			LBS_NOTIFY | WS_CHILD | WS_VSCROLL | WS_BORDER | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS, CRect(0, 0, 0, 0), pParent, 0);
		SetOwner(pParent);


		if (m_bShowShadow && XTPSystemVersion()->IsWinXPOrGreater())
			SetClassLongPtr(m_hWnd, GCL_STYLE, GetClassLongPtr(m_hWnd, GCL_STYLE) | 0x00020000);
	}
	SetFont(pParent->GetFont());

	ResetContent();

	CXTPPropertyGridItemConstraints* pList = pItem->GetConstraints();


	int dx = rect.right - rcValue.left;

	CWindowDC dc(pParent);
	CXTPFontDC font(&dc, pParent->GetFont());
	int nHeight = dc.GetTextExtent(_T(" "), 1).cy + 3;

	for (int i = 0; i < pList->GetCount(); i++)
	{
		CXTPPropertyGridItemConstraint* pConstraint = pList->GetConstraintAt(i);

		CString str = pConstraint->m_strConstraint;
		int nIndex = AddString(str);
		SetItemDataPtr(nIndex, pConstraint);

		CSize sz = pItem->OnMergeItemConstraint(&dc, pConstraint);

		dx = max(dx, sz.cx);
		nHeight = max(nHeight, sz.cy);

		if (pItem->GetValue() == str)
			SetCurSel(nIndex);
	}

	SetItemHeight(0, nHeight);

	rect.top = rect.bottom;
	rect.bottom += nHeight * __min(pItem->GetDropDownItemCount(), GetCount()) + 2;
	rect.left = rect.right - __min(dx, rect.Width() - XTP_PGI_EXPAND_BORDER);

	pParent->ClientToScreen(&rect);

	CRect rcWork = XTPMultiMonitor()->GetWorkArea(rect);
	if (rect.bottom > rcWork.bottom && rect.top > rcWork.CenterPoint().y)
	{
		rect.OffsetRect(0, - rect.Height() - rcValue.Height() - 1);
	}
	if (rect.left < rcWork.left) rect.OffsetRect(rcWork.left - rect.left, 0);
	if (rect.right > rcWork.right) rect.OffsetRect(rcWork.right - rect.right, 0);


	SetFocus();


	SetWindowLongPtr(m_hWnd, GWLP_HWNDPARENT, 0);
	ModifyStyle(WS_CHILD, WS_POPUP);
	SetWindowLongPtr(m_hWnd, GWLP_HWNDPARENT, (LONG_PTR)pParent->m_hWnd);

	SetWindowPos(&CWnd::wndTopMost, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOOWNERZORDER);

	CXTPMouseMonitor::SetupHook(this);
}