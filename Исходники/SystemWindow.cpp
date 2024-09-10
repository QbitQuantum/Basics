	//Every Windows Message will hit this function. 
	LRESULT CALLBACK GlobalWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) 
	{

		//Hold our target window instance
		SystemWindow *targetWindow = NULL;

		//If it's the WM_NCCREATE message (which should be the first message we get...)
		if(msg == WM_NCCREATE) {
			//Pull the target window out of the lpCreateParams which is the this pointer we pass into CreateWindowEx
			targetWindow = reinterpret_cast<SystemWindow*>((LONG)((LPCREATESTRUCT)lparam)->lpCreateParams);
			//Set the pointer to this instance in the GWLP_USERDATA so we can pull it out reliably in the future
			SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)targetWindow);
		}
		else {
			//Pull the window instance out of the GWLP_USERDATA
			targetWindow = reinterpret_cast<SystemWindow*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
		}

		//If we still don't have a window we can't respond to any events so kick it to the default.
		if(targetWindow == NULL) {
			return DefWindowProc(hwnd, msg, wparam, lparam);
		}

		//Otherwise we're all good and we can pipe it to the instances version of the WndProc
		return targetWindow->LocalWndProc(hwnd, msg, wparam, lparam);
	}