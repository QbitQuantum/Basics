	// Main code to find a window from it's z-order number.
DesktopWindow* GetNumberedWindow(int number, Boolean toplevel, BrowserDesktopWindow* container)
{
	int count;
	count = GetWindowCount(toplevel, container);
	if (number < 0)
		number = count + number;
	else
		number -= 1;
	if (number < 0 || number >= count)
	{
		return NULL;
	}

	int this_index = 0;
	if (container)
	{
		OpWorkspace* workspace = container->GetWorkspace();
		DesktopWindow* sub_win;
		int sub_count;
		if (workspace)
		{
			sub_count = workspace->GetDesktopWindowCount();
			for (int j = 0; j < sub_count; j++)
			{
				sub_win = workspace->GetDesktopWindowFromStack(j);
				if (sub_win && sub_win->GetType() == OpTypedObject::WINDOW_TYPE_DOCUMENT)
				{
					if (this_index == number)
						return sub_win;
					this_index++;
				}
			}
		}
		return NULL;
	}

	DesktopWindowCollection& windows = g_application->GetDesktopWindowCollection();
	int win_num = 0;
	void* theWin;
	while ((theWin = GetNSWindowWithNumber(win_num++)))
	{
		for (DesktopWindowCollectionItem* item = windows.GetFirstToplevel(); item; item = item->GetSiblingItem())
		{
			DesktopWindow* win = item->GetDesktopWindow();
			if (win)
			{
				CocoaOpWindow* opwin = (CocoaOpWindow*)win->GetOpWindow();
				if (opwin && (opwin->IsSameWindow(theWin)))
				{
					// It is a desktop window. Great!
					if (toplevel || win->GetType() == OpTypedObject::WINDOW_TYPE_DOCUMENT)
					{
						if (this_index == number)
							return win;
						this_index++;
					}
					else if (win->GetType() == OpTypedObject::WINDOW_TYPE_BROWSER)
					{
						OpWorkspace* workspace = win->GetWorkspace();
						DesktopWindow* sub_win;
						int sub_count;
						if (workspace)
						{
							sub_count = workspace->GetDesktopWindowCount();
							for (int j = 0; j < sub_count; j++)
							{
								sub_win = workspace->GetDesktopWindowFromStack(j);
								if (sub_win && sub_win->GetType() == OpTypedObject::WINDOW_TYPE_DOCUMENT)
								{
									if (this_index == number)
										return sub_win;
									this_index++;
								}
							}
						}
					}
				}
			}
		}
	}
	return NULL;
}