// 鼠标左键按下
void ProgressController::left_button_down()
{
	// 查询当前光标位置，判断光标是在滑道还是滑块上
	POINT p;
	GetCursorPos(&p);
	HWND hwnd = GetCapture();
	ScreenToClient(hwnd, &p);

	if (p.x >= m_left && p.x <= m_left + m_width)
	{
		// 如果光标在滑道上
		POINT point;
		GetCursorPos(&point); // 查询光标位置
	}
}