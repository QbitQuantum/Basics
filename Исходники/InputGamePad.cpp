void InputGamePad::Vibrate(float _LMotorSpeed, float _RMotorSpeed)
{
	// Check if the controler allows vibrate
	if (m_allowVibrate)
	{
		if ((_LMotorSpeed > 0.0f) || (_RMotorSpeed > 0.0f))
		{
			m_vibrating = true;
		}
		else
		{
			m_vibrating = false;
		}

		// Vibration State
		XINPUT_VIBRATION VibrationState;

		// Clear the memory of the vibration state
		ZeroMemory(&VibrationState, sizeof(XINPUT_VIBRATION));

		// Calculate the vibration values 
		// XInput’s default vibration values range from 0 to 65535
		// So convert the passed in 0.0f to 1.0f values to that
		int LMotorSpeed = int(_LMotorSpeed * 65535.0f);
		int RMotorSpeed = int(_RMotorSpeed * 65535.0f);

		// Set the vibrations
		VibrationState.wLeftMotorSpeed = LMotorSpeed;
		VibrationState.wRightMotorSpeed = RMotorSpeed;

		// Set the Vibration state
		XInputSetState(m_gamepadIndex, &VibrationState);
	}
}