bool keyReleaseWindows(int key, int modifiers = 0, bool extended = false)
{
	DRIVER_CHECK(key != 0, " Error: key = 0 in GTKeyboardDriver::keyRelease()");

	if (modifiers) {
		INPUT input = getKeyEvent(modifiers, true);
		SendInput(1, &input, sizeof(input));
	}

	INPUT input = getKeyEvent(key, true, extended);
	SendInput(1, &input, sizeof(input));

	return true;
}