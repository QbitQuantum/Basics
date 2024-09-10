	//Emulate a mouse click with given float delays
	void LibraryManager::mouse_click(float delay_before, float delay_between, float delay_after)
	{
		Sleep(delay_before);
		mouse_event(MOUSEEVENTF_LEFTDOWN,NULL,NULL,NULL,NULL);
		Sleep(delay_between);
		mouse_event(MOUSEEVENTF_LEFTUP,NULL,NULL,NULL,NULL);
		Sleep(delay_after);
	}