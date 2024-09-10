// Set vibration (0.0 to 1.0)
// 0 stops the vibration
void InputHandler::setVibration(  float leftMotor, float rightMotor, t_joyNum joyNum)
{

	XINPUT_VIBRATION vib;
	ZeroMemory(&vib, sizeof(XINPUT_VIBRATION));

	vib.wLeftMotorSpeed = static_cast <WORD> (leftMotor  * 65535.0f);
	vib.wRightMotorSpeed = static_cast <WORD> (rightMotor * 65535.0f);

	XInputSetState(joyNum, &vib);

}