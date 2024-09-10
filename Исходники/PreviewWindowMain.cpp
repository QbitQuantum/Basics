	__declspec(dllexport) void __cdecl SDR_EndMovie()
	{
		/*
			If the user didn't already close it.
		*/
		if (Window::WindowPtr)
		{
			auto handle = Window::WindowThread.native_handle();
			auto id = GetThreadId(handle);

			PostThreadMessageA(id, WM_QUIT, 0, 0);
		}
		
		if (Window::WindowThread.joinable())
		{
			Window::WindowThread.join();
		}

		Synchro::Destroy();
	}