static void
investigate(HWND hwnd)
{
	LONG_PTR exstyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
	LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
	TCHAR buf[80];

	GetWindowText(hwnd, buf, NUMBER_OF(buf));
	DEBUG_PRINTF(( T("inv: %p <- %p (%p) '%s'"),
	               hwnd, GetParent(hwnd), GetLastActivePopup(hwnd), buf ));

	buf[0] = T('\0');
	_tcscat(buf, (exstyle&WS_EX_ACCEPTFILES ? T("Af") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_APPWINDOW ? T("Aw") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_CLIENTEDGE ? T("Ce") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_COMPOSITED ? T("Cm") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_CONTEXTHELP ? T("Ch") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_CONTROLPARENT ? T("Cp") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_DLGMODALFRAME ? T("Dm") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_LAYERED ? T("Ly") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_LAYOUTRTL ? T("Lr") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_LEFT ? T("Le") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_LEFTSCROLLBAR ? T("Ls") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_LTRREADING ? T("Lr") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_MDICHILD ? T("Md") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_NOACTIVATE ? T("Na") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_NOINHERITLAYOUT ? T("Ni"):T(".,")));
	_tcscat(buf, (exstyle&WS_EX_NOPARENTNOTIFY ? T("Np") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_OVERLAPPEDWINDOW ? T("Ol"):T(".,")));
	_tcscat(buf, (exstyle&WS_EX_PALETTEWINDOW ? T("Pw") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_RIGHT ? T("Ri") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_RIGHTSCROLLBAR ? T("Rs") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_RTLREADING ? T("Rr") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_STATICEDGE ? T("Se") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_TOOLWINDOW ? T("Tw") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_TOPMOST ? T("Tm") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_TRANSPARENT ? T("Tp") : T(".,")));
	_tcscat(buf, (exstyle&WS_EX_WINDOWEDGE ? T("We") : T(".,")));
	DEBUG_PRINTF((T("inv: ex '%s'"), buf));

	buf[0] = T('\0');
	_tcscat(buf, (style&WS_BORDER ? T("Br") : T(".,")));
	_tcscat(buf, (style&WS_CAPTION ? T("Cp") : T(".,")));
	_tcscat(buf, (style&WS_CHILD ? T("Ch") : T(".,")));
	_tcscat(buf, (style&WS_CHILDWINDOW ? T("Cw") : T(".,")));
	_tcscat(buf, (style&WS_CLIPCHILDREN ? T("Cc") : T(".,")));
	_tcscat(buf, (style&WS_CLIPSIBLINGS ? T("Cs") : T(".,")));
	_tcscat(buf, (style&WS_DISABLED ? T("Di") : T(".,")));
	_tcscat(buf, (style&WS_DLGFRAME ? T("Df") : T(".,")));
	_tcscat(buf, (style&WS_GROUP ? T("Gr") : T(".,")));
	_tcscat(buf, (style&WS_HSCROLL ? T("Hs") : T(".,")));
	_tcscat(buf, (style&WS_ICONIC ? T("Ic") : T(".,")));
	_tcscat(buf, (style&WS_MAXIMIZE ? T("Mx") : T(".,")));
	_tcscat(buf, (style&WS_MAXIMIZEBOX ? T("Mb") : T(".,")));
	_tcscat(buf, (style&WS_MINIMIZE ? T("Mn") : T(".,")));
	_tcscat(buf, (style&WS_MINIMIZEBOX ? T("Mb") : T(".,")));
	_tcscat(buf, (style&WS_OVERLAPPED ? T("Ol") : T(".,")));
	_tcscat(buf, (style&WS_OVERLAPPEDWINDOW ? T("Ow") : T(".,")));
	_tcscat(buf, (style&WS_POPUP ? T("Po") : T(".,")));
	_tcscat(buf, (style&WS_POPUPWINDOW ? T("Pw") : T(".,")));
	_tcscat(buf, (style&WS_SIZEBOX ? T("Sb") : T(".,")));
	_tcscat(buf, (style&WS_SYSMENU ? T("Sm") : T(".,")));
	_tcscat(buf, (style&WS_TABSTOP ? T("Ts") : T(".,")));
	_tcscat(buf, (style&WS_THICKFRAME ? T("Tf") : T(".,")));
	_tcscat(buf, (style&WS_TILED ? T("Ti") : T(".,")));
	_tcscat(buf, (style&WS_TILEDWINDOW ? T("Tw") : T(".,")));
	_tcscat(buf, (style&WS_VISIBLE ? T("Vi") : T(".,")));
	_tcscat(buf, (style&WS_VSCROLL ? T("Vs") : T(".,")));
	_tcscat(buf, (style&WS_ACTIVECAPTION ? T("Ac") : T(".,")));
	DEBUG_PRINTF((T("inv: st '%s'"), buf));
}