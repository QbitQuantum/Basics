void StartTimedRedraw(UINT millis)
{
	SetTimer(g_hWnd, REFRESH_TIMER, millis, NULL);
}