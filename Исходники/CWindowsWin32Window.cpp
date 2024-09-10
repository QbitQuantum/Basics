	CWindowsWin32Window::~CWindowsWin32Window()
	{
		if(--s_winCount == 0)
		{
			s_pumpTask = nullptr; //The windows don't need it anymore.
			//the pump task will not be deleted until it's dequeued from the thread task list.
		}
		
		//A comment on SetWindowSubclass says to remove the subclass before destroying the window.
		RemoveWindowSubclass(_win,WindowProc,0);
		DestroyWindow(_win);
	}