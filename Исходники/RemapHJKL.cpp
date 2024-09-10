LRESULT CALLBACK KeyboardHook(int code, WPARAM wParam, LPARAM lParam)
{
	if (code != HC_ACTION) return CallNextHookEx(NULL, code, wParam, lParam);

	if (!myState) return CallNextHookEx(NULL, code, wParam, lParam);

	switch (wParam)
	{
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:	{
							PKBDLLHOOKSTRUCT hks = (PKBDLLHOOKSTRUCT)lParam;
							// SendInput
							switch (hks->vkCode) {
							case 'F':
							case 'B':
							case '4':
							case '6':
							case '0':
							case 'H':
							case 'J':
							case 'K':
							case 'L':{
										 //DWORD extended = (0x1000000 & lParam) >> 24; // Check if KEYEVENTF_EXTENDEDKEY
										 BYTE scanCode = (0xFF0000 & lParam) >> 16;

										 // Check if KEYEVENTF_KEYUP, otherwise will be set to down
										 LPARAM dwFlags = (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) ? KEYEVENTF_KEYUP : 0;
										 dwFlags |= KEYEVENTF_EXTENDEDKEY;
										 dwFlags |= KEYEVENTF_SCANCODE;

										 INPUT ip;
										 ZeroMemory(&ip, sizeof(ip));
										 ip.type = INPUT_KEYBOARD;
										 switch (hks->vkCode) {
										 case 'H':
											 ip.ki.wVk = VK_LEFT; 
											 break;
										 case 'J':
											 ip.ki.wVk = VK_DOWN;
											 break;
										 case 'K':
											 ip.ki.wVk = VK_UP;
											 break;
										 case 'L':
											 ip.ki.wVk = VK_RIGHT;
											 break;
										 case '4':
											 ip.ki.wVk = VK_END;
											 break;
										 case '6':
										 case '0':
											 ip.ki.wVk = VK_HOME;
											 break;
										 case 'F':
											 ip.ki.wVk = VK_NEXT;
											 break;
										 case 'B':
											 ip.ki.wVk = VK_PRIOR;
											 break;
										 }
										 ip.ki.wScan = MapVirtualKey(ip.ki.wVk, MAPVK_VK_TO_VSC);
										 ip.ki.dwFlags = dwFlags;
										 ip.ki.time = 0;
										 ip.ki.dwExtraInfo = 0;
										 SendInput(1, &ip, sizeof(ip));
										 return 1;						}
							}
							break;
	}
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}