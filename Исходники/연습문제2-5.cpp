LRESULT CALLBACK WndProc(HWND hWnd, UINT
	iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	static char text[10][100];
	static char text_copy[10][100];
	static SIZE size;
	static int count, xPos, yPos, line = 0;
	static int home = 1;

	switch (iMessage)
	{
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		count = 0;
		return 0;
		//엔터 벡스페이스 이스케이프(화면이 다지워지고 캐럿은 맨위의 앞줄로 이동) 텝 (스페이스 4개) 홈 (그줄의 맨앞으로이동)
	case WM_CHAR:
		if (wParam == VK_BACK) // 벡스페이스
		{
			if (count == 0 && line == 0)
			{
				break;
			}
			count--;
			if (count <= 0)
			{
				line--;
				count = strlen(text[line]);
				yPos = yPos - 20;
			}
		}
		else if (wParam == VK_RETURN)  // 엔터
		{
			if (line < 9) {
				count = 0;
				yPos = yPos + 20;
				line++;
			}
		}
		else if (wParam == VK_TAB) // 텝
		{
			for (int i = 0; i < 4; ++i) {
				text[line][count++] = ' ';
			}
			if (count >= 96)
			{
				line++;
				count = 0;
				yPos += 20;
			}
		}
		else if (wParam == VK_ESCAPE) // 이스케이프
		{
			for (int i = 0; i <= line; i++)
				for (int j = 0; j <= count; j++)
				{
					//text_copy[i][j] = text[i][j];
					text[i][j] = '\0';
				}
			count = 0;
			line = 0;
			yPos = 0;
		}
		else if (wParam =='/')
		{
			if (home != 1)
				home = 1;
			else
				home = 0;
		}
		else
			if (count < 98) 
			{
				text[line][count++] = wParam;
			}
		//home = true;
		text[line][count] = '\0';
		InvalidateRect(hWnd, NULL, TRUE);
		

		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		for (int i = 0; i <= line; ++i)
		{
			TextOut(hDC, 0, (i * 20), text[i], strlen(text[i]));
		}
		if (home==1)
		{
			GetTextExtentPoint(hDC, text[line], strlen(text[line]), &size);
			SetCaretPos(size.cx, yPos);
		}
		else
			SetCaretPos(0, yPos);
		

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}