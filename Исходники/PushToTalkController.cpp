LRESULT PushToTalkController::HandleInput(WPARAM wParam, LPARAM lParam)
{
	RAWINPUT rawInput;
	UINT bufferSize = sizeof(rawInput);

	auto result = GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &rawInput, &bufferSize, sizeof(RAWINPUTHEADER));
	Assert(result == sizeof(RAWINPUTHEADER) + sizeof(RAWKEYBOARD));
	
	if (rawInput.header.dwType == RIM_TYPEKEYBOARD && rawInput.data.keyboard.VKey == kPushToTalkKey)
	{
		if (rawInput.data.keyboard.Message == WM_KEYDOWN)
		{
			if (m_Muted)
			{
				m_DeviceDatabase.UnmuteAllDevices();
				m_Muted = false;
			}
		}
		else if (rawInput.data.keyboard.Message == WM_KEYUP)
		{
			if (!m_Muted)
			{
				m_DeviceDatabase.MuteAllDevices();
				m_Muted = true;
			}
		}

		return 0;
	}

	auto rawInputPtr = &rawInput;
	return DefRawInputProc(&rawInputPtr, 1, sizeof(RAWINPUTHEADER));
}