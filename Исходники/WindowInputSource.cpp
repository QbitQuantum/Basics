void WindowInputSource::handleRawInput(WPARAM wParam, LPARAM lParam)
{
	// Only process input when the application is on the foreground.
	if (wParam != RIM_INPUT)
		return;

	RAWINPUT input;
	UINT szData = sizeof(input), szHeader = sizeof(RAWINPUTHEADER);
	HRAWINPUT handle = reinterpret_cast<HRAWINPUT>(lParam);

	UINT bytesWritten = 
		GetRawInputData(handle, RID_INPUT, &input, &szData, szHeader);

	ASSERT(bytesWritten <= szData, "Unexpected return value from GetRawInputData.");
	ASSERT(bytesWritten != UINT(-1), "GetRawInputData returned error.");

	switch (input.header.dwType)
	{
		case RIM_TYPEMOUSE:
			mouseInput(input.data.mouse);
			break;
		case RIM_TYPEKEYBOARD:
			keyboardInput(input.data.keyboard);
			break;
	}
}