	bool PXL_Joystick::activate() {
		return joySetCapture(0, device_id, 0, false) == 0;
	}