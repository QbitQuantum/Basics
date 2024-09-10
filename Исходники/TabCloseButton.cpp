LRESULT TabCloseButton::WndProc(UINT msg, WPARAM wParam, LPARAM lParam) {
	RECT tmpRect;
	switch(msg) {
	case WM_MOUSEMOVE:
		if(state_)
			break;
		state_ = 1;
		TrackMouseEvent(TME_LEAVE);
		ImmediatelyUpdateWindow();
		return 0;
	case WM_MOUSELEAVE:
		state_ = 0;
		mousePressed_ = false;
		tmpRect = getClientRect();
		::MapWindowPoints(getWindowHandle(), getParent(), (POINT *) &tmpRect, 2);
		SafeWindowFromHandle(getParent())->UpdateWindow(&tmpRect);
		::UpdateWindow(getParent());
		ImmediatelyUpdateWindow();
		return 0;
	case WM_LBUTTONDOWN:
		state_ = 2;
		mousePressed_ = true;
		ImmediatelyUpdateWindow();
		return 0;
	case WM_LBUTTONUP:
		state_ = 1;
		ImmediatelyUpdateWindow();
		if(mousePressed_)
			onClick_(*this);
		return 0;
	}
	return Window::WndProc(msg, wParam, lParam);
}