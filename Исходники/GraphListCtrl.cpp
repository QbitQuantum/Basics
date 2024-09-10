int CGraphListCtrl::GetScrollPos32(int nBar, BOOL bGetTrackPos /* = FALSE */)
{
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);

	if (bGetTrackPos)
	{
		if (GetScrollInfo(nBar, &si, SIF_TRACKPOS))
			return si.nTrackPos;
	}
	else
	{
		if (GetScrollInfo(nBar, &si, SIF_POS))
			return si.nPos;
	}

	return 0;
}