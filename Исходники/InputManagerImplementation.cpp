CInputManagerImplementation::CInputManagerImplementation(HWND hWnd)
	: m_MovementX(0)
	, m_MovementY(0)
	, m_MovementZ(0)
	, m_ButtonLeft(false)
	, m_ButtonMiddle(false)
	, m_ButtonRight(false)
	, m_PreviousButtonLeft(false)
	, m_PreviousButtonMiddle(false)
	, m_PreviousButtonRight(false)
	, m_MouseSpeed(1)
	,m_FileName("")

{
	m_Alt = false;
	m_Ctrl = false;

	for (int i = 0; i < 256; ++i)
	{
		m_KeysPrevious[i] = m_KeysCurrent[i] = false;
	}

	for (int i = 0; i < 4; ++i)
	{
		m_PadButtensPrevious[i] = 0;
	}


	// mouse input
	HRESULT l_HR;
	DWORD l_CoopFlags = 0;

	/*l_CoopFlags= DISCL_EXCLUSIVE | DISCL_FOREGROUND;*/

	if (FAILED(l_HR = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_DI, NULL)))
		return;
	if (FAILED(l_HR = m_DI->CreateDevice(GUID_SysMouse, &m_Mouse, NULL)))
		return;
	if (FAILED(l_HR = m_Mouse->SetDataFormat(&c_dfDIMouse2)))
		return;
	//if (FAILED(l_HR = m_Mouse->SetCooperativeLevel(hWnd, l_CoopFlags)))
	//	return;

	HMODULE XInputLibrary = LoadLibraryA("xinput1_4.dll");
	if (!XInputLibrary)
	{
		XInputLibrary = LoadLibraryA("xinput9_1_0.dll");
	}

	if (!XInputLibrary)
	{
		XInputLibrary = LoadLibraryA("xinput1_3.dll");
	}

	if (XInputLibrary)
	{
		s_XInputGetState = (TF_XInputGetState *)GetProcAddress(XInputLibrary, "XInputGetState");
		if (!s_XInputGetState) { s_XInputGetState = FakeXInputGetState; }

	}

	if (m_Mouse != NULL)
		m_Mouse->Acquire();
	else
		MessageBox(hWnd, "Problem with de mouse input!", "Mouse", MB_ICONERROR | MB_OK);
}