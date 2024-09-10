void GameConsole::displayChat(bool console)
{
	capsLockToggled = GetKeyState(VK_CAPITAL) & 1;

	if (console)
	{
		if (selectedQueue != &consoleQueue)
		{
			lastChatQueue = selectedQueue;
		}
		selectedQueue = &consoleQueue;
		showConsole = true;
	}
	else
	{
		selectedQueue = lastChatQueue;
		showChat = true;
	}

	selectedQueue->startIndexForScrolling = 0;

	// Disables game keyboard input and enables our keyboard hook
	RAWINPUTDEVICE Rid;
	Rid.usUsagePage = 0x01;
	Rid.usUsage = 0x06;
	Rid.dwFlags = RIDEV_NOLEGACY; // adds HID keyboard and also ignores legacy keyboard messages
	Rid.hwndTarget = 0;

	if (!RegisterRawInputDevices(&Rid, 1, sizeof(Rid))) {
		consoleQueue.pushLineFromGameToUI("Registering keyboard failed");
	}
}