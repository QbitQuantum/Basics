void PressHotKey(BYTE key, BYTE mod)
{
	keybd_event(mod, 0, 0, 0);
	keybd_event(key, 0, 0, 0);
	keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(mod, 0, KEYEVENTF_KEYUP, 0);
}