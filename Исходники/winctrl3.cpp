void CCheckListBox::InvalidateItem(int nIndex)
{
	CRect rect;
	GetItemRect(nIndex, rect);
	InvalidateRect(rect, FALSE);
}