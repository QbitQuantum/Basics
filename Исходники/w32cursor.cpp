void MCScreenDC::setcursor(Window p_window, MCCursorRef p_cursor)
{
	if (p_cursor == nil || p_cursor -> kind == kMCCursorNone)
		SetCursor(NULL);
	else if (p_cursor -> kind == kMCCursorStandard)
		SetCursor(LoadCursorA(nil, p_cursor -> standard));
	else
		SetCursor(p_cursor -> custom);
}