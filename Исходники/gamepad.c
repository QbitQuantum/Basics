void GamepadSetRumble(GAMEPAD_DEVICE gamepad, float left, float right) {
	if ((STATE[gamepad].flags & FLAG_RUMBLE) != 0) {
		XINPUT_VIBRATION vib;
		ZeroMemory(&vib, sizeof(vib));
		vib.wLeftMotorSpeed = (WORD)(left * 65535);
		vib.wRightMotorSpeed = (WORD)(right * 65535);
		XInputSetState(gamepad, &vib);
	}
}