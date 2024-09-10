void CTestTaskView::OnMouseMove(UINT flags, CPoint point)
{
	if (GetCapture() == this)
	{
		CPoint tmp = GetDeviceScrollPosition();
		CPoint buff = _end - tmp;
		_end = point;

		CRect rect;
		GetWindowRect(&rect);

		CPoint vec = CPoint(0, 0);
		if ((_end.x > (rect.right - rect.left) || _end.x < 0) || (_end.y >(rect.bottom - rect.top) || _end.y < 0))
		{
			CPoint the_line = _end - _previous;
			if (_end.x > (rect.right - rect.left) || _end.x < 0)
			{
				if (the_line.y < 0)
					vec = CPoint(0, -1);
				else
					vec = CPoint(0, 1);
			}
			else if (_end.y > (rect.bottom - rect.top) || _end.y < 0)
			{
				if (the_line.x > 0)
					vec = CPoint(1, 0);
				else
					vec = CPoint(-1, 0);
			}

			double alpha = acos((double)(walter::scalar_multiplication(the_line, vec) /
				(walter::length(the_line) * walter::length(vec))));

			CPoint shift_scroll = walter::const_multiplication(the_line, cos(alpha));

			if (shift_scroll != CPoint(0, 0))
			{
				walter::normalize(shift_scroll);
				ScrollToPosition(GetScrollPosition() + shift_scroll);
			}
		}
		
		_end += tmp;
		Invalidate();
	}
}