// Generate a mouse right click based on hardware.
void VirtualMouse::generate_right_click()
{
	mouse_event.mi.dx = 0;
	mouse_event.mi.dy = 0;

	mouse_event.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &mouse_event, sizeof(mouse_event));

	mouse_event.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &mouse_event, sizeof(mouse_event));
}