HWND uie::window::g_on_tab(HWND wnd_focus)
{
	HWND rv = 0;
	
	HWND wnd_temp = GetAncestor(wnd_focus, GA_ROOT);/*_GetParent(wnd_focus);
	
	while (wnd_temp && GetWindowLong(wnd_temp, GWL_EXSTYLE) & WS_EX_CONTROLPARENT)
	{
		if (GetWindowLong(wnd_temp, GWL_STYLE) & WS_POPUP) break;
		else wnd_temp = _GetParent(wnd_temp);
	}*/
	
	if (wnd_temp)
	{
		HWND wnd_next = GetNextDlgTabItem(wnd_temp, wnd_focus, (GetKeyState(VK_SHIFT) & KF_UP) ? TRUE :  FALSE);
		if (wnd_next && wnd_next != wnd_focus) 
		{
			unsigned flags = uSendMessage(wnd_next, WM_GETDLGCODE, 0, 0);
			if (flags & DLGC_HASSETSEL) uSendMessage(wnd_next, EM_SETSEL, 0, -1);
			SetFocus(wnd_next);
			
			rv = wnd_next;
		}
	}
	return rv;
};