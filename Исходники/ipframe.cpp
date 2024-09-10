// </snippet1>
LRESULT CInPlaceFrame::OnResizeChild(WPARAM /*wParam*/, LPARAM lParam)
{
	// notify the container that the rectangle has changed!
	CWordPadDoc* pDoc = (CWordPadDoc*)GetActiveDocument();
	if (pDoc == NULL)
		return 0;

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CWordPadDoc)));

	// get new rect and parent
	CRect rectNew;
	rectNew.CopyRect((LPCRECT)lParam);
	CWnd* pParentWnd = GetParent();
	ASSERT_VALID(pParentWnd);

	// convert rectNew relative to pParentWnd
	ClientToScreen(&rectNew);
	pParentWnd->ScreenToClient(&rectNew);

	if (m_wndRulerBar.GetStyle()&WS_VISIBLE)
	{
		CRect rect;
		m_wndRulerBar.GetWindowRect(&rect);
		rectNew.top += rect.Height();
	}
	rectNew.left += HORZ_TEXTOFFSET;
	rectNew.top += VERT_TEXTOFFSET;

	// adjust the new rectangle for the current control bars
	CWnd* pLeftOver = GetDlgItem(AFX_IDW_PANE_FIRST);
	ASSERT(pLeftOver != NULL);
	CRect rectCur = m_rectPos;
	pLeftOver->CalcWindowRect(&rectCur, CWnd::adjustOutside);
	rectNew.left += m_rectPos.left - rectCur.left;
	rectNew.top += m_rectPos.top - rectCur.top;
	rectNew.right -= rectCur.right - m_rectPos.right;
	rectNew.bottom -= rectCur.bottom - m_rectPos.bottom;
	OnRequestPositionChange(rectNew);

	return 0;
}