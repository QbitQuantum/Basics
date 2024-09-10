//
//   ‘”Ќ ÷»я: InitInstance(HINSTANCE, int)
//
//   Ќј«Ќј„≈Ќ»≈: сохран¤ет обработку экземпл¤ра и создает главное окно.
//
//    ќћћ≈Ќ“ј–»»:
//
//        ¬ данной функции дескриптор экземпл¤ра сохран¤етс¤ в глобальной переменной, а также
//        создаетс¤ и выводитс¤ на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // —охранить дескриптор экземпл¤ра в глобальной переменной

   //Samsung Galaxy S+ Screen Resolution
   int WINDOW_WIDTH = 800;
   int WINDOW_HEIGHT = 480;

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, 
	   CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
   WINDOWINFO info;
   GetWindowInfo(hWnd, &info);
   AdjustWindowRectEx(&rect, info.dwStyle, GetMenu(hWnd) != NULL, info.dwExStyle);
   MoveWindow(hWnd, 0, 0, (rect.right - rect.left), (rect.bottom - rect.top), FALSE); 

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}