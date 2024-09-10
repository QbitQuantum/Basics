void CSysProgressDlg::Stop()
{
	if ((m_isVisible)&&(IsValid()))
	{
		m_pIDlg->StopProgressDialog();
		// Sometimes the progress dialog sticks around after stopping it,
		// until the mouse pointer is moved over it or some other triggers.
		// We hide the window here immediately.
		if (m_hWndProgDlg)
		{
			// The progress dialog is handled on a separate thread, which means
			// even calling StopProgressDialog() will not stop it immediately.
			// Even destroying the progress window is not enough.
			// Which can cause problems with modality: if we stop the progress
			// dialog and immediately show e.g. a messagebox over the same
			// window the progress dialog has as its parent, then the messagebox
			// is modal first (deactivates the parent), but then a little bit
			// later the progress dialog finally closes properly, and by doing that
			// re-enables its parent window.
			// Which leads to the parent window being enabled even though
			// the modal messagebox is shown over the parent window.
			// This situation can even lead to the messagebox appearing *behind*
			// the parent window (race condition)
			// 
			// So, to really ensure that the progress dialog is fully stopped
			// and destroyed, we have to attach to its UI thread and handle
			// all messages until there are no more messages: that's when
			// the progress dialog is really gone.
			AttachThreadInput(GetWindowThreadProcessId(m_hWndProgDlg, 0), GetCurrentThreadId(), TRUE);
			// StartProgressDialog creates a new thread to host the progress window.
			// When the window receives WM_DESTROY message StopProgressDialog() wrongly
			// attempts to re-enable the parent in the calling thread (our thread),
			// after the progress window is destroyed and the progress thread has died.
			// When the progress window dies, the system tries to assign a new foreground window.
			// It cannot assign to hwndParent because StartProgressDialog (w/PROGDLG_MODAL) disabled the parent window.
			// So the system hands the foreground activation to the next process that wants it in the
			// system foreground queue. Thus we lose our right to recapture the foreground window.
			// To fix this problem, we enable the parent window and set to focus to it here, after
			// we've attached to the window thread.
			ShowWindow(m_hWndProgDlg, SW_HIDE);
			EnableWindow(m_hWndParent, TRUE);
			if (m_hWndFocus)
				SetFocus(m_hWndFocus);
			else
				SetFocus(m_hWndParent);
			auto start = GetTickCount64();
			while (::IsWindow(m_hWndProgDlg) && ((GetTickCount64() - start) < 3000))
			{
				MSG msg = { 0 };
				while (PeekMessage(&msg, m_hWndProgDlg, 0, 0, PM_REMOVE))
				{
				}
			}
		}
		m_isVisible = false;
		m_pIDlg.Release();

		m_hWndProgDlg = nullptr;
	}
}