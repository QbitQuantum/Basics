/** Set the position of the candidate window. */
static void SetCandidatePos(HWND hwnd)
{
	HIMC hIMC = ImmGetContext(hwnd);
	if (hIMC != NULL) {
		CANDIDATEFORM cf;
		cf.dwIndex = 0;
		cf.dwStyle = CFS_EXCLUDE;

		if (EditBoxInGlobalFocus()) {
			Point pt = _focused_window->GetCaretPosition();
			cf.ptCurrentPos.x = _focused_window->left + pt.x;
			cf.ptCurrentPos.y = _focused_window->top  + pt.y;
			if (_focused_window->window_class == WC_CONSOLE) {
				cf.rcArea.left   = _focused_window->left;
				cf.rcArea.top    = _focused_window->top;
				cf.rcArea.right  = _focused_window->left + _focused_window->width;
				cf.rcArea.bottom = _focused_window->top  + _focused_window->height;
			} else {
				cf.rcArea.left   = _focused_window->left + _focused_window->nested_focus->pos_x;
				cf.rcArea.top    = _focused_window->top  + _focused_window->nested_focus->pos_y;
				cf.rcArea.right  = cf.rcArea.left + _focused_window->nested_focus->current_x;
				cf.rcArea.bottom = cf.rcArea.top  + _focused_window->nested_focus->current_y;
			}
		} else {
			cf.ptCurrentPos.x = 0;
			cf.ptCurrentPos.y = 0;
			SetRectEmpty(&cf.rcArea);
		}
		ImmSetCandidateWindow(hIMC, &cf);
	}
	ImmReleaseContext(hwnd, hIMC);
}