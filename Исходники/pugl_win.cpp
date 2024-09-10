static void
processMouseEvent(PuglView* view, int button, bool press, LPARAM lParam)
{
	view->event_timestamp_ms = GetMessageTime();
	if (press) {
		SetCapture(view->impl->hwnd);
	} else {
		ReleaseCapture();
	}

	if (view->mouseFunc) {
		view->mouseFunc(view, button, press,
		                GET_X_LPARAM(lParam),
		                GET_Y_LPARAM(lParam));
	}
}