bool initializeKeyhook() {
	std::thread([=](){
		if (g_hook != nullptr) {
			if (g_keyboardHookedCallback)
				g_keyboardHookedCallback(false);
			return;
		}

		g_hook = SetWindowsHookExA(WH_KEYBOARD_LL, lowLevelKeyboardProc, GetModuleHandle(0), 0);

		if (g_keyboardHookedCallback)
			g_keyboardHookedCallback(g_hook != nullptr);

		MSG msg;
		while (GetMessageA(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}).detach();

	return true;
}