int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LPARAM const DISPLAY_SHUT_OFF = (LPARAM)2;

	// Tell the system to power-off the display
	SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, DISPLAY_SHUT_OFF);

	// Tell the system to lock the workstation
	LockWorkStation();

	// No way to error check so exit
	return 0;
}