int CautooDlg::domouseclick(int v_x, int v_y, int v_sleepms=0)
{
	SetCursorPos(v_x, v_y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(v_sleepms);
	return(TRUE);
}