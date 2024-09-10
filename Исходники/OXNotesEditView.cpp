void COXNotesEditView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CRect rct;
	GetNotesRect(&rct);

	if (rct.PtInRect(point))
	{
		int n=HIWORD(GetEditCtrl().CharFromPos(point));
		int nChar=GetEditCtrl().LineIndex(n);
		if (IsMarked(nChar))
			RemoveBookmarks(nChar,nChar);
		else
			SetBookmark(nChar);
	}
	CEditView::OnLButtonDblClk(nFlags, point);
}