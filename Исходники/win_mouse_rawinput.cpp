void
win_mouse_close(void)
{
	RAWINPUTDEVICE ridev;
	ridev.dwFlags = RIDEV_REMOVE;
	ridev.hwndTarget = NULL;
	ridev.usUsagePage = 0x01;
	ridev.usUsage = 0x02;
	RegisterRawInputDevices(&ridev, 1, sizeof(ridev));
}