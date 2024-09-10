int CDlgIntersectionNodeBlock::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTResizeDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rtEmpty;
	rtEmpty.SetRectEmpty();
	if( m_lstNodeOption.GetSafeHwnd())
	{
		m_wndSortableHeaderCtrl.SubclassWindow(m_lstNodeOption.GetHeaderCtrl()->m_hWnd );
	}

	return 0;
}