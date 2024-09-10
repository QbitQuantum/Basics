static void WindowMonitorTask()
{
	LOG4CXX_DEBUG(NYDWE::gInjectLogger, "Monitor thread started.");

	try
	{
		std::string result;
		while (!WorldEditStrings("WESTRING_MODIFYTEXTURES", result))
		{
			boost::this_thread::sleep(boost::posix_time::milliseconds(125));
		}
		std::wstring text = ydwe::util::u2w(result);

		while (!gWindowMonitorShouldExit)
		{
			boost::this_thread::sleep(boost::posix_time::milliseconds(125));

			// Check dialog
			HWND dialog = FindWindowW(L"#32770", text.c_str());
			if (dialog && IsDlgButtonChecked(dialog, 0xC /* CheckBox */))
			{
				EnableWindow(GetDlgItem(dialog, 0x10 /* Delete style */), TRUE);
				EnableWindow(GetDlgItem(dialog, 0x11 /* Add style */), TRUE);
				EnableWindow(GetDlgItem(dialog, 0x12 /* Replace style */), TRUE);
			}
		}
	}
	catch (boost::thread_interrupted &) 
	{
		LOG4CXX_DEBUG(NYDWE::gInjectLogger, "Monitor thread interruppted.");
	}

	LOG4CXX_DEBUG(NYDWE::gInjectLogger, "Monitor thread ends.");
}