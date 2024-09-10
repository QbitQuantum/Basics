bool CChordEaseApp::HandleDlgKeyMsg(MSG* pMsg)
{
	static const LPCSTR	EditBoxCtrlKeys = "ACHVX";	// Z reserved for app undo
	CMainFrame	*Main = theApp.GetMain();
	ASSERT(Main != NULL);	// main frame must exist
	switch (pMsg->message) {
	case WM_KEYDOWN:
		{
			int	VKey = INT64TO32(pMsg->wParam);
			bool	bTryMainAccels = FALSE;	// assume failure
			if ((VKey >= VK_F1 && VKey <= VK_F24) || VKey == VK_ESCAPE) {
				bTryMainAccels = TRUE;	// function key or escape
			} else {
				bool	IsAlpha = VKey >= 'A' && VKey <= 'Z';
				CEdit	*pEdit = CFocusEdit::GetEdit();
				if (pEdit != NULL) {	// if an edit control has focus
					if ((IsAlpha									// if (alpha key
					&& strchr(EditBoxCtrlKeys, VKey) == NULL		// and unused by edit
					&& (GetKeyState(VK_CONTROL) & GKS_DOWN))		// and Ctrl is down)
					|| ((VKey == VK_SPACE							// or (space key,
					|| VKey == VK_RETURN || VKey == VK_BACK)		// Enter or Backspace
					&& (GetKeyState(VK_CONTROL) & GKS_DOWN))		// and Ctrl is down)
					|| (VKey == VK_SPACE							// or (space key
					&& (GetKeyState(VK_SHIFT) & GKS_DOWN))			// and Shift is down)
					|| (IsAlpha										// or (alpha key
					&& pEdit->IsKindOf(RUNTIME_CLASS(CNumEdit))		// and numeric edit
					&& (VKey > 'G'									// and (key above G
					|| !pEdit->IsKindOf(RUNTIME_CLASS(CNoteEdit)))	// or not note edit)
					&& (GetKeyState(VK_SHIFT) & GKS_DOWN)))			// and Shift is down)
						bTryMainAccels = TRUE;	// give main accelerators a try
				} else {	// non-edit control has focus
					if (IsAlpha										// if alpha key
					|| VKey == VK_SPACE								// or space key
					|| (GetKeyState(VK_CONTROL) & GKS_DOWN)			// or Ctrl is down
					|| (GetKeyState(VK_SHIFT) & GKS_DOWN))			// or Shift is down
						bTryMainAccels = TRUE;	// give main accelerators a try
				}
			}
			if (bTryMainAccels) {
				HACCEL	hAccel = Main->GetAccelTable();
				if (hAccel != NULL
				&& TranslateAccelerator(Main->m_hWnd, hAccel, pMsg))
					return(TRUE);	// message was translated, stop dispatching
			}
		}
		break;
	case WM_SYSKEYDOWN:
		// if focused window isn't descendant of main frame (e.g. floating bar's controls
		// are descendants of miniframe) main frame must steal focus else main menus fail
		if (!IsChild(Main->m_hWnd, GetFocus())) {	// avoid stealing focus needlessly
			if (GetKeyState(VK_SHIFT) & GKS_DOWN)	// if context menu
				return(FALSE);	// keep dispatching (false alarm)
			Main->SetFocus();	// main frame must have focus to display menus
			Main->SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);	// enter menu mode
			return(TRUE);	// message was translated, stop dispatching
		}
		break;
	}
	return(FALSE);	// continue dispatching
}