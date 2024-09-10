void XBoxController::vibrate(float motorL = 0.0f, float motorR = 0.0f)
{
		// Create new vibration.
		XINPUT_VIBRATION vibration;

		memset(&vibration, 0, sizeof(XINPUT_VIBRATION));

		int vibrationL = (int)(motorL * MAX_VIBRATION);
		int vibrationR = (int)(motorR * MAX_VIBRATION);

		// Set the vibration values.
		vibration.wLeftMotorSpeed = vibrationL;
		vibration.wRightMotorSpeed = vibrationR;

		// Vibrate the controller.
		XInputSetState((int)_player_index, &vibration);
}