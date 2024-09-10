LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;

	switch( pKeyBoard->vkCode )
	{
	case VK_CAPITAL:
		{
			switch (wParam)
			{
			case WM_KEYDOWN:
				keybd_event(VK_BACK, 0x8e, 0, 0);
				return 1;
			case WM_KEYUP:
				keybd_event(VK_BACK, 0x8e, KEYEVENTF_KEYUP, 0);
				return 1;
			}
		}
		
		default:
			return CallNextHookEx( NULL, nCode, wParam, lParam );
	}

	return 0;
}