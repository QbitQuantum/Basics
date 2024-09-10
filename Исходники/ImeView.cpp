LONG CImeView::OnInputLangChange(WPARAM dwCommand, LPARAM dwData)
{
    if (ImmIsIME(m_hKeyLayout) && m_property & IME_PROP_AT_CARET)
		ClearData();

    // Set new keyboard layout.
	InitIme();

	if(Enter()) {
		for (int i = 0; i < MAX_LISTCAND; i++) {
			CANDIDATEFORM cf;

			if (m_property & IME_PROP_AT_CARET) {
	/*
				// This application do not want to set candidate window to
				// any position. Anyway, if an application need to set the
				// candiadet position, it should remove the if 0 code
				// the position you want to set
				cf.dwIndex = i;
				cf.dwStyle = CFS_CANDIDATEPOS;
				cf.ptCurrentPos.x = ptAppWantPosition[i].x;
				cf.ptCurrentPos.y = ptAppWantPosition[i].y;
				ImmSetCandidateWindow(m_hIMC, &CandForm );
	*/
			} else {
				if (!ImmGetCandidateWindow(m_hIMC, i, &cf))
					continue;
				if (cf.dwStyle == CFS_DEFAULT)
					continue;
				cf.dwStyle = CFS_DEFAULT;
				ImmSetCandidateWindow(m_hIMC, &cf);
			}
		}
		Leave();
	}
	return (LONG)DefWindowProc(m_hWnd,WM_INPUTLANGCHANGE, dwCommand, dwData);
}