void Gamepad::Rumble(float leftmotor, float rightmotor) {

	XINPUT_VIBRATION VibrationState;

	ZeroMemory(&VibrationState, sizeof(XINPUT_VIBRATION));

	int ileftmotor = int(leftmotor*65535.0f);
	int irightmotor = int(rightmotor*65535.0f);

	VibrationState.wLeftMotorSpeed = ileftmotor;
	VibrationState.wRightMotorSpeed = irightmotor;

	XInputSetState(m_iGamepadIndex, &VibrationState);

}