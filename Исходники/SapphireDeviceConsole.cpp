	//! sets the caption of the window
	void CSapphirDeviceConsole::setWindowCaption(const wchar_t* text)
	{
#ifdef _SAPPHIRE_WINDOWS_NT_CONSOLE_
		SetConsoleTitleW(text);
#endif
	}