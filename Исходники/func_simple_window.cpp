LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam){
	GetWindowRect(hWnd, &Okno.win1rect);
	Okno.iPosX = Okno.win1rect.left;
	Okno.iPosY = Okno.win1rect.top;
	Okno.iWidth = Okno.win1rect.right - Okno.win1rect.left;
	Okno.iHeight = Okno.win1rect.bottom - Okno.win1rect.top;

	TCHAR tmp[200] = { 0 };
	switch (uMessage){
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			Okno.iPosX -= 10;
			MoveWindow(hWnd, Okno.iPosX, Okno.iPosY, Okno.iWidth, Okno.iHeight, 1);
			break;
		case VK_RIGHT:
			Okno.iPosX += 10;
			MoveWindow(hWnd, Okno.iPosX, Okno.iPosY, Okno.iWidth, Okno.iHeight, 1);
			break;
		case VK_UP:
			Okno.iPosY -= 10;
			MoveWindow(hWnd, Okno.iPosX, Okno.iPosY, Okno.iWidth, Okno.iHeight, 1);
			break;
		case VK_DOWN:
			Okno.iPosY += 10;
			MoveWindow(hWnd, Okno.iPosX, Okno.iPosY, Okno.iWidth, Okno.iHeight, 1);
			break;
		case VK_TAB:
			Okno.iPosX = 0;
			Okno.iPosY = 0;
			MoveWindow(hWnd, Okno.iPosX, Okno.iPosY, Okno.iWidth, Okno.iHeight, 1);
			break;
		case VK_ESCAPE:
			HWND hPanel = FindWindow(TEXT("Shell_TrayWnd"), NULL);
			if (hPanel){
				SetWindowText(hWnd, TEXT("Дескриптор панели получен"));
			}
			else{
				SetWindowText(hWnd, TEXT("Дескриптор панели НЕ получен"));
			}
			//HWND hWndStart = GetWindow(hPanel, GW_CHILD);
			//HWND hWndStart = FindWindowEx(hPanel, 0, TEXT("Button"), NULL);
			HWND hWndStart = FindWindow(TEXT("Button"), NULL);
			if (hWndStart){
				SetWindowText(hWnd, TEXT("Дескриптор ПУСКА получен"));
			}
			else{
				SetWindowText(hWnd, TEXT("Дескриптор ПУСКА НЕ получен"));
			}
			/*GetWindowRect(hWndStart, &Okno.win1rect);
			Okno.iPosX = 500;
			Okno.iPosY = 500;
			Okno.iWidth = Okno.win1rect.right - Okno.win1rect.left;
			Okno.iHeight = Okno.win1rect.bottom - Okno.win1rect.top;*/
			MoveWindow(hWndStart, 0, 0, 1, 1, 0);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		lmb++;
		break;
	case WM_RBUTTONDOWN:
		rmb++;
		/*HWND hWndCalc;
		hWndCalc = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
		if (hWndCalc){
			SetWindowText(hWndCalc, TEXT("БУЛЬБУЛЯТОР"));
		}
		else{
			MessageBox(hWnd, TEXT("Ошибка"), TEXT("Запустите калькулятор!"), MB_OK | MB_ICONINFORMATION);
		}*/
		break;
	case WM_MBUTTONDOWN:
		cmb++;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	wsprintf(tmp, TEXT("Клики: левой %i, средней %i, правой %i"), lmb, cmb, rmb);
	SetWindowText(hWnd, tmp);



	return 0;
}