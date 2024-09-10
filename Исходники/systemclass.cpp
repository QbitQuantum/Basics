LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
	case WM_CREATE:

		AllocConsole();
		FILE *acStreamOut;
		FILE *acStreamIn;
		freopen_s(&acStreamOut, "CONOUT$", "wt", stdout);
		freopen_s(&acStreamIn, "CONIN$", "r", stdin);
		// Check if a key has been pressed on the keyboard.
	case WM_KEYDOWN:

		// If a key is pressed send it to the input object so it can record that state.
		InputClass::GetInstance()->KeyDown((unsigned int)wparam);
		return 0;

		// Check if a key has been released on the keyboard.
	case WM_KEYUP:
		// If a key is released then send it to the input object so it can unset the state for that key.

		InputClass::GetInstance()->KeyUp((unsigned int)wparam);
		return 0;

		// Any other messages send to the default message handler as our application won't make use of them.
	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}