void ServerOpts2::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int OldScrollPos = GetScrollPos(SB_VERT);
	CScrollBar* pLScrollBar = GetScrollBarCtrl(SB_VERT);

	int Min, Max;
	GetScrollRange(SB_VERT, &Min, &Max);
	RECT WindowRect;
	GetClientRect(&WindowRect);
	long WindowHeight = WindowRect.bottom - WindowRect.top;
	long PageSize = WindowHeight;
	long LineSize = PageSize/10;

	switch (nSBCode)
	{
	case SB_TOP : //   Scroll to top. 
		{
			SetScrollPos(SB_VERT, Min, TRUE);
			ScrollWindow(0, Min - OldScrollPos);
		}break;
	case SB_BOTTOM :  //Scroll to bottom.
		{
			SetScrollPos(SB_VERT, Max, TRUE);
			ScrollWindow(0, Max - OldScrollPos);
		}break;
	case SB_LINEDOWN : //  Scroll one line down.
		{
			if (OldScrollPos < Max)
			{
				SetScrollPos(SB_VERT, OldScrollPos+LineSize, TRUE);
				ScrollWindow(0, -LineSize);
			};
		};break;
	case SB_LINEUP : // Scroll one line up.
		{
			if (OldScrollPos > Min)
			{
                SetScrollPos(SB_VERT, OldScrollPos-LineSize, TRUE);
				ScrollWindow(0, LineSize);
			}
		}break;
	case SB_PAGEDOWN : //  Scroll one page down.
		{
			int NewPos = OldScrollPos + PageSize;
			if (NewPos > Max) NewPos = Max;
			SetScrollPos(SB_VERT, NewPos, TRUE);
			ScrollWindow(0, OldScrollPos - NewPos);
		}break;
	case SB_PAGEUP : //  Scroll one page up.
		{
			int NewPos = OldScrollPos - PageSize;
			if (NewPos < Min) NewPos = Min;
			SetScrollPos(SB_VERT, NewPos, TRUE);
			ScrollWindow(0, OldScrollPos - NewPos);
		}break;
	case SB_THUMBPOSITION : //  Scroll to the absolute position. The current position is provided in nPos.
//		{
//		}break;
	case SB_THUMBTRACK : //  Drag scroll box to specified position. The current position is provided in nPos.
		{
			ScrollWindow(0, OldScrollPos - nPos);
			SetScrollPos(SB_VERT, nPos, TRUE);
		}break;	
	case SB_ENDSCROLL ://  End scroll.
		{
		}break;
	};
	
	CSubDlg::OnVScroll(nSBCode, nPos, pScrollBar);
}