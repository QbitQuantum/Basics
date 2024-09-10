void EQEmuLogSys::ProcessConsoleMessage(uint16 debug_level, uint16 log_category, const std::string &message)
{

	#ifdef _WINDOWS
		HANDLE  console_handle;
		console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_FONT_INFOEX info = { 0 };
		info.cbSize = sizeof(info);
		info.dwFontSize.Y = 12; // leave X as zero
		info.FontWeight = FW_NORMAL;
		wcscpy(info.FaceName, L"Lucida Console");
		SetCurrentConsoleFontEx(console_handle, NULL, &info);
		SetConsoleTextAttribute(console_handle, EQEmuLogSys::GetWindowsConsoleColorFromCategory(log_category));
		std::cout << message << "\n";
		SetConsoleTextAttribute(console_handle, Console::Color::White);
	#else
		std::cout << EQEmuLogSys::GetLinuxConsoleColorFromCategory(log_category) << message << LC_RESET << std::endl;
	#endif
}