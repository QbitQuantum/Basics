void CTEKWindow::OnTimer(UINT nIDEvent)
{
	UINT T;

	if (nIDEvent==IdCaretTimer) {
		if (ts.NonblinkingCursor!=0) {
			T = GetCaretBlinkTime();
			SetCaretBlinkTime(T);
		}
		else {
			::KillTimer(HTEKWin,IdCaretTimer);
		}
		return;
	}
	else {
		::KillTimer(HTEKWin,nIDEvent);
	}
}