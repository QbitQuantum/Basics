int Input::DetectDevices(ControllerType types[])
{
	int numControllers = 1;
	types[0] = KEYBOARD_AND_MOUSE;

	// detect XInput gamepads
	for(DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_CAPABILITIES capabilities;
		ZeroMemory(&capabilities, sizeof capabilities);

		DWORD result = XInputGetCapabilities(i, 0, &capabilities);
		if(result != ERROR_SUCCESS) continue;

		types[numControllers++] = GAMEPAD_XINPUT;
	}

	return numControllers;
}