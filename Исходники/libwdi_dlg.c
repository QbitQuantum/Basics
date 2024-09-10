/*
 * Callback for the run_with_progress_bar() function
 */
static LRESULT CALLBACK progress_callback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT loc;
	HANDLE handle;
	static int installation_time = 0;	// active installation time, in secs
	const int msg_max = ARRAYSIZE(progress_message);
	static int msg_index = 0;
	int i;
	// coordinates that we want to disable (=> no resize)
	static LRESULT disabled[9] = { HTLEFT, HTRIGHT, HTTOP, HTBOTTOM, HTSIZE,
		HTTOPLEFT, HTTOPRIGHT, HTBOTTOMLEFT, HTBOTTOMRIGHT };

	switch (message) {

	case WM_CREATE:
		// Reset static variables
		installation_time = 0;
		msg_index = 0;
		hProgress = hDlg;

		// Start modal (disable parent Window)
		EnableWindow(GetParent(hDlg), FALSE);

		init_children(hProgress);
		center_dialog(hProgress);

		// Send a WM_TIMER message every second
		SetTimer(hProgress, 1, 1000, NULL);

		PostMessage(hProgress, UM_PROGRESS_START, 0, 0);

		return (INT_PTR)TRUE;

	case WM_NCHITTEST:
		// Check coordinates to prevent resize actions
		loc = DefWindowProc(hDlg, message, wParam, lParam);
		for(i = 0; i < 9; i++) {
			if (loc == disabled[i]) {
				return (INT_PTR)TRUE;
			}
		}
		return (INT_PTR)FALSE;

	case UM_PROGRESS_START:
		if (progress_thid != -1L) {
			wdi_err("program assertion failed - another operation is in progress");
		} else {
			// Using a thread prevents application freezout on security warning
			progress_thid = _beginthread(progress_thread, 0, NULL);
			if (progress_thid != -1L) {
				return (INT_PTR)TRUE;
			}
			wdi_err("unable to create progress_thread");
		}
		// Fall through and return an error
		wParam = (WPARAM)WDI_ERROR_RESOURCE;

	case UM_PROGRESS_STOP:
		// If you don't re-enable the parent Window before leaving
		// all kind of bad things happen (other Windows get activated, etc.)
		EnableWindow(GetParent(hDlg), TRUE);
		PostQuitMessage((int)wParam);
		DestroyWindow(hProgress);
		return (INT_PTR)TRUE;

	case WM_TIMER:
		if (find_security_prompt() == NULL) {
			installation_time++;	// Only increment outside of security prompts
			if ( (msg_index < msg_max) && (installation_time > 15*(msg_index+1)) ) {
				// Change the progress blurb
				SetWindowTextA(hProgressText, progress_message[msg_index]);
				// Force a full redraw fot the transparent text background
				ShowWindow(hProgressText, SW_HIDE);
				UpdateWindow(hProgressText);
				ShowWindow(hProgressText, SW_SHOW);
				UpdateWindow(hProgressText);
				msg_index++;
			} else if ( (installation_time > 300) && (progress_thid != -1L) ) {
				// Wait 300 (loose) seconds and kill the thread
				// 300 secs is the timeout for driver installation on Vista
				wdi_err("progress timeout expired - KILLING THREAD!");
				handle = OpenThread(THREAD_TERMINATE, FALSE, (DWORD)progress_thid);
				TerminateThread(handle, -1);
				CloseHandle(handle);
				PostQuitMessage(WDI_ERROR_TIMEOUT);
				DestroyWindow(hProgress);
				return (INT_PTR)FALSE;
			}
		}
		return (INT_PTR)TRUE;

	case WM_CLOSE:		// prevent closure using Alt-F4
		return (INT_PTR)TRUE;

	case WM_DESTROY:	// close application
		hProgress = INVALID_HANDLE_VALUE;
		return (INT_PTR)FALSE;

	case WM_CTLCOLORSTATIC:
		pSetBkMode((HDC)wParam, TRANSPARENT);
		return (INT_PTR)pGetStockObject(NULL_BRUSH);
	}
	return DefWindowProc(hDlg, message, wParam, lParam);
}