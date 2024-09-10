bool StickyNoteEditDialog::winEvent(MSG * msg, long * result)
{
	POINT p = {0};
	bool evtResult = QDialog::winEvent(msg, result);
	if (msg->message == WM_NCHITTEST)
	{
		GetCursorPos(&p);
		p.x -= pos().x();
		p.y -= pos().y();
		QWidget * widget = childAt(p.x, p.y);
		if (!widget)
		{
			// if we are not clicking over a child widget, fool windows into 
			// thinking we are clicking a caption bar (to allow it to move
			// as if we were)
			if (msg->hwnd == WindowFromDC(getDC()))
			{
				*result = HTCAPTION;
				return true;
			}
		}
	}
	return evtResult;
}