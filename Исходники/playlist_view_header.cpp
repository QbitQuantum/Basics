void playlist_view::move_header(bool redraw, bool update)
{

	RECT rc_playlist, rc_header;
	GetClientRect(wnd_playlist, &rc_playlist);
	GetRelativeRect(wnd_header, wnd_playlist, &rc_header);
	int header_height = calculate_header_height();

	if (rc_header.left != 0 - horizontal_offset ||
		rc_header.top != 0 ||
		rc_header.right - rc_header.left != rc_playlist.right - rc_playlist.left + horizontal_offset ||
		rc_header.bottom - rc_header.top != header_height)
	{
		SendMessage(wnd_header, WM_SETREDRAW, FALSE, 0);
		if (rc_header.bottom - rc_header.top != header_height)
		{
			RECT playlist, redraw;
			get_playlist_rect(&playlist);
			ScrollWindowEx(wnd_playlist, 0, (header_height - rc_header.bottom), &playlist, &playlist, 0, &redraw, 0);
			//			RedrawWindow(wnd_playlist,&redraw,0,RDW_INVALIDATE|RDW_UPDATENOW);
		}
		SetWindowPos(wnd_header, 0, 0 - horizontal_offset, 0, rc_playlist.right - rc_playlist.left + horizontal_offset, header_height, SWP_NOZORDER);
		if (cfg_nohscroll && update) rebuild_header(false);
		SendMessage(wnd_header, WM_SETREDRAW, TRUE, 0);
		if (redraw) RedrawWindow(wnd_header, 0, 0, RDW_UPDATENOW | RDW_INVALIDATE);
	}

}