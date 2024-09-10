void ipod_browse_photo_dialog::on_size (HWND wnd, unsigned width, unsigned height)
{
	HWND wnd_close = GetDlgItem(wnd, IDCANCEL);
	HWND wnd_next = GetDlgItem(wnd, IDC_NEXT);
	HWND wnd_last = GetDlgItem(wnd, IDC_LAST);
	HWND wnd_prev = GetDlgItem(wnd, IDC_PREVIOUS);
	HWND wnd_nextf = GetDlgItem(wnd, IDC_NEXT_FORMAT);
	HWND wnd_prevf = GetDlgItem(wnd, IDC_PREVIOUS_FORMAT);
	HDWP dwp = BeginDeferWindowPos(6);
	RECT rc_close, rc_next, rc_next_format, rc_prev, rc_prev_format, rc_last;
	GetWindowRect(wnd_close, &rc_close);
	GetRelativeRect(wnd_next, wnd, &rc_next);
	GetRelativeRect(wnd_last, wnd, &rc_last);
	GetRelativeRect(wnd_nextf, wnd, &rc_next_format);
	GetRelativeRect(wnd_prev, wnd, &rc_prev);
	GetRelativeRect(wnd_prevf, wnd, &rc_prev_format);
	unsigned cy_close = rc_close.bottom - rc_close.top;
	unsigned cx_close = rc_close.right - rc_close.left;
	dwp = DeferWindowPos(dwp, m_viewer.get_wnd(), NULL, 0, 0, width, height-cy_close-2, SWP_NOZORDER);
	dwp = DeferWindowPos(dwp, wnd_close, NULL, width-cx_close, height-cy_close, cx_close, cy_close, SWP_NOZORDER|SWP_NOSIZE);
	int cx = width-cx_close-2-rc_next.right+rc_next.left;
	dwp = DeferWindowPos(dwp, wnd_last, NULL, cx, height-cy_close, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
	dwp = DeferWindowPos(dwp, wnd_next, NULL, cx -= (rc_last.right-rc_last.left +2), height-cy_close, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
	dwp = DeferWindowPos(dwp, wnd_prev, NULL, cx -= (rc_prev.right-rc_prev.left +2), height-cy_close, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
	dwp = DeferWindowPos(dwp, wnd_nextf, NULL, cx -= (rc_next_format.right-rc_next_format.left + 2), height-cy_close,0, 0, SWP_NOZORDER|SWP_NOSIZE);
	dwp = DeferWindowPos(dwp, wnd_prevf, NULL, cx -= (rc_prev_format.right-rc_prev_format.left + 2), height-cy_close, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
	EndDeferWindowPos(dwp);
}