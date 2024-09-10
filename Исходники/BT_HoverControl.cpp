void HoverControl::onMouseMove(long x, long y)
{
	if (!_isTracking)
	{
		// TrackMouseEvents disable after one message is received, so we need to
		// re-enable them.
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.dwHoverTime = HOVER_DEFAULT;
		tme.hwndTrack = _hwnd;
		TrackMouseEvent(&tme);
		_isTracking = true;
	}

	if (_mouseLeft)
	{
		// MOUSE OVER ACTION
		if (!_isDisabled && _hoverStateBitmap)
			SendMessage(_hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) _hoverStateBitmap);
		_mouseLeft = false;
	}

	if (!_isDisabled)
		SetCursor(LoadCursor(NULL, IDC_HAND));
}