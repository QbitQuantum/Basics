bool IsTopLevelWindow(HWND hWnd)
{
	WINDOWINFO wi = {0};

	assert(GetWindowInfo(hWnd, &wi));



	bool WS_VISIBLE_isSet = (wi.dwStyle & WS_VISIBLE) != 0;
	bool WS_EX_NOACTIVATE_isSet = (wi.dwExStyle & WS_EX_NOACTIVATE) != 0;
	bool WS_EX_TOOLWINDOW_isSet = (wi.dwExStyle & WS_EX_TOOLWINDOW) != 0;
	bool WS_EX_APPWINDOW_isSet = (wi.dwExStyle & WS_EX_APPWINDOW) != 0;
	bool WS_POPUP_isSet = (wi.dwStyle & WS_POPUP) != 0;
	bool WS_CHILD_isSet = (wi.dwStyle & WS_CHILD) != 0;


	if (!WS_VISIBLE_isSet
		|| ((WS_EX_NOACTIVATE_isSet || WS_EX_TOOLWINDOW_isSet) && !WS_EX_APPWINDOW_isSet)
		|| hWnd == 0
		|| WS_POPUP_isSet
		|| WS_CHILD_isSet
		)
	{
		return false;
	}
	else
	{
		return true;
	}

}