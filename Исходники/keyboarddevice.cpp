bool KeyboardDevice::doKeyAction(Action action, int nativeKey, bool alterPressedKeys)
{
	bool result = true;
	
#ifdef Q_OS_UNIX
    KeyCode keyCode = XKeysymToKeycode(QX11Info::display(), nativeKey);
	
	if(action == Press || action == Trigger)
		result &= XTestFakeKeyEvent(QX11Info::display(), keyCode, True, CurrentTime);
	if(action == Release || action == Trigger)
		result &= XTestFakeKeyEvent(QX11Info::display(), keyCode, False, CurrentTime);

	XFlush(QX11Info::display());
#endif
	
#ifdef Q_OS_WIN
	INPUT input;
    SecureZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_KEYBOARD;

	switch(mType)
	{
	case Win32:
    {
        input.ki.wVk = nativeKey;

        HKL keyboardLayout = GetKeyboardLayout(0);
        input.ki.wScan = MapVirtualKeyEx(nativeKey, MAPVK_VK_TO_VSC, keyboardLayout);

        if(extendedKeys.count(nativeKey) > 0)
            input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
    }
		break;
	case DirectX:
		input.ki.wVk = 0;
		input.ki.wScan = ActionTools::KeyMapper::toDirectXKey(nativeKey);
		break;
	}

	if(action == Press || action == Trigger)
        result &= (SendInput(1, &input, sizeof(INPUT)) != 0);
	if(action == Release || action == Trigger)
	{
		input.ki.dwFlags |= KEYEVENTF_KEYUP;

        result &= (SendInput(1, &input, sizeof(INPUT)) != 0);
	}
#endif
	
    if(alterPressedKeys)
    {
        if(action == Press)
            mPressedKeys.insert(nativeKey);
        else if(action == Release)
            mPressedKeys.remove(nativeKey);
    }

    return result;
}