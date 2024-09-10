//定时模拟按下Z
void CALLBACK CC2ZDlg::timerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	if ((GetKeyState('C') & (1 << 15)) != 0) // C键按下
	{
		INPUT input;
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = 'Z';
		input.ki.wScan = MapVirtualKey(input.ki.wVk, MAPVK_VK_TO_VSC);
		SendInput(1, &input, sizeof(INPUT)); // 按下Z键
		Sleep(100); // 可能东方是在处理逻辑时检测一下Z键是否按下才发弹幕，如果这时Z键刚好弹起就没有反应，所以要延迟一下
		input.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(INPUT)); // 弹起Z键
	}
}