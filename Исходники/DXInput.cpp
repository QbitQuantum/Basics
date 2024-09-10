void DXInput::Initialize(HWND hWindow)
{
	// Check if we have already initialized the system
	if (mInitialized)
	{
		// Write to log
		Log::Get()->Write(LogType::Warning, "[Input] System already initialized.");
		return;
	}

	// Write to log
	Log::Get()->Write(LogType::Message, "[Input] Initializing...");

	// Obtain an interface to DirectInput
	if (FAILED(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mpDI, nullptr)))
	{
		// Write to log
		Log::Get()->Write(LogType::Error, "[Input] Failed to create DirectInput object.");
		return;
	}

	//----------------------------------------------------------------------------------------------------
	// Create keyboard device
	if (FAILED(mpDI->CreateDevice(GUID_SysKeyboard, &mpKeyboard, nullptr)))
	{
		// Write to log
		Log::Get()->Write(LogType::Error, "[Input] Failed to create keyboard device.");
		return;
	}

	// Set the keyboard data format
	if (FAILED(mpKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		// Write to log
		Log::Get()->Write(LogType::Error, "[Input] Failed to set keyboard data format.");
		return;
	}

	// Set the keyboard cooperative level
	if (FAILED(mpKeyboard->SetCooperativeLevel(hWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY)))
	{
		// Write to log
		Log::Get()->Write(LogType::Error, "[Input] Failed to set keyboard cooperative level.");
		return;
	}

	// Acquire the keyboard device
	if (FAILED(mpKeyboard->Acquire()))
	{
		// Write to log
		Log::Get()->Write(LogType::Error, "[Input] Failed to acquire keyboard device.");
	}
	//----------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------------
	// Create mouse device
	if (FAILED(mpDI->CreateDevice(GUID_SysMouse, &mpMouse, nullptr)))
	{
		// Write to log
		Log::Get()->Write(LogType::Error, "[Input] Failed to create mouse device.");
		return;
	}

	// Set the mouse data format
	if (FAILED(mpMouse->SetDataFormat(&c_dfDIMouse)))
	{
		// Write to log
		Log::Get()->Write(LogType::Error, "[Input] Failed to set mouse data format.");
		return;
	}

	// Set the mouse cooperative level
	if (FAILED(mpMouse->SetCooperativeLevel(hWindow, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
	{
		// Write to log
		Log::Get()->Write(LogType::Error, "[Input] Failed to set mouse cooperative level.");
		return;
	}

	// Acquire the mouse device
	if (FAILED(mpMouse->Acquire()))
	{
		// Write to log
		Log::Get()->Write(LogType::Error, "[Input] Failed to acquire mouse device.");
	}

	// Calculate starting mouse position
	RECT clientRect;
	GetClientRect(hWindow, &clientRect);
	GetWindowRect(hWindow, &clientRect);
	mScreenWidth = clientRect.right - clientRect.left;
	mScreenHeight = clientRect.bottom - clientRect.top;
	mMouseX = mScreenWidth>> 1;
	mMouseY = mScreenHeight>> 1;
	//----------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------------
	// Enumerate for game pad device
	if (FAILED(mpDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumGamePadCallback, nullptr, DIEDFL_ATTACHEDONLY)))
	{
		// Write to log
		Log::Get()->Write(LogType::Warning, "[Input] Failed to enumerate for game pad devices.");
	}

	// Check if we have a game pad detected
	if (nullptr != mpGamePad)
	{
		// Set the game pad data format
		if (FAILED(mpGamePad->SetDataFormat(&c_dfDIJoystick)))
		{
			// Write to log
			Log::Get()->Write(LogType::Error, "[Input] Failed to set game pad data format.");
			return;
		}

		// Set the game pad cooperative level
		if (FAILED(mpGamePad->SetCooperativeLevel(hWindow, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
		{
			// Write to log
			Log::Get()->Write(LogType::Error, "[Input] Failed to set game pad cooperative level.");
			return;
		}

		// Acquire the game pad device
		if (FAILED(mpGamePad->Acquire()))
		{
			// Write to log
			Log::Get()->Write(LogType::Error, "[Input] Failed to acquire game pad device.");
		}
	}
	else
	{
		// Write to log
		Log::Get()->Write(LogType::Warning, "[Input] No game pad attached.");
	}

	// Set flag
	mInitialized = true;

	// Write to log
	Log::Get()->Write(LogType::Message, "[Input] System initialized.");
}