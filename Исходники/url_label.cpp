	// handle mouse enter/leave
	void URLLabel::OnMouseMove(UINT nFlags, CPoint point)
	{
		if (!reg_mouseleave) {
			reg_mouseleave = true;

			// we want to receive the WM_MOUSELEAVE notification
			TRACKMOUSEEVENT		tm;

			tm.cbSize		= sizeof(tm);
			tm.dwFlags		= TME_LEAVE;
			tm.dwHoverTime	= 0;
			tm.hwndTrack	= *this;

			TrackMouseEvent(&tm);
		}

		if (!mouse_hover) {
			mouse_hover = true;

			// repaint our window
			CWnd		*parent = GetParent();
			if (parent) {
				CPoint		pt(0, 0);
				parent->ClientToScreen(&pt);

				CPoint		op(0, 0);
				ClientToScreen(&op);

				CRect		rc;
				GetClientRect(&rc);
				rc.OffsetRect(op.x - pt.x, op.y - pt.y);
				parent->InvalidateRect(&rc);
				Invalidate();
			}
		}
	}