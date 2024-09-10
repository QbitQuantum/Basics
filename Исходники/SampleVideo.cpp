// для GCC - другая
int main()
#endif
{
	MSG msg;
	WNDCLASSA wcl;
	// 0. Регистрируем оконный класс

	wcl.hInstance = NULL;
	wcl.lpszClassName = szWinName;
	wcl.lpfnWndProc = MyFunc;
	wcl.style = 0;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.lpszMenuName = NULL;

	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;

	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

	if(!RegisterClassA(&wcl)) return 0;

	// 1. Создаём окно

	hWnd = CreateWindowA(szWinName, "Video", 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 700, HWND_DESKTOP, NULL, 
		NULL, NULL);

	// 2. Отображаем окно на экран
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// 3. Запускаем таймер (20 мсек, 50 кадров в секунду)
	SetTimer(hWnd, 1, 20, NULL);

	// 4. стартуем получение кадров с камеры
	InitVideo();

	// 5. Стандартный цикл обработки событий
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}