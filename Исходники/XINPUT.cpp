	DLL_IMPORT DWORD XINPUT_GetState(DWORD dwUserIndex, XINPUT_STATE *pState)
	{
		printf("XInput_GetState(0x%X, 0x%X)\n", dwUserIndex, pState);
		return XInputGetState(dwUserIndex, pState);
	}