LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode != HC_ACTION)
		return CallNextHookEx(g_Hook, nCode, wParam, lParam);
	INPUT inputDat[2];
	BOOL preventCallNextHookEx = FALSE;
	// Data about the mouse event
	const MSLLHOOKSTRUCT *p = reinterpret_cast<const MSLLHOOKSTRUCT*>(lParam);

	// An extended mouse button was pressed
	if (wParam == WM_XBUTTONDOWN) {
		// XButton1
		//WORD w = HIWORD(p->mouseData);
		if (HIWORD(p->mouseData) & XBUTTON1) {
#if defined(_DEBUG)
		std::cout << "XB1 down\n";
#endif
			preventCallNextHookEx = TRUE;
			// Save cursor pos at time of "scroll-click"
			g_origin = p->pt;
			bXB1 = TRUE;	// Remember that XButton1 is down
		}
		// XButton2
		else if (HIWORD(p->mouseData) & XBUTTON2) {
#if defined(_DEBUG)
			std::cout << "XB2 down\n";
#endif
			// Send a MiddleButton Up message
			inputDat[0].type = INPUT_MOUSE;
			inputDat[0].mi.dx = p->pt.x;
			inputDat[0].mi.dy = p->pt.y;
			inputDat[0].mi.mouseData = (DWORD)0x0;
			inputDat[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN; // middle button down
			inputDat[0].mi.time = (DWORD)0x0;
			inputDat[0].mi.dwExtraInfo = (ULONG_PTR)NULL;
			SendInput(1, inputDat, sizeof(INPUT));

			bXB2 = TRUE;	// Remember that XButton2 is down
			preventCallNextHookEx = TRUE;
		}
	}
	// An extended mouse button was released
	else if (wParam == WM_XBUTTONUP) {
		// XButton1
		if (HIWORD(p->mouseData) & XBUTTON1) {
#if defined(_DEBUG)
			std::cout << "XB1 up\n";
#endif
			preventCallNextHookEx = TRUE;
			bScrolling = FALSE;
			bXB1 = FALSE;	// Forget it. XButton1 is no longer down
		}
		// XButton2
		else if (HIWORD(p->mouseData) & XBUTTON2) {
#if defined(_DEBUG)
			std::cout << "XB2 up\n";
#endif
			// Send a MiddleButton Up message
			inputDat[0].type = INPUT_MOUSE;
			inputDat[0].mi.dx = p->pt.x;
			inputDat[0].mi.dy = p->pt.y;
			inputDat[0].mi.mouseData = (DWORD)0x0;
			inputDat[0].mi.dwFlags = MOUSEEVENTF_MIDDLEUP; // middle button up
			inputDat[0].mi.time = (DWORD)0x0;
			inputDat[0].mi.dwExtraInfo = (ULONG_PTR)NULL;
			SendInput(1, inputDat, sizeof(INPUT));

			bXB2 = FALSE;	// Forget it. XButton1 is no longer down
			preventCallNextHookEx = TRUE;
		}
	}
	else if (wParam == WM_MOUSEMOVE) {
		// Is XButton1 being held
		if (bXB1) {
			// If we haven't started scrolling...
			if (!bScrolling) {
#if defined(_DEBUG)
				std::cout << "First scroll\n";
#endif
				preventCallNextHookEx = TRUE;
				// Remember that we are now scrolling
				bScrolling = TRUE;
				g_ycount = 0;	// Reset our record of verticle movement
				SetCursorPos(g_origin.x, g_origin.y);
			}
			// If we are in the middle of scrolling...
			else {
#if defined(_DEBUG)
				std::cout << " Continuing scroll\n";
#endif
				preventCallNextHookEx = TRUE;
				// Keep track of how much we moved vertically
				g_ycount += p->pt.y - g_origin.y;
				// Reset the cursor to its original position
				SetCursorPos(g_origin.x, g_origin.y);
				// If we have moved more than the threshold...
				if (g_ycount < -Y_THRESHOLD || g_ycount > Y_THRESHOLD){
					DWORD mouseData = (g_ycount > 0 ? -WHEEL_DELTA : +WHEEL_DELTA); // scroll direction
					g_ycount = 0;

					// Send <WHEEL_FACTOR> number of scroll events
					INPUT input[WHEEL_FACTOR];
					for (size_t i = 0; i < WHEEL_FACTOR; ++i) {
						input[i].type = INPUT_MOUSE;
						// INFO: Should these be set to g_origin pos instead?
						input[i].mi.dx = p->pt.x;
						input[i].mi.dy = p->pt.y;
						input[i].mi.mouseData = mouseData;
						input[i].mi.dwFlags = MOUSEEVENTF_WHEEL; // wheel
						input[i].mi.time = (DWORD)0x0;
						input[i].mi.dwExtraInfo = (ULONG_PTR)NULL;
					}
#if defined(_DEBUG)
					std::cout << "Sending Scrollwheel event\n";
#endif
					SendInput(WHEEL_FACTOR, input, sizeof(INPUT));
				}
			}
		}
	}

	// Decide if we should let other programs detect the mouse events
	return (preventCallNextHookEx ? 1 : CallNextHookEx(g_Hook, nCode, wParam, lParam));
}