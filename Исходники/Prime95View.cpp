void CPrime95View::position (
	int	vnum,
	int	iview,
	BOOL	forceTile)
{
	CMainFrame *mainframe;
	CRect	frame_rect;
	int	frame_width, frame_height;
	BOOL handled = FALSE;

	if (!forceTile)
	{
		handled = getSubWindowPlacement(GetParent(), iview);
	}
	if (!handled)
	{
		mainframe = (CMainFrame *) AfxGetApp()->m_pMainWnd;
		mainframe->GetClientRect (&frame_rect);
		frame_height = frame_rect.bottom - frame_rect.top;
		frame_width = frame_rect.right - frame_rect.left;

		mainframe->m_wndStatusBar.GetClientRect (&frame_rect);
		frame_height -= frame_rect.bottom - frame_rect.top;

		frame_height -= 2;
		frame_width -= 2;

		GetParent()->MoveWindow (0,
					 vnum * frame_height / NumViews,
					 frame_width,
					 (vnum+1) * frame_height / NumViews -
					  vnum * frame_height / NumViews);
	}
}