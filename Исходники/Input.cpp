	Input::Input(HWND wndw,int numControllers)
	{
		window = wndw;
		ZeroMemory(keyState,256);
		ZeroMemory(&mouseState,sizeof(mouseState));
		ZeroMemory(&state,sizeof(XINPUT_STATE)*4);

		DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&di,NULL);

		di->CreateDevice(GUID_SysKeyboard,&keyboard,NULL);
		keyboard->SetDataFormat(&c_dfDIKeyboard);
		keyboard->SetCooperativeLevel(window,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		keyboard->Acquire();

		di->CreateDevice(GUID_SysMouse,&mouse,NULL);
		mouse->SetDataFormat(&c_dfDIMouse);
		mouse->SetCooperativeLevel(window,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		mouse->Acquire();

		XInputEnable(true);
		this->numControllers = numControllers;
	}