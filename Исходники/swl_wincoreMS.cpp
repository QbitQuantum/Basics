int Win::DoModal()
{
	WinID lastParentFC = parent ? parent->lastFocusChild : 0; 
	bool visibled = IsVisible();
	bool enabled = IsEnabled();
	try {
		if (!visibled) Show();
		if (!enabled) Enable(true);

		if (parent && type != WT_POPUP) parent->RecalcLayouts();

		AppBlock(GetID());
		UnblockTree(GetID());

		ModalStruct modalStruct;
		modal = &modalStruct;

		MSG msg;
		
		while (!modalStruct.end) 
		{
			wth_DoEvents();
			if (modalStruct.end) break;

			if (!PeekMessage(&msg, NULL, 0, 0,PM_NOREMOVE))
			{
				unsigned waitTime = RunTimers();
				if (waitTime > 5000) waitTime = 5000;
				if (modalStruct.end) break;

				HANDLE thEvent = wthInternalEvent.SignalFD();
				DWORD res = MsgWaitForMultipleObjects(1,&thEvent,FALSE, waitTime, QS_ALLINPUT);

				if (res == WAIT_TIMEOUT) CheckMousePosition();

				continue;
			}

			if (!GetMessage(&msg, NULL, 0, 0)) 
				break;

			DispatchMessage(&msg);
		}

		modal = 0;
		AppUnblock(GetID());
		if (!visibled) Hide();

///
		if (type == WT_POPUP || type == WT_CHILD && parent) 
		{
			Win *w = GetWinByID(lastParentFC);
			if (w) w->SetFocus();
		}

		return modalStruct.id;
	} catch (...) {
		modal = 0;
		AppUnblock(GetID());
		if (!visibled) Hide(); 
		throw;
	}
}