LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	#ifndef WM_MOUSEWHEEL
	#define WM_MOUSEWHEEL 0x020A
	#endif
	#ifndef WHEEL_DELTA
	#define WHEEL_DELTA 120
	#endif

	irr::CIrrDeviceWin32* dev = 0;
	irr::SEvent event;

	static irr::s32 ClickCount=0;
	if (GetCapture() != hWnd && ClickCount > 0)
		ClickCount = 0;


	struct messageMap
	{
		irr::s32 group;
		UINT winMessage;
		irr::s32 irrMessage;
	};

	static messageMap mouseMap[] =
	{
		{0, WM_LBUTTONDOWN, irr::EMIE_LMOUSE_PRESSED_DOWN},
		{1, WM_LBUTTONUP,   irr::EMIE_LMOUSE_LEFT_UP},
		{0, WM_RBUTTONDOWN, irr::EMIE_RMOUSE_PRESSED_DOWN},
		{1, WM_RBUTTONUP,   irr::EMIE_RMOUSE_LEFT_UP},
		{0, WM_MBUTTONDOWN, irr::EMIE_MMOUSE_PRESSED_DOWN},
		{1, WM_MBUTTONUP,   irr::EMIE_MMOUSE_LEFT_UP},
		{2, WM_MOUSEMOVE,   irr::EMIE_MOUSE_MOVED},
		{3, WM_MOUSEWHEEL,  irr::EMIE_MOUSE_WHEEL},
		{-1, 0, 0}
	};

	// handle grouped events
	messageMap * m = mouseMap;
	while ( m->group >=0 && m->winMessage != message )
		m += 1;

	if ( m->group >= 0 )
	{
		if ( m->group == 0 )	// down
		{
			ClickCount++;
			SetCapture(hWnd);
		}
		else
		if ( m->group == 1 )	// up
		{
			ClickCount--;
			if (ClickCount<1)
			{
				ClickCount=0;
				ReleaseCapture();
			}
		}

		event.EventType = irr::EET_MOUSE_INPUT_EVENT;
		event.MouseInput.Event = (irr::EMOUSE_INPUT_EVENT) m->irrMessage;
		event.MouseInput.X = (short)LOWORD(lParam);
		event.MouseInput.Y = (short)HIWORD(lParam);
		event.MouseInput.Shift = ((LOWORD(wParam) & MK_SHIFT) != 0);
		event.MouseInput.Control = ((LOWORD(wParam) & MK_CONTROL) != 0);
		// left and right mouse buttons
		event.MouseInput.ButtonStates = wParam & ( MK_LBUTTON | MK_RBUTTON);
		// middle and extra buttons
		if (wParam & MK_MBUTTON)
			event.MouseInput.ButtonStates |= irr::EMBSM_MIDDLE;
#if(_WIN32_WINNT >= 0x0500)
		if (wParam & MK_XBUTTON1)
			event.MouseInput.ButtonStates |= irr::EMBSM_EXTRA1;
		if (wParam & MK_XBUTTON2)
			event.MouseInput.ButtonStates |= irr::EMBSM_EXTRA2;
#endif
		event.MouseInput.Wheel = 0.f;

		// wheel
		if ( m->group == 3 )
		{
			POINT p; // fixed by jox
			p.x = 0; p.y = 0;
			ClientToScreen(hWnd, &p);
			event.MouseInput.X -= p.x;
			event.MouseInput.Y -= p.y;
			event.MouseInput.Wheel = ((irr::f32)((short)HIWORD(wParam))) / (irr::f32)WHEEL_DELTA;
		}

		dev = getDeviceFromHWnd(hWnd);
		if (dev)
		{
			dev->postEventFromUser(event);

			if ( event.MouseInput.Event >= irr::EMIE_LMOUSE_PRESSED_DOWN && event.MouseInput.Event <= irr::EMIE_MMOUSE_PRESSED_DOWN )
			{
				irr::u32 clicks = dev->checkSuccessiveClicks(event.MouseInput.X, event.MouseInput.Y, event.MouseInput.Event);
				if ( clicks == 2 )
				{
					event.MouseInput.Event = (irr::EMOUSE_INPUT_EVENT)(irr::EMIE_LMOUSE_DOUBLE_CLICK + event.MouseInput.Event-irr::EMIE_LMOUSE_PRESSED_DOWN);
					dev->postEventFromUser(event);
				}
				else if ( clicks == 3 )
				{
					event.MouseInput.Event = (irr::EMOUSE_INPUT_EVENT)(irr::EMIE_LMOUSE_TRIPLE_CLICK + event.MouseInput.Event-irr::EMIE_LMOUSE_PRESSED_DOWN);
					dev->postEventFromUser(event);
				}
			}
		}
		return 0;
	}

	switch (message)
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		return 0;

	case WM_ERASEBKGND:
		return 0;

	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
		{
			BYTE allKeys[256];

			event.EventType = irr::EET_KEY_INPUT_EVENT;
			event.KeyInput.Key = (irr::EKEY_CODE)wParam;
			event.KeyInput.PressedDown = (message==WM_KEYDOWN || message == WM_SYSKEYDOWN);

			const UINT MY_MAPVK_VSC_TO_VK_EX = 3; // MAPVK_VSC_TO_VK_EX should be in SDK according to MSDN, but isn't in mine.
			if ( event.KeyInput.Key == irr::KEY_SHIFT )
			{
				// this will fail on systems before windows NT/2000/XP, not sure _what_ will return there instead.
				event.KeyInput.Key = (irr::EKEY_CODE)MapVirtualKey( ((lParam>>16) & 255), MY_MAPVK_VSC_TO_VK_EX );
			}
			if ( event.KeyInput.Key == irr::KEY_CONTROL )
			{
				event.KeyInput.Key = (irr::EKEY_CODE)MapVirtualKey( ((lParam>>16) & 255), MY_MAPVK_VSC_TO_VK_EX );
				// some keyboards will just return LEFT for both - left and right keys. So also check extend bit.
				if (lParam & 0x1000000)
					event.KeyInput.Key = irr::KEY_RCONTROL;
			}
			if ( event.KeyInput.Key == irr::KEY_MENU )
			{
				event.KeyInput.Key = (irr::EKEY_CODE)MapVirtualKey( ((lParam>>16) & 255), MY_MAPVK_VSC_TO_VK_EX );
				if (lParam & 0x1000000)
					event.KeyInput.Key = irr::KEY_RMENU;
			}