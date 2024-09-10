void CDirectSerial::setBreak (bool value) {
	if (value) SetCommBreak (hCom);
	else ClearCommBreak (hCom);
}