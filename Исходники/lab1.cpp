LRESULT CALLBACK WndProc(
				HWND	hWnd,
				UINT	message,
				WPARAM	wParam,
				LPARAM	lParam)
{
	RECT	Screen;		// используется позднее для размеров окна
	GLuint	PixelFormat;
	static	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// Размер этой структуры
		1,				// Номер версии (?)
		PFD_DRAW_TO_WINDOW |// Формат для Окна
		PFD_SUPPORT_OPENGL |// Формат для OpenGL
		PFD_DOUBLEBUFFER,// Формат для двойного буфера
		PFD_TYPE_RGBA,	// Требуется RGBA формат
		16,				// Выбор 16 бит глубины цвета
		0, 0, 0, 0, 0, 0,// Игнорирование цветовых битов (?)
		0,				// нет буфера прозрачности
		0,				// Сдвиговый бит игнорируется (?)
		0,				// Нет буфера аккумуляции
		0, 0, 0, 0,		// Биты аккумуляции игнорируются (?)
		16,				// 16 битный Z-буфер (буфер глубины)  
		0,				// Нет буфера траффарета
		0,				// Нет вспомогательных буферов (?)
		PFD_MAIN_PLANE,	// Главный слой рисования
		0,				// Резерв (?)
		0, 0, 0			// Маски слоя игнорируются (?)
	};
	switch (message)	// Тип сообщения
	{
		case WM_CREATE:
		hDC = GetDC(hWnd);	// Получить контекст устройства для окна
		PixelFormat = ChoosePixelFormat(hDC, &pfd);
			// Найти ближайшее совпадение для нашего формата пикселов
		if (!PixelFormat)
		{
			MessageBox(0,"Can't Find A Suitable PixelFormat.","Error",MB_OK|MB_ICONERROR);
			PostQuitMessage(0);
			// Это сообщение говорит, что программа должна завершится
			break;	// Предтовращение повтора кода
		}
		if(!SetPixelFormat(hDC,PixelFormat,&pfd))
		{
			MessageBox(0,"Can't Set The PixelFormat.","Error",MB_OK|MB_ICONERROR);
			PostQuitMessage(0);
			break;
		}
		hRC = wglCreateContext(hDC);
		if(!hRC)
		{
			MessageBox(0,"Can't Create A GL Rendering Context.","Error",MB_OK|MB_ICONERROR);
			PostQuitMessage(0);
			break;
		}
		if(!wglMakeCurrent(hDC, hRC))
		{
			MessageBox(0,"Can't activate GLRC.","Error",MB_OK|MB_ICONERROR);
			PostQuitMessage(0);
			break;
		}
		GetClientRect(hWnd, &Screen);
		InitGL(Screen.right, Screen.bottom);
		break;

		case WM_DESTROY:
		case WM_CLOSE:
		ChangeDisplaySettings(NULL, 0);

		wglMakeCurrent(hDC,NULL);
		wglDeleteContext(hRC);
		ReleaseDC(hWnd,hDC);

		PostQuitMessage(0);
		break;

		case WM_KEYDOWN:
		keys[wParam] = TRUE;
		break;

		case WM_KEYUP:
		keys[wParam] = FALSE;
		break;

		case WM_SIZE:
		ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));
		break;

		default:
	return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}