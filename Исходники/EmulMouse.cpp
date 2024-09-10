void EmulMouse::LeftMouseClick(long _mouseX, long _mouseY)
{
	int screenX = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int screenY = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	int propX = 65535 / screenX;
	int propY = 65535 / screenY;

	mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, propX * _mouseX, propY * _mouseY, 0, 0);

	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, propX * _mouseX, propY * _mouseY, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE, propX * _mouseX, propY * _mouseY, 0, 0);
}