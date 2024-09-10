// InvalidateRange is an overrideable function that is used to invalidate the view
// between two caret positions.  This is used to invalidate bits of the window
// when the selection is changed (using mouse selection or with SetSel()).
// The default behaviour invalidates the lines (whole width of document) from
// the top of start to the bottom of end (using the current character height).
void CScrView::InvalidateRange(CPointAp start, CPointAp end, bool f /*=false*/)
{
	if (start.y > scrollpos_.y + win_height_ || start.x > scrollpos_.x + win_width_ ||
		end.y < scrollpos_.y || end.x < scrollpos_.x)
	{
		// All outside display area so do nothing.  Note that this may appear to not be nec.
		// as Windows does this too but due to overflow problems is safer to do it here.
		return;
	}

	CSizeAp ss = caret_size();

	// Also invalidate a row above and up to 3 rows below (this is necessary for stacked mode)
	start.y -= ss.cy;
	end.y += 3*ss.cy;

	if (start.x < scrollpos_.x) start.x = scrollpos_.x;
	if (start.y < scrollpos_.y) start.y = scrollpos_.y;
	if (end.y > scrollpos_.y + win_height_)
		end.y = scrollpos_.y + win_height_;

	// Invalidate the full width of display from top of start to bottom of end
	CRectAp rr(0, start.y, total_.cx, end.y);

	// Convert to device coords
	CRect norm_rect = ConvertToDP(rr);

	CRect cli;
	GetDisplayRect(&cli);

	// Invalidate the previous selection so that it is drawn unselected
	CRect rct;
	if (rct.IntersectRect(&cli, &norm_rect))
		DoInvalidateRect(&norm_rect);
}