	void CInputManager::SetMotorSpeed(UINT gamepad, USHORT speedLeft, USHORT speedRight)
	{
		XINPUT_VIBRATION vib;
		vib.wLeftMotorSpeed = speedLeft;
		vib.wRightMotorSpeed = speedRight;
		XInputSetState(gamepad, &vib);
	}