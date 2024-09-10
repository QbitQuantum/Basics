void XBox360XInput::setVibration( unsigned short left , unsigned short right , unsigned int player )
{
	XINPUT_VIBRATION vibration;
	vibration.wLeftMotorSpeed = left;
	vibration.wRightMotorSpeed = right;
	XInputSetState( player , &vibration );
}