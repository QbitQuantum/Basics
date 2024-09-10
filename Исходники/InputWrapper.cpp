	bool InputWrapper::Init(HINSTANCE hinstance, HWND hwnd)
	{
		if (myIsInitialized == false)
		{
			myIsInitialized = true;
			HRESULT result;

			// Initialize the main direct input interface.
			result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&myDirectInputInterface, NULL);
			if (FAILED(result) == true)
			{
				return false;
			}

			// Initialize the direct input interface for the keyboard.
			result = myDirectInputInterface->CreateDevice(GUID_SysKeyboard, &myKeyboard, NULL);
			if (FAILED(result) == true)
			{
				return false;
			}

			// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
			result = myKeyboard->SetDataFormat(&c_dfDIKeyboard);
			if (FAILED(result) == true)
			{
				return false;
			}

			// Set the cooperative level of the keyboard to not share with other programs.
			result = myKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
			if (FAILED(result) == true)
			{
				return false;
			}

			// Now acquire the keyboard.
			result = myKeyboard->Acquire();
			if (FAILED(result) == true)
			{
				return false;
			}

			// Initialize the direct input interface for the mouse.
			result = myDirectInputInterface->CreateDevice(GUID_SysMouse, &myMouse, NULL);
			if (FAILED(result) == true)
			{
				return false;
			}

			// Set the data format for the mouse using the pre-defined mouse data format.
			result = myMouse->SetDataFormat(&c_dfDIMouse);
			if (FAILED(result) == true)
			{
				return false;
			}

			// Set the cooperative level of the mouse to share with other programs.
			result = myMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
			if (FAILED(result) == true)
			{
				return false;
			}

			// Acquire the mouse.
			result = myMouse->Acquire();
			if (FAILED(result) == true)
			{
				return false;
			}
		}
		return true;
	}