void Hotkey::stop_mainwindow()
{
	if (MainWindowHotkeyRegistered) {
		UnregisterHotKey(ServerWND, MainWindowHotKeyId - 0xC000);
		MainWindowHotkeyRegistered = false;
	}
}