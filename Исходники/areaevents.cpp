static void areaMouseEvent(uiArea *a, int down, int  up, WPARAM wParam, LPARAM lParam)
{
	uiAreaMouseEvent me;
	int button;
	POINT clientpt;
	RECT client;
	BOOL inClient;
	double xpix, ypix;

	if (a->capturing) {
		clientpt.x = GET_X_LPARAM(lParam);
		clientpt.y = GET_Y_LPARAM(lParam);
		uiWindowsEnsureGetClientRect(a->hwnd, &client);
		inClient = PtInRect(&client, clientpt);
		if (inClient && !a->inside) {
			a->inside = TRUE;
			(*(a->ah->MouseCrossed))(a->ah, a, 0);
			uiprivClickCounterReset(&(a->cc));
		} else if (!inClient && a->inside) {
			a->inside = FALSE;
			(*(a->ah->MouseCrossed))(a->ah, a, 1);
			uiprivClickCounterReset(&(a->cc));
		}
	}

	xpix = (double) GET_X_LPARAM(lParam);
	ypix = (double) GET_Y_LPARAM(lParam);
	// these are in pixels; we need points
	pixelsToDIP(a, &xpix, &ypix);
	me.X = xpix;
	me.Y = ypix;
	if (a->scrolling) {
		me.X += a->hscrollpos;
		me.Y += a->vscrollpos;
	}

	loadAreaSize(a, NULL, &(me.AreaWidth), &(me.AreaHeight));

	me.Down = down;
	me.Up = up;
	me.Count = 0;
	if (me.Down != 0)
		// GetMessageTime() returns LONG and GetDoubleClckTime() returns UINT, which are int32 and uint32, respectively, but we don't need to worry about the signedness because for the same bit widths and two's complement arithmetic, s1-s2 == u1-u2 if bits(s1)==bits(s2) and bits(u1)==bits(u2) (and Windows requires two's complement: http://blogs.msdn.com/b/oldnewthing/archive/2005/05/27/422551.aspx)
		// signedness isn't much of an issue for these calls anyway because http://stackoverflow.com/questions/24022225/what-are-the-sign-extension-rules-for-calling-windows-api-functions-stdcall-t and that we're only using unsigned values (think back to how you (didn't) handle signedness in assembly language) AND because of the above AND because the statistics below (time interval and width/height) really don't make sense if negative
		// GetSystemMetrics() returns int, which is int32
		me.Count = uiprivClickCounterClick(&(a->cc), me.Down,
			me.X, me.Y,
			GetMessageTime(), GetDoubleClickTime(),
			GetSystemMetrics(SM_CXDOUBLECLK) / 2,
			GetSystemMetrics(SM_CYDOUBLECLK) / 2);

	// though wparam will contain control and shift state, let's just one function to get modifiers for both keyboard and mouse events; it'll work the same anyway since we have to do this for alt and windows key (super)
	me.Modifiers = getModifiers();

	button = me.Down;
	if (button == 0)
		button = me.Up;
	me.Held1To64 = 0;
	if (button != 1 && (wParam & MK_LBUTTON) != 0)
		me.Held1To64 |= 1 << 0;
	if (button != 2 && (wParam & MK_MBUTTON) != 0)
		me.Held1To64 |= 1 << 1;
	if (button != 3 && (wParam & MK_RBUTTON) != 0)
		me.Held1To64 |= 1 << 2;
	if (button != 4 && (wParam & MK_XBUTTON1) != 0)
		me.Held1To64 |= 1 << 3;
	if (button != 5 && (wParam & MK_XBUTTON2) != 0)
		me.Held1To64 |= 1 << 4;

	// on Windows, we have to capture on drag ourselves
	if (me.Down != 0)
		capture(a, TRUE);
	// only release capture when all buttons released
	if (me.Up != 0 && me.Held1To64 == 0)
		capture(a, FALSE);

	(*(a->ah->MouseEvent))(a->ah, a, &me);
}