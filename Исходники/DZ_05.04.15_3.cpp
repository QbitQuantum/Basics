LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	COLORREF colorText = RGB(0, 0, 255); // задаём цвет текста
	
	switch (message)
	{

	case WM_COMMAND:

	case BN_CLICKED:

		if (LOWORD(wParam) == ID_BUTTON1)
		{
			
			GetClientRect(hWnd, &rect);
			edit1 = CreateWindowEx(
				WS_EX_CLIENTEDGE,
				L"edit",
				L"Нажмите правую клавишу мыши",
				WS_CHILD | WS_VISIBLE | EM_FMTLINES,
				rect.right / 4,									/*координаты по X*/
				rect.bottom / 4,								/*координаты по Y*/
				rect.right / 2,									/*Ширина окошка*/
				rect.bottom / 2,
				hWnd,
				(HMENU)ID_EDIT1,
				hinst,
				NULL);
		
		}
		
		break;

	case WM_RBUTTONDOWN:
			
			ShowWindow(edit1, SW_HIDE);
			break;

	case WM_CREATE:

		GetClientRect(hWnd, &rect);
				
		button1 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"button",
			L"Показать",
			WS_CHILD | WS_VISIBLE,
			rect.right / 2 - ARRAYSIZE(L"Показать") * 4 - 10,		/*координаты по X*/
			rect.bottom - 30,						/*координаты по Y*/
			ARRAYSIZE(L"Показать") * 10,						/*Ширина окошка*/
			25,
			hWnd,
			(HMENU)ID_BUTTON1,
			hinst,
			NULL);

		
		break;

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps); // инициализируем контекст устройства
		GetClientRect(hWnd, &rect); // получаем ширину и высоту области для рисования
		SetTextColor(hdc, colorText); // устанавливаем цвет контекстного устройства
		
		
				DrawText(hdc, L"В в е д и т е   т е к с т", -1, &rect, DT_SINGLELINE | DT_CENTER); // рисуем текст
			
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}