	virtual void OnUpdate()
	{
		IInput *pInput = m_pInput;
		XINPUT_CAPABILITIES caps;

		while (!m_bQuit)
		{
			{
				for (DWORD i = 0; i < 4; ++i)
				{
					DWORD r = XInputGetCapabilities(i, XINPUT_FLAG_GAMEPAD, &caps);
					g_bConnected[i] = r == ERROR_SUCCESS;
				}
			}
			Sleep(1000);
		}
	}