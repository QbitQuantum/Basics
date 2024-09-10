LRESULT CALLBACK WinFun(HWND hwnd, UINT message, 
						WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN Pen=CreatePen(PS_DASHDOTDOT, 1, RGB(130,10,130));		// Стиль и цвет границы
	HBRUSH br=CreateHatchBrush(HS_DIAGCROSS, RGB(255,255,0));	// Стиль и цвет штриховки
			
	switch(message)
	{
	case WM_RBUTTONDOWN:
		x2=x1=LOWORD(lParam);
		y2=y1=HIWORD(lParam);
		break;
	case WM_MOUSEMOVE:
		if (wParam & MK_RBUTTON)								// Определяем нажатие правой кнопки мыши
		{
			x2=LOWORD(lParam);
			y2=HIWORD(lParam);
		}
		break;
	case WM_RBUTTONUP:											// Отпускаем правую кнопку мыши
		hdc=GetDC(hwnd);
		SelectObject(hdc, Pen);									// Делаем перо активным
		Ellipse(hdc, x1, y1, x2, y2);							// Определяем размеры эллипса
		SelectObject(hdc, br);									// Делаем кисть активной
		Ellipse(hdc, x1, y1, x2, y2);							// Определяем размеры заштрихованной части
		DeleteObject(Pen);										// Удаляем перо
		DeleteObject(br);										// Удаляем кисть
		ReleaseDC(hwnd, hdc);
		
		p=new EllipsList;
		p->L.x1=x1; p->L.x2=x2;
		p->L.y1=y1; p->L.y2=y2;
		add(pFirst, p);
		break;

	//case WM_ERASEBKGND:										// Не стирает рисунок
	case WM_PAINT:												// Перерисовка
		hdc=BeginPaint(hwnd, &ps);
		p=pFirst;
		while(p)												// Просматриваем список и рисуем эллипс
		{
		SelectObject(hdc, Pen);									// Делаем перо активным
		Ellipse(hdc, p->L.x1, p->L.y1, p->L.x2, p->L.y2);		// Определяем размеры эллипса
		SelectObject(hdc, br);									// Делаем кисть активной
		Ellipse(hdc, p->L.x1, p->L.y1, p->L.x2, p->L.y2);		// Определяем размеры заштрихованной части
		p=p->pNext;
		}
		
		EndPaint(hwnd, &ps);
		break;
	
	case WM_DESTROY:											// Завершение программы
		PostQuitMessage(0);
		break;


	default:
// Позволяет Windows обрабатывать любые сообщения, неуказанные в предыдущем случае
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}