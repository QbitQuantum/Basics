void C4GamePadControl::CheckGamePad(const SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_JOYDEVICEADDED:
		// Report that an unsupported joystick device has been detected, to help with controller issues.
		if (!SDL_IsGameController(e.jdevice.which))
			LogF("Gamepad %s isn't supported.", SDL_JoystickNameForIndex(e.jdevice.which));
		break;
	case SDL_CONTROLLERDEVICEADDED:
	{
		auto device = std::make_shared<C4GamePadOpener>(e.cdevice.which);
		Gamepads[device->GetID()] = device;
		LogF("Gamepad #%d connected: %s", device->GetID(), SDL_JoystickNameForIndex(e.cdevice.which));
		break;
	}
	case SDL_CONTROLLERDEVICEREMOVED:
		LogF("Gamepad #%d disconnected.", e.cdevice.which);
		Gamepads.erase(e.cdevice.which);
		break;
	}
}