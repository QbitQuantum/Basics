bool Read(int XPadPlayer, u32 deviceType, EmulatedDevices::FT0::SStatus* status)
{
	const int base = 0x80;
	XINPUT_STATE xstate;
	DWORD xresult = XInputGetState(XPadPlayer, &xstate);

	// Let's .. yes, let's use XINPUT!
	if (xresult == ERROR_SUCCESS)
	{
		const XINPUT_GAMEPAD& xpad = xstate.Gamepad;

		switch (deviceType)
		{
		case ID_STDCONTROLLER:
			ScaleStickValues(&status->joyx, &status->joyy, xpad.sThumbLX, xpad.sThumbLY);
			ScaleStickValues(&status->joy2x, &status->joy2y, xpad.sThumbRX, xpad.sThumbRY);

			status->ltrig = xpad.bLeftTrigger;
			status->rtrig = xpad.bRightTrigger;

			if (xpad.wButtons & XINPUT_GAMEPAD_A)			{status->buttons ^= CONT_BUTTON_A;}
			if (xpad.wButtons & XINPUT_GAMEPAD_B)			{status->buttons ^= CONT_BUTTON_B;}
			if (xpad.wButtons & XINPUT_GAMEPAD_X)			{status->buttons ^= CONT_BUTTON_X;}
			if (xpad.wButtons & XINPUT_GAMEPAD_Y)			{status->buttons ^= CONT_BUTTON_Y;}
			if (xpad.wButtons & XINPUT_GAMEPAD_START)		{status->buttons ^= CONT_BUTTON_START;}
			if (xpad.wButtons & XINPUT_GAMEPAD_DPAD_UP)		{status->buttons ^= CONT_DPAD_UP;}
			if (xpad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)	{status->buttons ^= CONT_DPAD_DOWN;}
			if (xpad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)	{status->buttons ^= CONT_DPAD_LEFT;}
			if (xpad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)	{status->buttons ^= CONT_DPAD_RIGHT;}
			break;

		case ID_TWINSTICK:
			{
				ScaleStickValues(&status->joyx, &status->joyy, xpad.sThumbLX, xpad.sThumbLY);
				ScaleStickValues(&status->joy2x, &status->joy2y, xpad.sThumbRX, xpad.sThumbRY);

				int x = status->joyx;
				int y = status->joyy;
				int x2 = status->joy2x;
				int y2 = status->joy2y;
				if (x != 0)
				{
					if (x > 168)
						status->buttons ^= CONT_DPAD_RIGHT;
					if (x < 40)
						status->buttons ^= CONT_DPAD_LEFT;
				}
				if (y != 0)
				{
					if (y > 168)
						status->buttons ^= CONT_DPAD_DOWN;
					if (y < 40)
						status->buttons ^= CONT_DPAD_UP;
				}
				if (x2 != 0)
				{
					if (x2 > 168)
						status->buttons ^= CONT_DPAD2_RIGHT;
					if (x2 < 40)
						status->buttons ^= CONT_DPAD2_LEFT;
				}
				if (y2 != 0)
				{
					if (y2 > 168)
						status->buttons ^= CONT_DPAD2_DOWN;
					if (y2 < 40)
						status->buttons ^= CONT_DPAD2_UP;
				}

				if (xpad.bLeftTrigger > 0x10)					{status->buttons ^= CONT_BUTTON_X;}
				if (xpad.bRightTrigger > 0x10)					{status->buttons ^= CONT_BUTTON_A;}
				if (xpad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)	{status->buttons ^= CONT_BUTTON_Y;}
				if (xpad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)	{status->buttons ^= CONT_BUTTON_B;}
				if (xpad.wButtons & XINPUT_GAMEPAD_BACK)		{status->buttons ^= CONT_BUTTON_D;}
				if (xpad.wButtons & XINPUT_GAMEPAD_START)		{status->buttons ^= CONT_BUTTON_START;}
			}
			break;

		case ID_ARCADESTICK:
			{
				ScaleStickValues(&status->joyx, &status->joyy, xpad.sThumbLX, xpad.sThumbLY);

				int x = status->joyx;
				int y = status->joyy;
				if (x != 0)
				{
					if (x > 168)
						status->buttons ^= CONT_DPAD_RIGHT;
					if (x < 40)
						status->buttons ^= CONT_DPAD_LEFT;
				}
				if (y != 0)
				{
					if (y > 168)
						status->buttons ^= CONT_DPAD_DOWN;
					if (y < 40)
						status->buttons ^= CONT_DPAD_UP;
				}

				if (xpad.wButtons & XINPUT_GAMEPAD_A)			{status->buttons ^= CONT_BUTTON_A;}
				if (xpad.wButtons & XINPUT_GAMEPAD_B)			{status->buttons ^= CONT_BUTTON_B;}
				if (xpad.wButtons & XINPUT_GAMEPAD_X)			{status->buttons ^= CONT_BUTTON_X;}
				if (xpad.wButtons & XINPUT_GAMEPAD_Y)			{status->buttons ^= CONT_BUTTON_Y;}
				if (xpad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER){status->buttons ^= CONT_BUTTON_C;}
				if (xpad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER){status->buttons ^= CONT_BUTTON_Z;}
				if (xpad.wButtons & XINPUT_GAMEPAD_START)		{status->buttons ^= CONT_BUTTON_START;}
			}
			break;
		}
		return true;
	}
	else
	{
		if (xresult == ERROR_DEVICE_NOT_CONNECTED)
			printf("x360 pad %i not connected\n", XPadPlayer);
		return false;
	}
}