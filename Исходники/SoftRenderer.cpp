void DrawText_GUI(int x, int y)
{
	static DWORD t = timeGetTime();
	static DWORD frm = 0;
	static unsigned int  m_deltaTime = 0;

	++frm;

	static char strFPS[256] = { "FPS:" };
	const int maxFrm = 100;
	DWORD curTime = timeGetTime();
	DWORD deltaT = (curTime - t);
	static DWORD lastTime = curTime;
	m_deltaTime = curTime - lastTime;
	lastTime = curTime;
	if (deltaT > 500)
	{
		float fps = frm / (deltaT / 1000.f);
		frm = 0;
		t = timeGetTime();
		sprintf_s(strFPS, "FPS:%5.1f, POLY:%d", fps, draw_polys);
	}


	HDC hdc;
	hdc = GetDC(main_window_handle);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);
	TextOutA(hdc, x, y, strFPS, strlen(strFPS));
	ReleaseDC(main_window_handle, hdc);
}